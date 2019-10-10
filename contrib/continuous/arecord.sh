#!/bin/bash

arecord -f cd -t wav -d 30 -D default:CODEC "$1/$2.wav"&
