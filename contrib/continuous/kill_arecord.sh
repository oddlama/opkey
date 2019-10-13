#!/bin/bash

killall arecord
sox --ignore-length "$1/$2.wav.broken" "$1/$2.wav"&
