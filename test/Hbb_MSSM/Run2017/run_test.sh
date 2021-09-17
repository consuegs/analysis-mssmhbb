#!/bin/sh 
export PYTHONIOENCODING=utf-8

: '
#submit test with 100 events to condor
#data
echo "Submitting to condor for testing 100 events, BTagCSV_Run2017C-deep-CR-3j data"
naf_submit.py --exe SimpleMssmHbbAnalysis_2017 --config BTagCSV_Run2017C-deep-CR-3j_test.cfg --nfiles 1

#signal MC	
echo "Submitting to condor for testing 100 events, mc-sig-300-NLO-deep-SR-3j"
naf_submit.py --exe SimpleMssmHbbAnalysis_2017 --config mc-sig-300-NLO-deep-SR-3j_test.cfg --nfiles 1

#background MC
echo "Submitting to condor for testing 100 events, QCD_HT100to200-deep-CR-3j"
naf_submit.py --exe SimpleMssmHbbAnalysis_2017 --config QCD_HT100to200-deep-CR-3j_test.cfg --nfiles 1
'

#local test with 100 events
#data
echo "Running locally for testing on 100 events, BTagCSV_Run2017C-deep-CR-3j data"
SimpleMssmHbbAnalysis_2017 -c BTagCSV_Run2017C-deep-CR-3j_test.cfg 

#signal MC	
echo "Running locally for testing on 100 events, mc-sig-300-NLO-deep-SR-3j"
SimpleMssmHbbAnalysis_2017 -c mc-sig-300-NLO-deep-SR-3j_test.cfg 


#background MC
echo "Running locally for testing on 100 events, QCD_HT100to200-deep-CR-3j"
SimpleMssmHbbAnalysis_2017 -c QCD_HT100to200-deep-CR-3j_test.cfg 
