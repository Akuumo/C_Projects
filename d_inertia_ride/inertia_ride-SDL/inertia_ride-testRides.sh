#!/bin/bash

echo "-----------------------------------------------------------"

for ride in $(ls ../rides | grep -E "^(ride0)([[:digit:]]?).*$")
do 
	echo -e "$ride\n"; 
	echo -e "$(cat ../rides/$ride | ./inertia_ride-SDL)\n"; 
	echo -e "-----------------------------------------------------------\n"
done 

