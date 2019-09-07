#!/usr/bin/env python3

import math
import numpy as np
import pandas as pd
import plotly.graph_objects as go
from scipy import signal

def butter_lowpass(cutoff, fs, order):
    nyq = 0.5 * fs
    normal_cutoff = cutoff / nyq
    b, a = signal.butter(order, normal_cutoff, btype='low', analog=False)
    return b, a

def butter_lowpass_filter(data, cutoff, fs, order=5):
    b, a = butter_lowpass(cutoff, fs, order=order)
    y = signal.lfilter(b, a, data)
    return y

files = [
    "sensor_C6_0",
    "sensor_C6_1",
]

fig = go.Figure()
for file in files:
    data = pd.read_csv("out/{}".format(file), names=["time","value"])
    cutoff=50
    fs=1000000/(data['time'].iloc[-1]/len(data['time']))

    tokens=file.split('_')
    sensor=tokens[1]
    num=tokens[2]
    identifier="{}, #{}".format(sensor, num)

    d = [math.sqrt(i) for i in data['value'].values]
    deriv0 = signal.savgol_filter(d, 153, 3, deriv=0)
    deriv1 = signal.savgol_filter(d, 153, 3, deriv=1)

    iMaxD1 = np.where(deriv1 == np.amax(deriv1))[0][0]
    t0 = -data['time'].values[iMaxD1]
    t = [(t0 + x) / 1000 for x in data['time'].values]

    fig.add_trace(go.Scattergl(
        name='{} pos'.format(identifier),
        x=t,
        y=deriv0,
    ))
    fig.add_trace(go.Scattergl(
        name='{} vel'.format(identifier),
        x=t,
        y=deriv1,
        yaxis="y2",
    ))

fig.update_traces(mode='lines')
fig.update_layout(
    xaxis=dict(
        title="Time (ms)",
        ),
    yaxis=dict(
        title="Position",
        anchor="x",
        overlaying="y",
        side="left"
        ),
    yaxis2=dict(
        title="Velocity",
        anchor="x",
        overlaying="y",
        side="right"
        ),
    )
fig.update_layout(
    template='plotly_dark',
    title="Sensor Plot"
    )
#fig.update_yaxes(type="log")
fig.show()
