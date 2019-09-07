#!/usr/bin/env python3

import pandas as pd
import plotly.graph_objects as go
from scipy import signal

data = pd.read_csv("out/sensor_C6_0", names=["time","value"])

fig = go.Figure()
fig.add_trace(go.Scattergl(
    name='Value',
    x=data.time,
    y=data.value
))
fig.add_trace(go.Scattergl(
    name='1st derivative',
    x=data.time,
    y=signal.savgol_filter(data.value, 153, 3, deriv=1),
    yaxis="y2",
))
fig.add_trace(go.Scattergl(
    name='2nd derivative',
    x=data.time,
    y=signal.savgol_filter(data.value, 153, 3, deriv=2),
    yaxis="y3",
))
#fig.add_trace(go.Scattergl(
#    name='Delta',
#    mode='lines',
#    x=data.time,
#    y=diff.value,
#    yaxis="y2",
#    line=dict(shape='spline')
#))
fig.update_traces(mode='lines')
fig.update_layout(
    yaxis=dict(
        title="Axis1",
        anchor="x",
        overlaying="y",
        side="left"
        ),
    yaxis2=dict(
        title="Axis2",
        anchor="x",
        overlaying="y",
        side="right"
        ),
    yaxis3=dict(
        title="Axis3",
        anchor="x",
        overlaying="y",
        side="right"
        )
    )
fig.update_layout(
    template='plotly_dark',
    title="C6"
    )
#fig.update_yaxes(type="log")
fig.show()
