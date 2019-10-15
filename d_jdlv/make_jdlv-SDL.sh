#!/bin/bash

gcc -c -Wall -std=gnu99 -lm jdlv-SDL.c 
gcc -L/usr/lib/x86_64-linux-gnu -lSDL2 -o jdlv-SDL jdlv-SDL.o -lm && rm -rf jdlv-SDL.o
