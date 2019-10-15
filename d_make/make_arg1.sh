#!/bin/bash

gcc -c -Wall -std=gnu99 -lm $1.c 2>/dev/null
gcc -L/usr/lib/x86_64-linux-gnu -lSDL2 -o $1 $1.o -lm && rm -rf $1.o 

