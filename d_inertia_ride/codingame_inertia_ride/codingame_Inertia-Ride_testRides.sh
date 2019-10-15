#!/bin/bash

echo "-----------------------------------------------------------"

for ride in $(ls ../rides | grep -E "^(ride0)([[:digit:]]?).*$")
do 
	echo -e "$ride\n"; 
	echo -e "$(cat ../rides/$ride)\n";
	echo -e "Position Finale : $(cat ../rides/$ride | ./codingame_Inertia-Ride)\n"; 
	echo -e "-----------------------------------------------------------"
done 

