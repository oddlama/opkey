#!/usr/bin/env python3

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

# Config
createCombinedFigure=False
maxSensorValue = 4096
includeRaw=True
combinedFilename="combined.html"

# Constants (DONT CHANGE!)
plotAxisPos = "y"
plotAxisPosRaw = "y3"
plotAxisVel = "y2"
plotAxisVelRaw = "y4"
plotAxisWav = "y5"

maxKeyFreqDeviation = 0.05
keyFrequencies = {
    'A0'    : 27.50000, 'A#0'   : 29.13524, 'B0'    : 30.86771, 'C1'    : 32.70320,
    'C#1'   : 34.64783, 'D1'    : 36.70810, 'D#1'   : 38.89087, 'E1'    : 41.20344,
    'F1'    : 43.65353, 'F#1'   : 46.24930, 'G1'    : 48.99943, 'G#1'   : 51.91309,
    'A1'    : 55.00000, 'A#1'   : 58.27047, 'B1'    : 61.73541, 'C2'    : 65.40639,
    'C#2'   : 69.29566, 'D2'    : 73.41619, 'D#2'   : 77.78175, 'E2'    : 82.40689,
    'F2'    : 87.30706, 'F#2'   : 92.49861, 'G2'    : 97.99886, 'G#2'   : 103.8262,
    'A2'    : 110.0000, 'A#2'   : 116.5409, 'B2'    : 123.4708, 'C3'    : 130.8128,
    'C#3'   : 138.5913, 'D3'    : 146.8324, 'D#3'   : 155.5635, 'E3'    : 164.8138,
    'F3'    : 174.6141, 'F#3'   : 184.9972, 'G3'    : 195.9977, 'G#3'   : 207.6523,
    'A3'    : 220.0000, 'A#3'   : 233.0819, 'B3'    : 246.9417, 'C4'    : 261.6256,
    'C#4'   : 277.1826, 'D4'    : 293.6648, 'D#4'   : 311.1270, 'E4'    : 329.6276,
    'F4'    : 349.2282, 'F#4'   : 369.9944, 'G4'    : 391.9954, 'G#4'   : 415.3047,
    'A4'    : 440.0000, 'A#4'   : 466.1638, 'B4'    : 493.8833, 'C5'    : 523.2511,
    'C#5'   : 554.3653, 'D5'    : 587.3295, 'D#5'   : 622.2540, 'E5'    : 659.2551,
    'F5'    : 698.4565, 'F#5'   : 739.9888, 'G5'    : 783.9909, 'G#5'   : 830.6094,
    'A5'    : 880.0000, 'A#5'   : 932.3275, 'B5'    : 987.7666, 'C6'    : 1046.502,
    'C#6'   : 1108.731, 'D6'    : 1174.659, 'D#6'   : 1244.508, 'E6'    : 1318.510,
    'F6'    : 1396.913, 'F#6'   : 1479.978, 'G6'    : 1567.982, 'G#6'   : 1661.219,
    'A6'    : 1760.000, 'A#6'   : 1864.655, 'B6'    : 1975.533, 'C7'    : 2093.005,
    'C#7'   : 2217.461, 'D7'    : 2349.318, 'D#7'   : 2489.016, 'E7'    : 2637.020,
    'F7'    : 2793.826, 'F#7'   : 2959.955, 'G7'    : 3135.963, 'G#7'   : 3322.438,
    'A7'    : 3520.000, 'A#7'   : 3729.310, 'B7'    : 3951.066, 'C8'    : 4186.009,
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
            title="Time (ms)",
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

        if len(content) != 4:
            raise IOError("Invalid meta content length")

        self.uniqueSessionId = int(content[0])
        self.hostBegin = int(content[1])
        self.hostEnd = int(content[2])
        self.hostElapsed = self.hostEnd - self.hostBegin
        self.mcuElapsed = int(content[3])

    def getUniqueSessionId(self):
        return self.uniqueSessionId

    def getBeginNsHost(self):
        return self.hostBegin

    def getEndNsHost(self):
        return self.hostEnd

    def getElapsedNsHost(self):
        return self.hostElapsed

    def getElapsedNsMcu(self):
        return self.mcuElapsed

class Capture:
    def __init__(self, path, basename):
        self.path = path
        self.basename = basename
        self.name = os.path.splitext(basename)[0]
        self.meta = Meta(self.__getMetaFile())

        tokens = self.name.split('_')
        self.sensorName = tokens[1]
        self.num = tokens[2]
        self.identifier = "{}, #{}".format(self.sensorName, self.num)

        self.__readData()

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
        self.csv = pd.read_csv(self.__getRawFile(), names=['time','value'])
        self.rawSensorData = self.csv['value'].values

        # General information
        self.count = len(self.rawSensorData)
        self.tStep = (self.meta.getElapsedNsMcu() / 1000000000) / self.count
        self.tStepInv = self.count / (self.meta.getElapsedNsMcu() / 1000000000)

        # Calculate pos and vel
        self.rawPos = [math.sqrt(i / maxSensorValue) for i in self.rawSensorData]
        self.rawVel = np.diff(self.rawPos) * self.tStepInv
        self.smoothPos = signal.savgol_filter(self.rawPos, 153, 3)
        self.smoothVel = signal.savgol_filter(self.rawVel, 153, 3)

        # Calculate time shift
        self.indexT0 = np.where(self.rawVel == np.amax(self.rawVel))[0][0]
        self.t0 = -self.csv['time'].values[self.indexT0]
        self.t = [(self.t0 + x) / 1000 for x in self.csv['time'].values]

        # Load wav if available
        wavFile = self.getWavFile()
        if os.path.exists(wavFile):
            (self.audioFs, self.audioData) = scipy.io.wavfile.read(wavFile)
        else:
            (self.audioFs, self.audioData) = (None, None)

    def plotPos(self, fig):
        fig.add_trace(go.Scattergl(
            name='{} pos'.format(self.getIdentifier()),
            x=self.t,
            y=self.smoothPos,
            yaxis=plotAxisPos,
        ))
        if includeRaw:
            fig.add_trace(go.Scattergl(
                name='{} raw pos'.format(self.getIdentifier()),
                x=self.t,
                y=self.rawPos,
                yaxis=plotAxisPosRaw,
            ))

    def plotVel(self, fig):
        fig.add_trace(go.Scattergl(
            name='{} vel'.format(self.getIdentifier()),
            x=self.t,
            y=self.smoothVel,
            yaxis=plotAxisVel,
        ))
        if includeRaw:
            fig.add_trace(go.Scattergl(
                name='{} raw vel'.format(self.getIdentifier()),
                x=self.t,
                y=self.rawVel,
                yaxis=plotAxisVelRaw,
            ))

    def plotAudio(self, fig):
        if self.audioData is None:
            return

        recordOffset = 1.0 - 0.06

        t0 = self.t0 / 1000000
        mcuSampleLength = (self.meta.getElapsedNsMcu() / 1000000000)

        readRange = (recordOffset, recordOffset + mcuSampleLength)
        displayRange = (t0, t0 + mcuSampleLength)

        first = int(readRange[0] * self.audioFs)
        last = int(readRange[1] * self.audioFs)
        tWav = np.linspace(displayRange[0] * 1000, displayRange[1] * 1000, num=(last - first))

        lowcut = keyFrequencies[self.sensorName] * (1.0 - maxKeyFreqDeviation)
        highcut = keyFrequencies[self.sensorName] * (1.0 + maxKeyFreqDeviation)

        fig.add_trace(go.Scattergl(
            name='{} wav (l)'.format(self.getIdentifier()),
            x=tWav,
            y=butter_bandpass_filter(self.audioData[first:last,0], lowcut, highcut, self.audioFs),
            yaxis=plotAxisWav,
        ))

        fig.add_trace(go.Scattergl(
            name='{} wav (r)'.format(self.getIdentifier()),
            x=tWav,
            y=butter_bandpass_filter(self.audioData[first:last,1], lowcut, highcut, self.audioFs),
            yaxis=plotAxisWav,
        ))

    def plot(self, fig):
        self.plotPos(fig)
        self.plotVel(fig)
        self.plotAudio(fig)

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("usage: plot.py <directory|file.raw>")
        sys.exit(1)

    (path, fileBasenames) = getInputFiles(sys.argv[1])
    combinedFig = go.Figure() if createCombinedFigure else None
    autoOpen = (len(fileBasenames) == 1)

    for file in fileBasenames:
        try:
            capture = Capture(path, file)
        except IOError as e:
            print("Error while loading Capture:")
            print(e)
            continue

        print("{} [wav: {}]".format(capture.getIdentifier(), capture.audioData is not None))
        singleFig = go.Figure()

        capture.plot(singleFig)
        if combinedFig is not None:
            capture.plot(combinedFig)

        setFigureLayout(singleFig)
        plotly.offline.plot(singleFig, filename=capture.getPlotHtmlFile(), auto_open=autoOpen)

    if combinedFig is not None:
        print("[combined]")
        setFigureLayout(combinedFig)
        plotly.offline.plot(combinedFig, filename=os.path.join(path, combinedFilename), auto_open=False)
