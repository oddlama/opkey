#!/bin/bash

arecord -f cd -t wav -D default:CODEC "$1/$2.wav.broken"&
