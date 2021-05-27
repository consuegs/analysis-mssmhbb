#!/bin/sh 
# $1 - SR, CR or VR

#Join root files corresponding to background MC samples:
samples_bkgMC=(QCD_HT100to200
QCD_HT200to300
QCD_HT300to500
QCD_HT500to700
QCD_HT700to1000
QCD_HT1000to1500
QCD_HT1500to2000
QCD_HT2000toInf 
QCD-BGenFilter_HT100to200
QCD-BGenFilter_HT200to300
QCD-BGenFilter_HT300to500
QCD-BGenFilter_HT500to700
QCD-BGenFilter_HT700to1000
QCD-BGenFilter_HT1000to1500
QCD-BGenFilter_HT1500to2000
QCD-BGenFilter_HT2000toInf 
QCD-bEnriched_HT100to200
QCD-bEnriched_HT200to300
QCD-bEnriched_HT300to500
QCD-bEnriched_HT500to700
QCD-bEnriched_HT700to1000
QCD-bEnriched_HT1000to1500
QCD-bEnriched_HT1500to2000
QCD-bEnriched_HT2000toInf 
)

l=1

while [ $l -le ${#samples_bkgMC[@]} ] 
do
    ./hadd.sh ${samples_bkgMC[$l]}-deep-$i-3j
      
    l=`expr $l + 1` 
done
