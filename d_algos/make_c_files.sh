#!/bin/bash

for c_file_path in $(ls C/*.c); 
do
	c_file=$(echo $c_file_path | cut -d/ -f2) 
	file=$(echo $c_file | cut -d. -f1) 
	
	echo "gcc -c -Wall -std=gnu99 -lm ./C/$file.c"
	echo "gcc -L/usr/lib/x86_64-linux-gnu -lSDL2 -o ./exe/$file $file.o -lm && rm -rf $file.o"

	gcc -c -Wall -std=gnu99 -lm ./C/$file.c
	gcc -L/usr/lib/x86_64-linux-gnu -lSDL2 -o ./exe/$file $file.o -lm && rm -rf $file.o
done 
