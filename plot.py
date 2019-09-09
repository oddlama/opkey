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
            domain=[.04,.96] if includeRaw else [0.0, 1.0],
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
                position=1.0,
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

        range = (0.9, 1.0 + (self.meta.getElapsedNsMcu() / 1000000000))
        offset = 1.0
        first = int(range[0] * self.audioFs)
        last = int(range[1] * self.audioFs)
        tWav = np.linspace((range[0] - offset) * 1000, (range[1] - offset) * 1000, num=(last - first))

        def running_mean(x, N):
            cumsum = np.cumsum(np.insert(x, 0, 0))
            return (cumsum[N:] - cumsum[:-N]) / float(N)

        fig.add_trace(go.Scattergl(
            name='{} wav (l)'.format(self.getIdentifier()),
            x=tWav,
            y=running_mean(np.absolute(self.audioData[first:last,0]), 200),
            yaxis=plotAxisWav,
        ))

        fig.add_trace(go.Scattergl(
            name='{} wav (r)'.format(self.getIdentifier()),
            x=tWav,
            y=running_mean(np.absolute(self.audioData[first:last,1]), 200),
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
