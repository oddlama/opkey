#!/usr/bin/env python3

import sys
from parse import *
import pickle
import pandas as pd

secondsBeforeTrigger = 0.1
secondsAfterTrigger = 0.01

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("usage: extract_data.py <directory|file.raw> <extract_dir>")
        sys.exit(1)

    (path, fileBasenames) = getInputFiles(sys.argv[1])
    extractDir = sys.argv[2]
    if not os.path.exists(extractDir):
        os.makedirs(extractDir)

    captures = []
    extractIdx = 0
    invalidTriggers = 0
    audioPeaks = []
    for file in fileBasenames:
        usedPeaks = set()
        try:
            print("reading {}".format(file))
            cap = Capture.fromFile(path, file)

            for t,state in cap.triggers:
                # find wav peak for this trigger
                searchBefore = .03
                searchAfter = .06
                b = max(cap.firstValid, t - searchBefore)
                e = min(cap.lastValid, t + searchAfter)
                if e - b < searchAfter:
                    continue

                try:
                    (trFrom, trTo) = findFromTo(b, e, cap.wavHullTtrigg)
                except Exception:
                    continue

                smallestDistance = max(searchBefore, searchAfter)
                peak = -1
                for i in range(trFrom, trTo):
                    distance = t - cap.wavHullTtrigg[i]
                    absd = np.abs(distance)
                    if absd < smallestDistance and i not in usedPeaks:
                        smallestDistance = absd
                        peak = i

                usedPeaks.add(peak)
                if peak == -1:
                    try:
                        (wavFrom, wavTo) = findFromTo(b, e, cap.wavT)
                    except Exception:
                        continue
                    if np.sum(cap.wavHullYd[wavFrom:wavTo]) > 0.01:
                        invalidTriggers += 1
                    audioPeak = 0.0
                else:
                    audioPeak = cap.wavHullYtrigg[peak]

                b = max(cap.firstValid, t - secondsBeforeTrigger)
                e = min(cap.lastValid, t + secondsAfterTrigger)
                if e - b < secondsBeforeTrigger:
                    continue
                try:
                    (rawFrom, rawTo) = findFromTo(b, e, cap.t)
                except Exception:
                    continue

                t0 = cap.t[rawFrom]
                t = [int((x - t0) * 1000000) for x in cap.t[rawFrom:rawTo]]
                pos = cap.rawPos[rawFrom:rawTo]
                vel = cap.rawVel[rawFrom:rawTo]
                audioPeaks += [audioPeak]
                data = {
                    't': t,
                    'pos': pos,
                    'vel': vel,
                    'triggerTime': t - t0,
                    'audioPeak': audioPeak,
                    'logicState': state,
                }

                # Store data (serialize)
                with open(os.path.join(extractDir, '{}.pickle'.format(extractIdx)), 'wb') as handle:
                    pickle.dump(data, handle, protocol=pickle.HIGHEST_PROTOCOL)
                extractIdx += 1

                #fig = go.Figure()
                #fig.add_trace(go.Scattergl(
                #    name='raw pos',
                #    x=cap.t[rawFrom:rawTo],
                #    y=pos,
                #    yaxis=plotAxisPosRaw,
                #))
                #fig.add_trace(go.Scattergl(
                #    name='raw vel',
                #    x=cap.t[rawFrom:rawTo],
                #    y=vel,
                #    yaxis=plotAxisVelRaw,
                #))
                #fig.add_trace(go.Scattergl(
                #    name='desired',
                #    x=[cap.t[rawFrom], cap.t[rawTo]],
                #    y=[desiredVel, desiredVel],
                #    yaxis=plotAxisWav,
                #))

                ##(wavFrom, wavTo) = findFromTo(b, e, cap.wavHullT)
                ##wavHullYh = cap.wavHullYh[wavFrom:wavTo]
                ##wavHullYl = cap.wavHullYl[wavFrom:wavTo]
                ##wavHullYd = np.abs(np.array(wavHullYh) - np.array(wavHullYl))
                ##fig.add_trace(go.Scattergl(
                ##    name='hull h',
                ##    x=cap.wavHullT[wavFrom:wavTo],
                ##    y=wavHullYh,
                ##    yaxis=plotAxisWav,
                ##))
                ##fig.add_trace(go.Scattergl(
                ##    name='hull l',
                ##    x=cap.wavHullT[wavFrom:wavTo],
                ##    y=wavHullYl,
                ##    yaxis=plotAxisWav,
                ##))
                ##fig.add_trace(go.Scattergl(
                ##    name='hull d',
                ##    x=cap.wavHullT[wavFrom:wavTo],
                ##    y=wavHullYd,
                ##    yaxis=plotAxisWav,
                ##))
                #setFigureLayout(fig)
                #plotly.offline.plot(fig, filename='/tmp/efafrrga.html', auto_open=True)
                #wavHullYh = cap.wavHullYh[b:e]
                #wavHullYl = cap.wavHullYl[b:e]
        except IOError as e:
            print("Error while loading Capture:")
            print(e)
            continue

    # save meta info
    meta = {
        'audioPeaks': audioPeaks,
    }
    pd.DataFrame(meta).to_csv(os.path.join(extractDir, '.meta'), index=None)
    print("extracted {} samples, and skipped {} invalid triggers".format(extractIdx, invalidTriggers))
