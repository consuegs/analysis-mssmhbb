#!/bin/sh
# $1 - SR, CR or VR
export PYTHONIOENCODING=utf-8

# This script resubmit jobs in failed status 


#Submit data samples:
samples_data=(JetHT_Run2017C
JetHT_Run2017D
JetHT_Run2017E
JetHT_Run2017F
)

j=1 

while [ $j -le ${#samples_data[@]} ] 
do
    echo "Checks status of jobs for data sample " ${samples_data[$j]}-deep-$1-3j 
    naf_submit.py --dir Condor_SimpleMssmHbbAnalysis_2017_${samples_data[$j]}-deep-$1-3j --status
      
    j=`expr $j + 1` 
done


#Submit signal MC samples:
for k in 300 350 400 450 500 600 700 800 900 1000 1200 1400 1600
do
    echo "Checks status of jobs for signal sample " mc-sig-${k}-NLO-deep-$1-3j
    naf_submit.py --dir Condor_SimpleMssmHbbAnalysis_2017_mc-sig-${k}-NLO-deep-$1-3j --status

done

<< 'MULTILINE-COMMENT'
#Submit background MC samples:
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
    echo "Checks status of jobs for background MC sample " ${samples_bkgMC[$l]}-deep-$1-3j
    naf_submit.py --dir Condor_SimpleMssmHbbAnalysis_2017_${samples_bkgMC[$l]}-deep-$1-3j --status

    l=`expr $l + 1` 
done
MULTILINE-COMMENT
