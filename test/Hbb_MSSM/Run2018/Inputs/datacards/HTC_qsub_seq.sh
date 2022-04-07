#!/bin/sh

for subrange in SR1
do

for i in 300 350

do

   cat > HTC_TheScript_${i}_${subrange}.sh <<EOF
source /cvmfs/cms.cern.ch/cmsset_default.sh
export SCRAM_ARCH=slc7_amd64_gcc700
cd ${CMSSW_BASE}/src
cmsenv
cd -	
	
echo "Starting combine ${subrange} ${i}"

echo "Expected/Observed Limits"	
combine -M AsymptoticLimits -d hbb_mbb${i}_${subrange}_mssm-13TeV.root --setParameterRanges r=-1,1 --setParameters mask_SR=0,r=0 --cminDefaultMinimizerStrategy 0 -n Hbb_${subrange} -m ${i} -v 5 

EOF
   chmod u+x HTC_TheScript_${i}_${subrange}.sh
   ./HTC_qsub.sh HTC_TheScript_${i}_${subrange}.sh HTC_TheScript_${subrange}

done

done

for subrange in SR2
do

for i in 400 500 600 

do

   cat > HTC_TheScript_${i}_${subrange}.sh <<EOF
source /cvmfs/cms.cern.ch/cmsset_default.sh
export SCRAM_ARCH=slc7_amd64_gcc700
cd ${CMSSW_BASE}/src
cmsenv
cd -	
	
echo "Starting combine ${subrange} ${i}"

echo "Expected/Observed Limits"	
combine -M AsymptoticLimits -d hbb_mbb${i}_${subrange}_mssm-13TeV.root --setParameterRanges r=-1,1 --setParameters mask_SR=0,r=0 --cminDefaultMinimizerStrategy 0 -n Hbb_${subrange} -m ${i} -v 5 

EOF
   chmod u+x HTC_TheScript_${i}_${subrange}.sh
   ./HTC_qsub.sh HTC_TheScript_${i}_${subrange}.sh HTC_TheScript_${i}_${subrange}

done

done


for subrange in SR3
do
	
for i in 700 800 900 1000

do

   cat > HTC_TheScript_${i}_${subrange}.sh <<EOF
source /cvmfs/cms.cern.ch/cmsset_default.sh
export SCRAM_ARCH=slc7_amd64_gcc700
cd ${CMSSW_BASE}/src
cmsenv
cd -	
	
echo "Starting combine ${subrange} ${i}"

echo "Expected/Observed Limits"	
combine -M AsymptoticLimits -d hbb_mbb${i}_${subrange}_mssm-13TeV.root --setParameterRanges r=-1,1 --setParameters mask_SR=0,r=0 --cminDefaultMinimizerStrategy 0 -n Hbb_${subrange} -m ${i} -v 5 

EOF
   chmod u+x HTC_TheScript_${i}_${subrange}.sh
  ./HTC_qsub.sh HTC_TheScript_${i}_${subrange}.sh HTC_TheScript_${i}_${subrange}

done

done


for subrange in SR4
do

for i in 1200 1400 1600 1800
do

   cat > HTC_TheScript_${i}_${subrange}.sh <<EOF
source /cvmfs/cms.cern.ch/cmsset_default.sh
export SCRAM_ARCH=slc7_amd64_gcc700
cd ${CMSSW_BASE}/src
cmsenv
cd -	
	
echo "Starting combine ${subrange} ${i}"

echo "Expected/Observed Limits"	
combine -M AsymptoticLimits -d hbb_mbb${i}_${subrange}_mssm-13TeV.root --setParameterRanges r=-1,1 --setParameters mask_SR=0,r=0 --cminDefaultMinimizerStrategy 0 -n Hbb_${subrange} -m ${i} -v 5 

EOF
   chmod u+x HTC_TheScript_${i}_${subrange}.sh
   ./HTC_qsub.sh HTC_TheScript_${i}_${subrange}.sh HTC_TheScript_${i}_${subrange}

done

done
