#!/bin/bash

gcc -c -Wall -std=gnu99 -lm inertia_ride-SDL.c 
gcc -L/usr/lib/x86_64-linux-gnu -lSDL2 -o inertia_ride-SDL inertia_ride-SDL.o -lm && rm -rf inertia_ride-SDL.o
