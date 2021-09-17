#!/bin/sh 
# $1 - SR, CR or VR

#Join root files corresponding to data samples:
for i in C D E F
do
./hadd.sh BTagCSV_Run2017${i}-deep-$1-3j

done

if [ -e BTagCSV_Run2017-deep-$1-3j.root  ]
then
    rm BTagCSV_Run2017-deep-$1-3j.root
fi

hadd BTagCSV_Run2017-deep-$1-3j.root BTagCSV_Run2017C-deep-$1-3j.root BTagCSV_Run2017D-deep-$1-3j.root BTagCSV_Run2017E-deep-$1-3j.root BTagCSV_Run2017F-deep-$1-3j.root


