#!/bin/sh 
# $1 - SR, CR or VR

#Join root files corresponding to signal MC samples:
for i in 300 350 400 450 500 600 700 800 900 1000 1200 1400 1600
do
./hadd.sh mc-sig-${i}-NLO-deep-$1-3j

done


