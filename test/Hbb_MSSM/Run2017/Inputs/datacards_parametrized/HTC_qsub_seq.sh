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
combine -M AsymptoticLimits -d hbb_mbb${i}_${subrange}_mssm-13TeV.root --setParameters mask_SR=0,r=0,bernstein_coefficient_00=2.28831,bernstein_coefficient_01=0.000193003,bernstein_coefficient_02=24.9699,bernstein_coefficient_03=0.799356,bernstein_coefficient_04=6.15331,bernstein_coefficient_05=2.15559,bernstein_coefficient_06=1.84779,turnon_novoeff=228.7,slope_novoeff=0.02 --freezeParameters bernstein_coefficient_02 --cminDefaultMinimizerStrategy 0 -n Hbb_${subrange} --setParameterRanges r=-20,20:bernstein_coefficient_00=0,5:bernstein_coefficient_01=-1,1:bernstein_coefficient_02=20,30:bernstein_coefficient_03=-2,2:bernstein_coefficient_04=2,10:bernstein_coefficient_05=0,10:bernstein_coefficient_06=0,5:turnon_novoeff=200,300:slope_novoeff=0,0.1:slopelinTF=-3e-4,3e-4:steepnessTF=0.0001,0.05:offsetTF=-250,250 -m ${i} -v 5 

EOF
   chmod u+x HTC_TheScript_${i}_${subrange}.sh
   ./HTC_qsub.sh HTC_TheScript_${i}_${subrange}.sh HTC_TheScript_${subrange}

done

done

for subrange in SR2
do

for i in 400 450 500 600

do

   cat > HTC_TheScript_${i}_${subrange}.sh <<EOF
source /cvmfs/cms.cern.ch/cmsset_default.sh
export SCRAM_ARCH=slc7_amd64_gcc700
cd ${CMSSW_BASE}/src
cmsenv
cd -	
	
echo "Starting combine ${subrange} ${i}"

echo "Expected/Observed Limits"	
combine -M AsymptoticLimits -d hbb_mbb${i}_${subrange}_mssm-13TeV.root --setParameters mask_SR=0,r=0,par0=0.000232321,peak=270.117,slope_novoeff=0.0122963,tail=-0.878842,turnon_novoeff=281.955,width=51.8367,offsetTF=170,alphaTF=0 --freezeParameters offsetTF,par0,slopelinTF --cminDefaultMinimizerStrategy 0 -n Hbb_${subrange} -m ${i} --setParameterRanges r=-5,5:tail=-10,-0.5:par0=-0.001,0.001 -v 5 

EOF
   chmod u+x HTC_TheScript_${i}_${subrange}.sh
   ./HTC_qsub.sh HTC_TheScript_${i}_${subrange}.sh HTC_TheScript_${i}_${subrange}

done

done


for subrange in SR3
do
    peak=240
    tail=-0.711103
	width=57.801
	
for i in 700 800 900

do

   cat > HTC_TheScript_${i}_${subrange}.sh <<EOF
source /cvmfs/cms.cern.ch/cmsset_default.sh
export SCRAM_ARCH=slc7_amd64_gcc700
cd ${CMSSW_BASE}/src
cmsenv
cd -	
	
echo "Starting combine ${subrange} ${i}"

echo "Expected/Observed Limits"	
combine -M AsymptoticLimits -d hbb_mbb${i}_${subrange}_mssm-13TeV.root --setParameterRanges r=-3,3:tail=-1,-0.68:width=40,65 --setParameters mask_SR=0,r=0,tail=$tail,width=$width,peak=$peak,offsetTF=170,alphaTF=0 --freezeParameters offsetTF,tail,alphaTF --cminDefaultMinimizerStrategy 0 -n Hbb_${subrange} -m ${i} -v 5 

EOF
   chmod u+x HTC_TheScript_${i}_${subrange}.sh
  ./HTC_qsub.sh HTC_TheScript_${i}_${subrange}.sh HTC_TheScript_${i}_${subrange}

done

done


for subrange in SR4
do
    peak=240
    tail=-0.764043
	width=51.0459

for i in 1000 1200 1400 1600
do

   cat > HTC_TheScript_${i}_${subrange}.sh <<EOF
source /cvmfs/cms.cern.ch/cmsset_default.sh
export SCRAM_ARCH=slc7_amd64_gcc700
cd ${CMSSW_BASE}/src
cmsenv
cd -	
	
echo "Starting combine ${subrange} ${i}"

echo "Expected/Observed Limits"	
combine -M AsymptoticLimits -d hbb_mbb${i}_${subrange}_mssm-13TeV.root --setParameterRanges r=-1,1:tail=-1,-0.68:width=40,65:steepnessTF=-0.003,0.03:slopelinTF=0.00001,0.001 --setParameters mask_SR=0,r=0,tail=$tail,width=$width,peak=$peak --freezeParameters offsetTF --cminDefaultMinimizerStrategy 0 -n Hbb_${subrange} -m ${i} -v 5  #steepnessTF=-0.003,0.03, nothing for linear slope

EOF
   chmod u+x HTC_TheScript_${i}_${subrange}.sh
   ./HTC_qsub.sh HTC_TheScript_${i}_${subrange}.sh HTC_TheScript_${i}_${subrange}

done

done
