#!/usr/bin/env python3

import copy
import glob
import math
import numpy as np
import pandas as pd
import plotly
import plotly.graph_objects as go
import os
import sys
import scipy
import scipy.io.wavfile
from scipy import signal

triggerVelocityThreshold = 3.0
maxTriggerDelayUs = 40000
minTriggerJitterDelayUs = 15000
releasePositionThreshold = 0.4
releasePositionAbsolute = 0.15
pedalReleaseThreshold = 0.1
pedalPressThreshold = 0.2
velocityEmaAlpha = 0.1

def findFromTo(b, e, t):
    for i,v in enumerate(t):
        if v >= b:
            rFrom = i
            break
    else:
        raise Exception("Could not find matching time for begin")

    for i,v in enumerate(t):
        if v >= e:
            rTo = i
            break
    else:
        raise Exception("Could not find matching time for end")

    return (rFrom,rTo)


def IsValidVelocityMaximum(pos, vel):
    return ((pos > .45) and (vel > 4.5)) or ((pos > .6) and (vel > 2.0))

class LogicState:
    def __init__(self):
        self.lastUpdateTime = 0
        self.pos = 0.0
        self.vel = 0.0
        self.velEma = 0.0

        self.changed = False
        self.pressed = False

        self.lastPressTime = 0
        self.pressVelocity = 0.0
        self.lastReleaseTime = 0

        self.maxVelTime = 0
        self.maxVel = 0.0
        self.maxVelEma = 0.0
        self.maxVelPos = 0.0

        self.samplesLowCount = 0

    def nextState(self, now, deltaTime, newData):
        velEmaAlpha = 0.1

        prevPos = self.pos
        prevVel = self.vel
        self.pos = newData
        self.vel = (self.pos - prevPos) * (1000000.0 / deltaTime)
        self.velEma = self.velEma * (1.0 - velEmaAlpha) + self.vel * velEmaAlpha

        if (prevVel < 5.0 and self.vel < 5.0):
            self.samplesLowCount += 1
        elif prevVel > self.vel:
            self.samplesLowCount = 0

        self.changed = False
        if self.pressed:
            if (self.pos < releasePositionAbsolute) or ((self.maxVelPos - self.pos) > releasePositionThreshold * self.maxVelPos):
                self.pressed = False
                self.changed = True
                self.lastReleaseTime = now

                self.maxVelTime = 0
                self.maxVel = 0.0
                self.maxVelEma = 0.0
                self.maxVelPos = 0.0
        else:
            if (prevPos < .3 and self.pos >= .3):
                self.allow = now
                #self.pressed = True
                #self.changed = True
                #self.lastPressTime = now
                #print("trigg {} ®{} ".format(self.vel, (self.pos - self.minPos) * (1000000 / (now - self.minTime))))
                #self.pressVelocity = self.vel / 60.0
                #self.pressVelocity = (self.pos - self.minPos) * (1000000 / (now - self.minTime))

            if self.vel > self.maxVel:
                if IsValidVelocityMaximum(self.pos, self.vel):
                    self.maxVelTime = now
                    self.maxVel = self.vel
                    self.maxVelEma = self.velEma
                    self.maxVelPos = self.pos
                    if True or now - self.allow < 5000:
                        print("allow {} = {}".format(now, self.vel / 60))
                        self.pressed = True
                        self.changed = True
                        self.lastPressTime = now
                        self.pressVelocity = self.vel / 60
                        self.allow = 0
                    else:
                        print("fail {} diff {} >= 5000".format(now, now - self.allow))
                        self.allow = 0
                        self.maxVelTime = 0
                        self.maxVel = 0.0
                        self.maxVelEma = 0.0
                        self.maxVelPos = 0.0
                    #if self.samplesLowCount > 4:
                    #    print("instant {}".format(self.maxVelTime))
                    #    self.pressed = True
                    #    self.changed = True
                    #    self.lastPressTime = self.maxVelTime
                    #    self.pressVelocity = self.maxVel / 60
                    #    return

            if self.pos < prevPos:
                self.minPos = self.pos
                self.minTime = now

            #if ((prevVel > triggerVelocityThreshold) and (self.vel <= triggerVelocityThreshold)):
            #    if ((now - self.maxVelTime) <= maxTriggerDelayUs) and (now - self.lastReleaseTime > minTriggerJitterDelayUs):
            #        self.pressed = True
            #        self.changed = True
            #        self.lastPressTime = self.maxVelTime
            #        self.pressVelocity = self.maxVel / 60
            #    #else:
            #    #    self.maxVelTime = 0
            #    #    self.maxVel = 0.0
            #    #    self.maxVelEma = 0.0
            #    #    self.maxVelPos = 0.0
            #elif (prevPos < .8 and self.pos >= .8):
            #    if ((now - self.maxVelTime) <= maxTriggerDelayUs) and (now - self.lastReleaseTime > minTriggerJitterDelayUs):
            #        print("now {}".format(self.maxVelTime))
            #        self.pressed = True
            #        self.changed = True
            #        self.lastPressTime = self.maxVelTime
            #        self.pressVelocity = self.maxVel / 60
            #elif (prevVel - self.vel >= 20):
            #    if ((now - self.maxVelTime) <= maxTriggerDelayUs) and (now - self.lastReleaseTime > minTriggerJitterDelayUs):
            #        print("v now {}".format(self.maxVelTime))
            #        self.pressed = True
            #        self.changed = True
            #        self.lastPressTime = self.maxVelTime
            #        self.pressVelocity = self.maxVel / 60
            #    #else:
            #    #    self.maxVelTime = 0
            #    #    self.maxVel = 0.0
            #    #    self.maxVelEma = 0.0
            #    #    self.maxVelPos = 0.0

# Config
includeRaw=True

# Constants (DONT CHANGE!)
plotAxisPos = "y"
plotAxisPosRaw = "y3"
plotAxisVel = "y2"
plotAxisVelRaw = "y4"
plotAxisWav = "y5"
plotAxisTriggers = plotAxisPosRaw

maxKeyFreqDeviation = 0.05
keyFrequencies = {
    'A0'    : 27.50000, 'A+0'   : 29.13524, 'B0'    : 30.86771, 'C1'    : 32.70320,
    'C+1'   : 34.64783, 'D1'    : 36.70810, 'D+1'   : 38.89087, 'E1'    : 41.20344,
    'F1'    : 43.65353, 'F+1'   : 46.24930, 'G1'    : 48.99943, 'G+1'   : 51.91309,
    'A1'    : 55.00000, 'A+1'   : 58.27047, 'B1'    : 61.73541, 'C2'    : 65.40639,
    'C+2'   : 69.29566, 'D2'    : 73.41619, 'D+2'   : 77.78175, 'E2'    : 82.40689,
    'F2'    : 87.30706, 'F+2'   : 92.49861, 'G2'    : 97.99886, 'G+2'   : 103.8262,
    'A2'    : 110.0000, 'A+2'   : 116.5409, 'B2'    : 123.4708, 'C3'    : 130.8128,
    'C+3'   : 138.5913, 'D3'    : 146.8324, 'D+3'   : 155.5635, 'E3'    : 164.8138,
    'F3'    : 174.6141, 'F+3'   : 184.9972, 'G3'    : 195.9977, 'G+3'   : 207.6523,
    'A3'    : 220.0000, 'A+3'   : 233.0819, 'B3'    : 246.9417, 'C4'    : 261.6256,
    'C+4'   : 277.1826, 'D4'    : 293.6648, 'D+4'   : 311.1270, 'E4'    : 329.6276,
    'F4'    : 349.2282, 'F+4'   : 369.9944, 'G4'    : 391.9954, 'G+4'   : 415.3047,
    'A4'    : 440.0000, 'A+4'   : 466.1638, 'B4'    : 493.8833, 'C5'    : 523.2511,
    'C+5'   : 554.3653, 'D5'    : 587.3295, 'D+5'   : 622.2540, 'E5'    : 659.2551,
    'F5'    : 698.4565, 'F+5'   : 739.9888, 'G5'    : 783.9909, 'G+5'   : 830.6094,
    'A5'    : 880.0000, 'A+5'   : 932.3275, 'B5'    : 987.7666, 'C6'    : 1046.502,
    'C+6'   : 1108.731, 'D6'    : 1174.659, 'D+6'   : 1244.508, 'E6'    : 1318.510,
    'F6'    : 1396.913, 'F+6'   : 1479.978, 'G6'    : 1567.982, 'G+6'   : 1661.219,
    'A6'    : 1760.000, 'A+6'   : 1864.655, 'B6'    : 1975.533, 'C7'    : 2093.005,
    'C+7'   : 2217.461, 'D7'    : 2349.318, 'D+7'   : 2489.016, 'E7'    : 2637.020,
    'F7'    : 2793.826, 'F+7'   : 2959.955, 'G7'    : 3135.963, 'G+7'   : 3322.438,
    'A7'    : 3520.000, 'A+7'   : 3729.310, 'B7'    : 3951.066, 'C8'    : 4186.009,
    'Soft'  : 0.0,
    'Damp'  : 0.0,
}

def butter_bandpass(lowcut, highcut, fs, order=5):
    nyq = 0.5 * fs
    low = lowcut / nyq
    high = highcut / nyq
    b, a = signal.butter(order, [low, high], btype='band')
    return b, a

def butter_bandpass_filter(data, lowcut, highcut, fs, order=5):
    b, a = butter_bandpass(lowcut, highcut, fs, order=order)
    y = signal.lfilter(b, a, data)
    return y

def running_mean(x, N):
    cumsum = np.cumsum(np.insert(x, 0, 0))
    return (cumsum[N:] - cumsum[:-N]) / float(N)


#def butter_lowpass(cutoff, fs, order):
#    nyq = 0.5 * fs
#    normal_cutoff = cutoff / nyq
#    b, a = signal.butter(order, normal_cutoff, btype='low', analog=False)
#    return b, a
#
#def butter_lowpass_filter(data, cutoff, fs, order=5):
#    b, a = butter_lowpass(cutoff, fs, order=order)
#    y = signal.lfilter(b, a, data)
#    return y
#
#cutoff=50
#fs=1000000/(csv['time'].iloc[-1]/len(csv['time']))

def getInputFiles(inputPath):
    if os.path.isdir(inputPath):
        path = inputPath
        fileBasenames = glob.glob(os.path.join(path, "*.raw"))
        fileBasenames = [os.path.basename(f) for f in fileBasenames if os.path.isfile(f)]
        fileBasenames.sort(key=lambda f: os.path.getmtime(os.path.join(path, f)))
    elif os.path.isfile(inputPath):
        path = os.path.dirname(inputPath)
        fileBasenames = [os.path.basename(inputPath)]
    else:
        print("error: Given path is neither a directory nor a .raw file'".format(path))
        sys.exit(1)

    return (path, fileBasenames)

def setFigureLayout(fig):
    fig.update_traces(mode='lines')
    fig.update_layout(
        xaxis=dict(
            title="Time (s)",
            domain=[.04,.92] if includeRaw else [0.0, 1.0],
            ),
        yaxis=dict(
            title="Position",
            overlaying="y",
            anchor="x",
            side="left",
            ),
        yaxis2=dict(
            title="Velocity",
            overlaying="y",
            anchor="x",
            side="right",
            ),
        yaxis5=dict(
            title="dB",
            overlaying="y",
            anchor="free",
            side="right",
            position=1.0,
            ),
        )
    if includeRaw:
        fig.update_layout(
            yaxis3=dict(
                title="Raw Position",
                overlaying="y",
                anchor="free",
                side="left",
                position=0.0,
                ),
            yaxis4=dict(
                title="Raw Velocity",
                overlaying="y",
                anchor="free",
                side="right",
                position=0.96,
                ),
            )
    fig.update_layout(
        template='plotly_dark',
        title="Sensor Plot"
        )

class Meta:
    def __init__(self, file):
        try:
            with open(file, 'r') as f:
                content = f.readlines()
            content = [l.strip() for l in content]
        except IOError:
            raise IOError("Could not open meta file '{}'".format(file))

        if len(content) != 5:
            raise IOError("Invalid meta content length")

        self.uniqueSessionId = int(content[0])
        self.hostOverallBegin = int(content[1])
        self.hostBegin = int(content[2])
        self.hostEnd = int(content[3])
        self.mcuElapsed = int(content[4])

    def getUniqueSessionId(self):
        return self.uniqueSessionId

    def getOverallBeginUsHost(self):
        return self.hostOverallBegin

    def getBeginUsHost(self):
        return self.hostBegin

    def getEndUsHost(self):
        return self.hostEnd

    def getElapsedUsHost(self):
        return self.hostEnd - self.hostBegin

    def getElapsedUsMcu(self):
        return self.mcuElapsed

    def getOverallOffsetSec(self):
        return (self.hostBegin - self.hostOverallBegin) / 1000000

class Capture:
    def __init__(self):
        pass

    @classmethod
    def fromFile(cls, path, basename):
        c = cls()
        c.path = path
        c.basename = basename
        c.name = os.path.splitext(basename)[0]
        c.meta = Meta(c.__getMetaFile())

        tokens = c.name.split('_')
        c.sensorName = tokens[1]
        c.num = tokens[2]
        c.identifier = "{}, #{}".format(c.sensorName, c.num)

        c.__readData()
        return c

    @classmethod
    def fromCaptures(cls, captures):
        c = cls()
        c.path = captures[0].path
        c.basename = captures[0].basename
        c.name = captures[0].name
        #c.meta = Meta(c.__getMetaFile())

        c.sensorName = captures[0].sensorName
        c.num = captures[-1].num
        c.identifier = "{}".format(c.sensorName)

        c.count = 0
        c.t = []
        c.tTriggers = []
        c.yTriggers = []
        c.rawPos = []
        c.rawVel = []
        c.emaPos = []
        c.emaVel = []
        c.emaAcc = []
        ## XXX c.wavT = []
        ## XXX c.wavY = []
        ## XXX c.wavHullT = []
        ## XXX c.wavHullYh = []
        ## XXX c.wavHullYl = []
        ## XXX c.wavHullYd = []
        ## XXX c.wavHullTtrigg = []
        ## XXX c.wavHullYtrigg = []
        for capture in captures:
            c.count += capture.count
            c.t.extend(capture.t)
            c.tTriggers.extend(capture.tTriggers)
            c.yTriggers.extend(capture.yTriggers)
            c.rawPos.extend(capture.rawPos)
            c.rawVel.extend(capture.rawVel)
            c.emaPos.extend(capture.emaPos)
            c.emaVel.extend(capture.emaVel)
            c.emaAcc.extend(capture.emaAcc)
            ## XXX c.wavT.extend(capture.wavT)
            ## XXX c.wavY.extend(capture.wavY)
            ## XXX c.wavHullT.extend(capture.wavHullT)
            ## XXX c.wavHullYh.extend(capture.wavHullYh)
            ## XXX c.wavHullYl.extend(capture.wavHullYl)
            ## XXX c.wavHullYd.extend(capture.wavHullYd)
            ## XXX c.wavHullTtrigg.extend(capture.wavHullTtrigg)
            ## XXX c.wavHullYtrigg.extend(capture.wavHullYtrigg)
        return c

    def __getRawFile(self):
        return os.path.join(self.path, self.basename)

    def __getMetaFile(self):
        return "{}.meta".format(self.__getRawFile())

    def getPlotHtmlFile(self):
        return "{}.html".format(os.path.join(self.path, self.name))

    def getWavFile(self):
        return os.path.join(self.path, "{}.wav".format(self.meta.uniqueSessionId))

    def getIdentifier(self):
        return self.identifier

    def __readData(self):
        # Read data
        self.csv = pd.read_csv(self.__getRawFile(), names=['time', 'dt', 'value'])

        self.rawTime = self.csv['time'].values
        self.rawDt = self.csv['dt'].values
        self.rawSensorData = self.csv['value'].values

        # General information
        self.count = len(self.rawSensorData)
        #self.tStep = (self.meta.getElapsedNsMcu() / 1000000000) / self.count
        #if self.tStep < 4000:
        #    frac = int(0.004 / self.tStep)
        #    self.tStep *= frac
        #    self.rawSensorData = [self.rawSensorData[i] for i in range(0, self.count, frac)]
        #    self.count = len(self.rawSensorData)

        #self.tStepInv = self.count / (self.meta.getElapsedNsMcu() / 1000000000)

        #self.t0 = self.rawTime[0]
        #self.t = [(x - self.t0) / 1000 for x in self.csv['time'].values]
        self.t = [self.meta.getOverallOffsetSec() + i / 1000000 for i in self.rawTime]
        self.rawPos = self.rawSensorData
        self.rawPos = [-1.609864 - (-19.9053/7.83965)*(1 - np.exp(-7.83965*i)) for i in self.rawPos]
        self.rawVel = [0] + [(self.rawPos[i + 1] - self.rawPos[i]) * (1000000.0 / self.rawDt[i + 1]) for i in range(len(self.rawPos) - 1)]

        # Detect triggers
        self.triggers = []
        self.triggersStates = []
        self.tTriggers = []
        self.yTriggers = []
        logicState = LogicState()
        for i in range(len(self.rawDt)):
            logicState.nextState(self.rawTime[i], self.rawDt[i], self.rawSensorData[i])
            if logicState.changed:
                if logicState.pressed:
                    self.triggers += [(self.t[i], copy.deepcopy(logicState))]
                    self.tTriggers += [self.t[i] - 0.0000001, self.t[i]]
                    self.yTriggers += [0, logicState.pressVelocity]
                else:
                    self.tTriggers += [self.t[i] - 0.0000001, self.t[i]]
                    self.yTriggers += [logicState.pressVelocity, 0]

        ### Calculate pos and vel
        ##self.rawPos = self.rawSensorData
        ##self.rawVel = np.insert(np.diff(self.rawPos) * self.tStepInv, 0, 0)
        global aat
        aat = .0
        def accumTen(i):
            global aat
            aat = aat * .9 + i * .1
            return aat
        self.emaPos = [accumTen(i) for i in self.rawPos]
        #self.emaVel = np.insert(np.diff(self.emaPos) * self.tStepInv, 0, 0)
        self.emaVel = [0] + [(self.emaPos[i + 1] - self.emaPos[i]) * (1000000.0 / self.rawDt[i + 1]) for i in range(len(self.emaPos) - 1)]
        #self.emaAcc = [0] + [(self.emaVel[i + 1] - self.emaVel[i]) * (10000.0 / self.rawDt[i + 1]) for i in range(len(self.emaVel) - 1)]
        self.emaAcc = [0] + [(self.rawVel[i + 1] - self.rawVel[i]) * (10000.0 / self.rawDt[i + 1]) for i in range(len(self.rawVel) - 1)]
        global bat
        bat = .0
        def accumTen2(i):
            global bat
            bat = bat * .9 + i * .1
            return bat
        self.emaAcc = [accumTen2(i) for i in self.rawVel]
        ##global bbt
        ##bbt = .0
        ##def accumTen2(i):
        ##    global bbt
        ##    if i < bbt:
        ##        bbt = bbt * .7 + i * .3
        ##    else:
        ##        bbt = bbt * .9 + i * .1
        ##    return bbt
        ##self.emaVel = [accumTen2(i) for i in self.rawVel]
        ###self.smoothPos = signal.savgol_filter(self.rawPos, 153, 3)
        ###self.smoothVel = signal.savgol_filter(self.rawVel, 153, 3)

        ### Calculate time shift
        ##self.indexT0 = np.where(self.rawVel == np.amax(self.rawVel))[0][0]
        ##self.t0 = -self.csv['time'].values[self.indexT0]
        ##self.t = [(self.t0 + x) / 1000 for x in self.csv['time'].values]

        ### Calculate t0 based velocity
        ##self.t0Vel = [(e - self.rawPos[self.indexT0]) * 1000000 / (self.t[i] - self.t0) for i,e in enumerate(self.rawPos)]

        ## XXX   wavFile = self.getWavFile()
        ## XXX   (self.audioFs, self.audioData) = scipy.io.wavfile.read(wavFile)
        ## XXX   if self.audioData.shape[1] == 2:
        ## XXX       self.audioData = self.audioData[:,0]
        ## XXX   if self.audioData.dtype == np.int16:
        ## XXX       self.audioData = self.audioData / (2**(16-1))
        ## XXX   elif self.audioData.dtype == np.int32:
        ## XXX       self.audioData = self.audioData / (2**(32-1))
        ## XXX   self.audioDuration = len(self.audioData) / self.audioFs

        ## XXX   lowcut = keyFrequencies[self.sensorName] * (1.0 - maxKeyFreqDeviation)
        ## XXX   highcut = keyFrequencies[self.sensorName] * (1.0 + maxKeyFreqDeviation)
        ## XXX   #print("lowcut {}, highcut {}".format(lowcut, highcut))

        ## XXX   #self.audioData = butter_bandpass_filter(self.audioData, lowcut, highcut, self.audioFs)
        ## XXX   self.audioData = self.audioData[::28]
        ## XXX   self.audioFs = int(self.audioFs / 28)
        ## XXX   self.audioData = butter_bandpass_filter(self.audioData, lowcut, highcut, self.audioFs)

        ## XXX   recordOffset = 0.953 + 0.045 - 0.025
        ## XXX   #displayRange = (self.t[0], ccap.t[-1])
        ## XXX   #readRange = (recordOffset, recordOffset + (displayRange[1] - displayRange[0]))

        ## XXX   #first = int(readRange[0] * self.audioFs)
        ## XXX   #last = int(readRange[1] * self.audioFs)

        ## XXX   #self.wavT = np.linspace(displayRange[0], displayRange[1], num=(last - first))

        ## XXX   self.wavY = self.audioData
        ## XXX   #self.wavY = butter_bandpass_filter(self.audioData, lowcut, highcut, self.audioFs)
        ## XXX   #self.wavY = np.array(self.audioData)
        ## XXX   self.wavOffset = self.meta.getOverallOffsetSec() - recordOffset
        ## XXX   self.wavT = np.linspace(self.wavOffset, self.wavOffset + self.audioDuration, num=len(self.wavY))

        ## XXX   #maskedWavY = np.ma.masked_where(np.isfinite(self.wavY), self.wavY)
        ## XXX   #maskedWavT = np.ma.masked_where(np.ma.getmask(maskedWavY), self.wavT)
        ## XXX   #self.wavY = maskedWavY.compressed()
        ## XXX   #self.wavT = maskedWavT.compressed()

        ## XXX   #maskedWavY = np.ma.masked_where(np.absolute(self.wavY) < .001, self.wavY)
        ## XXX   #maskedWavT = np.ma.masked_where(np.ma.getmask(maskedWavY), self.wavT)
        ## XXX   #self.wavY = maskedWavY.compressed()
        ## XXX   #self.wavT = maskedWavT.compressed()

        ## XXX   ## get the maximum for buckets of 5 ms each
        ## XXX   #bucketEach = 0.005
        ## XXX   #buckets = int(len(self.wavY) / (bucketEach * self.audioFs))
        ## XXX   #split = np.array_split(self.wavY, buckets)
        ## XXX   #self.wavY = []
        ## XXX   #for i in split:
        ## XXX   #    self.wavY += [np.amax(i)]

        ## XXX   #self.wavY = np.amax(np.stack(split, axis=0), axis=1)
        ## XXX   #self.wavT = np.linspace(displayRange[0], displayRange[1], num=len(self.wavY))
        ## XXX   #self.wavY = 20 * np.log10(self.wavY)

        ## XXX   #wavD = np.diff(np.append(self.wavY, 0))
        ## XXX   #maskedWavY = np.ma.masked_where(np.abs(wavD) < .02, np.abs(self.wavY))
        ## XXX   #maskedWavT = np.ma.masked_where(np.ma.getmask(maskedWavY), self.wavT)
        ## XXX   #self.wavY = maskedWavY.compressed()
        ## XXX   #self.wavT = maskedWavT.compressed()

        ## XXX   #print("wav percentage: {}".format(100 * len(self.wavT) / (self.audioDuration * self.audioFs)))

        ## XXX   combineSamples=int(2.5 / keyFrequencies[self.sensorName] * self.audioFs)
        ## XXX   #print("combineSamples {}".format(combineSamples))

        ## XXX   self.wavHullT = []
        ## XXX   self.wavHullYh = []
        ## XXX   self.wavHullYl = []
        ## XXX   for i in range(combineSamples, len(self.wavT), combineSamples):
        ## XXX       self.wavHullT += [self.wavT[i - combineSamples // 2]]
        ## XXX       self.wavHullYh += [np.amax(self.wavY[i - combineSamples:i])]
        ## XXX       self.wavHullYl += [np.amin(self.wavY[i - combineSamples:i])]
        ## XXX   self.wavHullYd = np.abs(np.array(self.wavHullYh) - np.array(self.wavHullYl)) / 2

        ## XXX   #self.wavHullYd = 20 * np.log10(self.wavHullYd)
        ## XXX   #self.wavHullYd = signal.savgol_filter(self.wavHullYd, 53, 3)
        ## XXX   samplesPerSecond = len(self.wavHullYd) / self.audioDuration
        ## XXX   #peaks,_ = signal.find_peaks(self.wavHullYd, distance=0.1*samplesPerSecond, width=0.1*samplesPerSecond, height=-70)
        ## XXX   peaks,_ = signal.find_peaks(self.wavHullYd, distance=0.1*samplesPerSecond, width=6)
        ## XXX   #prominences = signal.peak_prominences(self.wavHullYd, peaks)[0]
        ## XXX   #self.wavHullTtrigg = np.take(self.wavHullT, peaks)
        ## XXX   #self.wavHullYtrigg = np.take(self.wavHullYd, peaks)
        ## XXX   self.wavHullTtrigg = np.take(self.wavHullT, peaks)
        ## XXX   self.wavHullYtrigg = np.take(self.wavHullYd, peaks)

        ## XXX   self.firstValid = max(self.wavT[0], self.meta.getOverallOffsetSec())
        ## XXX   self.lastValid = self.wavT[-1]

        ## XXX   # preform wav offset synchronization, by applying the averaging distance
        ## XXX   # between manual triggers and wav peaks (+desiredAttackTime).
        ## XXX   guessedOffset = 0
        ## XXX   guesses = 0
        ## XXX   for t,_ in self.triggers:
        ## XXX       searchRadius = .3
        ## XXX       b = max(self.firstValid, t - searchRadius)
        ## XXX       e = min(self.lastValid, t + searchRadius)
        ## XXX       if e - b < searchRadius:
        ## XXX           continue

        ## XXX       try:
        ## XXX           (trFrom, trTo) = findFromTo(b, e, self.wavHullTtrigg)
        ## XXX       except Exception:
        ## XXX           continue

        ## XXX       smallestDistance = searchRadius
        ## XXX       gO = 0
        ## XXX       for i in range(trFrom, trTo):
        ## XXX           distance = t - self.wavHullTtrigg[i]
        ## XXX           absd = np.abs(distance)
        ## XXX           if absd < smallestDistance:
        ## XXX               smallestDistance = absd
        ## XXX               gO = distance

        ## XXX       if smallestDistance < searchRadius:
        ## XXX           guessedOffset += gO
        ## XXX           guesses += 1



        ## XXX   if guesses > 0:
        ## XXX       #desiredAttackTime = .05
        ## XXX       desiredAttackTime = .0
        ## XXX       offsetCorrection = (guessedOffset / guesses) + desiredAttackTime
        ## XXX       #print("offsetCorrection {}".format(offsetCorrection))

        ## XXX       self.firstValid += offsetCorrection
        ## XXX       self.lastValid += offsetCorrection
        ## XXX       self.wavT += offsetCorrection
        ## XXX       self.wavHullT += offsetCorrection
        ## XXX       self.wavHullTtrigg += offsetCorrection


    def plotPos(self, fig):
        print("plotting position...")
        #fig.add_trace(go.Scattergl(
        #    name='{} pos'.format(self.getIdentifier()),
        #    x=self.t,
        #    y=self.smoothPos,
        #    yaxis=plotAxisPos,
        #))
        if includeRaw:
            fig.add_trace(go.Scattergl(
                name='{} raw pos'.format(self.getIdentifier()),
                x=self.t,
                y=self.rawPos,
                yaxis=plotAxisPosRaw,
            ))

    def plotVel(self, fig):
        print("plotting velocity...")
        #fig.add_trace(go.Scattergl(
        #    name='{} vel'.format(self.getIdentifier()),
        #    x=self.t,
        #    y=self.smoothVel,
        #    yaxis=plotAxisVel,
        #))
        #fig.add_trace(go.Scattergl(
        #    name='{} t0 vel'.format(self.getIdentifier()),
        #    x=self.t,
        #    y=self.t0Vel,
        #    yaxis=plotAxisVel,
        #))
        if includeRaw:
            #global aat
            #aat = .0
            #def accumTen(i):
            #    global aat
            #    aat = aat * .9 + i * .1
            #    #aat = aat * .999 + i * .001
            #    return aat
            #tendency = [accumTen(i) for i in self.rawPos]
            fig.add_trace(go.Scattergl(
                name='{} raw vel'.format(self.getIdentifier()),
                x=self.t,
                y=self.rawVel,
                yaxis=plotAxisVelRaw,
            ))
            fig.add_trace(go.Scattergl(
                name='{} pos ema'.format(self.getIdentifier()),
                x=self.t,
                y=self.emaPos,
                yaxis=plotAxisPosRaw,
            ))
            fig.add_trace(go.Scattergl(
                name='{} vel ema'.format(self.getIdentifier()),
                x=self.t,
                y=self.emaVel,
                yaxis=plotAxisVelRaw,
            ))
            fig.add_trace(go.Scattergl(
                name='{} acc ema'.format(self.getIdentifier()),
                x=self.t,
                y=self.emaAcc,
                yaxis=plotAxisVelRaw,
            ))

    def plotAudio(self, fig):
        print("plotting audio...")
        #fig.add_trace(go.Scattergl(
        #    name='{} wav'.format(self.getIdentifier()),
        #    x=self.wavT,
        #    y=self.wavY,
        #    yaxis=plotAxisWav,
        #))
        fig.add_trace(go.Scattergl(
            name='{} wav hull D'.format(self.getIdentifier()),
            x=self.wavHullT,
            y=self.wavHullYd,
            yaxis=plotAxisWav,
        ))
        wavHullTtrigg = np.array([[t-0.0000001,t,t+0.0000001] for t in self.wavHullTtrigg]).flatten()
        wavHullYtrigg = np.array([[0,v,0] for v in self.wavHullYtrigg]).flatten()
        fig.add_trace(go.Scattergl(
            name='{} wav trigg'.format(self.getIdentifier()),
            #x=self.wavHullT,
            #y=self.wavHullYl,
            x=wavHullTtrigg,
            y=wavHullYtrigg,
            yaxis=plotAxisWav,
        ))

    def plotTriggers(self, fig):
        print("plotting triggers...")
        fig.add_trace(go.Scattergl(
            name='{} triggers'.format(self.getIdentifier()),
            x=self.tTriggers,
            y=self.yTriggers,
            yaxis=plotAxisTriggers,
        ))
    #    if self.audioData is None:
    #        return

    #    recordOffset = 1.0 - 0.06

    #    t0 = self.t0 / 1000000
    #    mcuSampleLength = (self.meta.getElapsedNsMcu() / 1000000000)

    #    readRange = (recordOffset, recordOffset + mcuSampleLength)
    #    displayRange = (t0, t0 + mcuSampleLength)

    #    first = int(readRange[0] * self.audioFs)
    #    last = int(readRange[1] * self.audioFs)
    #    tWav = np.linspace(displayRange[0] * 1000, displayRange[1] * 1000, num=(last - first))

    #    lowcut = keyFrequencies[self.sensorName] * (1.0 - maxKeyFreqDeviation)
    #    highcut = keyFrequencies[self.sensorName] * (1.0 + maxKeyFreqDeviation)

    #    fig.add_trace(go.Scattergl(
    #        name='{} wav (l)'.format(self.getIdentifier()),
    #        x=tWav,
    #        y=butter_bandpass_filter(self.audioData[first:last,0], lowcut, highcut, self.audioFs),
    #        yaxis=plotAxisWav,
    #    ))

    #    fig.add_trace(go.Scattergl(
    #        name='{} wav (r)'.format(self.getIdentifier()),
    #        x=tWav,
    #        y=butter_bandpass_filter(self.audioData[first:last,1], lowcut, highcut, self.audioFs),
    #        yaxis=plotAxisWav,
    #    ))

    def plot(self, fig):
        self.plotPos(fig)
        self.plotVel(fig)
        ## XXX self.plotAudio(fig)
        self.plotTriggers(fig)
