#!/bin/sh
# $1 - SR, CR or VR
export PYTHONIOENCODING=utf-8

#Submit signal MC samples (671 jobs each region):
for k in 300 350 400 450 500 600 700 800 900 1000 1200 1400 1600
do
    echo "Submitting jobs for signal sample" mc-sig-${k}-NLO-deep-$1-3j
    naf_submit.py --exe SimpleMssmHbbAnalysis_2017 --config mc-sig-${k}-NLO-deep-$1-3j.cfg --nfiles 5

done

