#!/bin/bash

arecord -f cd -t wav -d 3 "$1/$2.wav"&
