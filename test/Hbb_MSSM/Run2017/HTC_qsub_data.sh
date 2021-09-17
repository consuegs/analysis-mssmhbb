#!/bin/sh 
# $1 - SR, CR or VR
export PYTHONIOENCODING=utf-8

#Submit data samples:
samples_data=(BTagCSV_Run2017C
#BTagCSV_Run2017D
#BTagCSV_Run2017E
#BTagCSV_Run2017F
)

j=1

while [ $j -le ${#samples_data[@]} ] 
do
    echo "Submitting jobs for data sample" ${samples_data[$j]}-deep-$1-3j 
    naf_submit.py --exe SimpleMssmHbbAnalysis_2017 --config ${samples_data[$j]}-deep-$1-3j.cfg --nfiles 5
      
    j=`expr $j + 1` 
done
