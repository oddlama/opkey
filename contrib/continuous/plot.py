#!/usr/bin/env python3

import sys
from parse import *

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("usage: plot.py <directory|file.raw>")
        sys.exit(1)

    (path, fileBasenames) = getInputFiles(sys.argv[1])

    captures = []
    for file in fileBasenames:
        try:
            print("reading {}".format(file))
            captures.append(Capture.fromFile(path, file))
        except IOError as e:
            print("Error while loading Capture:")
            print(e)
            continue

    print("combining...")
    ccap = Capture.fromCaptures(captures)
    fig = go.Figure()
    ccap.plot(fig)
    print("layouting...")
    setFigureLayout(fig)
    print("plotting...")
    plotly.offline.plot(fig, filename=ccap.getPlotHtmlFile(), auto_open=False)
    print("done")
