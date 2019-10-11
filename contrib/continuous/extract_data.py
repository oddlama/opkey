#!/usr/bin/env python3

import sys
from parse import *

secondsBeforeTrigger = 0.100
secondsAfterTrigger = 0.100

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


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("usage: extract_data.py <directory|file.raw>")
        sys.exit(1)

    (path, fileBasenames) = getInputFiles(sys.argv[1])

    captures = []
    for file in fileBasenames:
        try:
            print("reading {}".format(file))
            cap = Capture.fromFile(path, file)

            firstValid = max(cap.wavT[0], cap.meta.getOverallOffsetSec())
            lastValid = cap.wavT[-1]

            for t,_ in cap.triggers:
                b = t - secondsBeforeTrigger
                e = t + secondsAfterTrigger
                if b < firstValid or e > lastValid:
                    continue
                (rawFrom, rawTo) = findFromTo(b, e, cap.t)
                #print(b, e)
                #print(rawFrom, rawTo)
                #print(cap.t[rawFrom], cap.t[rawTo])

                pos = cap.rawPos[rawFrom:rawTo]
                vel = cap.rawVel[rawFrom:rawTo]
                fig = go.Figure()
                fig.add_trace(go.Scattergl(
                    name='raw pos',
                    x=cap.t[rawFrom:rawTo],
                    y=pos,
                    yaxis=plotAxisPosRaw,
                ))
                fig.add_trace(go.Scattergl(
                    name='raw vel',
                    x=cap.t[rawFrom:rawTo],
                    y=vel,
                    yaxis=plotAxisVelRaw,
                ))

                (wavFrom, wavTo) = findFromTo(b, e, cap.wavHullTh)
                wavHullYh = cap.wavHullYh[wavFrom:wavTo]
                wavHullYl = cap.wavHullYl[wavFrom:wavTo]
                wavHullYd = np.abs(np.array(wavHullYh) - np.array(wavHullYl))
                fig.add_trace(go.Scattergl(
                    name='hull h',
                    x=cap.wavHullTh[wavFrom:wavTo],
                    y=wavHullYh,
                    yaxis=plotAxisWav,
                ))
                fig.add_trace(go.Scattergl(
                    name='hull l',
                    x=cap.wavHullTh[wavFrom:wavTo],
                    y=wavHullYl,
                    yaxis=plotAxisWav,
                ))
                fig.add_trace(go.Scattergl(
                    name='hull d',
                    x=cap.wavHullTh[wavFrom:wavTo],
                    y=wavHullYd,
                    yaxis=plotAxisWav,
                ))
                setFigureLayout(fig)
                plotly.offline.plot(fig, filename='/tmp/efafrrga.html', auto_open=True)
                break
                #wavHullYh = cap.wavHullYh[b:e]
                #wavHullYl = cap.wavHullYl[b:e]
        except IOError as e:
            print("Error while loading Capture:")
            print(e)
            continue
