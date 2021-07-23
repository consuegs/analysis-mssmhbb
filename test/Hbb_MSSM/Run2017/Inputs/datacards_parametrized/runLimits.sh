#!/bin/sh

# script to run limit calculation from combination tools
# Documentation:
# https://twiki.cern.ch/twiki/bin/viewauth/CMS/SWGuideHiggsAnalysisCombinedLimit#Datacard_for_Shape_analyses
#

echo "combine -M Asymptotic -m MASS hbb_mbb*_mssm-13TeV.txt"

for i in 300 350
do

    subrange=SR1
    
    limit_file=Hbb.limits_${subrange}
[[ -f "$limit_file_${subrange}" ]] && rm "$limit_file_${subrange}"

	name=hbb_mbb${i}_${subrange}_mssm-13TeV.root
	echo "Process $i GeV Mass Point with: $name"
		
    echo "Starting combine ${subrange} ${i}"

    echo "Expected/Observed Limits"	
    combine -M AsymptoticLimits -d hbb_mbb${i}_${subrange}_mssm-13TeV.root --setParameters mask_SR=0,r=0,bernstein_coefficient_00=2.28831,bernstein_coefficient_01=0.000193003,bernstein_coefficient_02=24.9699,bernstein_coefficient_03=0.799356,bernstein_coefficient_04=6.15331,bernstein_coefficient_05=2.15559,bernstein_coefficient_06=1.84779,turnon_novoeff=228.7,slope_novoeff=0.02 --freezeParameters bernstein_coefficient_02 --cminDefaultMinimizerStrategy 0 -n Hbb_${subrange} --setParameterRanges r=-20,20:bernstein_coefficient_00=0,5:bernstein_coefficient_01=-1,1:bernstein_coefficient_02=20,30:bernstein_coefficient_03=-2,2:bernstein_coefficient_04=2,10:bernstein_coefficient_05=0,10:bernstein_coefficient_06=0,5:turnon_novoeff=200,300:slope_novoeff=0,0.1:slopelinTF=-3e-4,3e-4:steepnessTF=0.0001,0.05:offsetTF=-250,250 -m ${i} -v 5

    root_name=`readlink -f "higgsCombineHbb_${subrange}.AsymptoticLimits.mH${i}.root"`
	echo "$root_name" >> "$limit_file"	
	echo "$root_name" >> "Hbb.limits"	

done


for i in 400 450 500 600
do

    subrange=SR2
    
    limit_file=Hbb.limits_${subrange}
[[ -f "$limit_file_${subrange}" ]] && rm "$limit_file_${subrange}"

	name=hbb_mbb${i}_${subrange}_mssm-13TeV.root
	echo "Process $i GeV Mass Point with: $name"	
	
	echo "Starting combine ${subrange} ${i}"

    echo "Expected/Observed Limits"	
    combine -M AsymptoticLimits -d hbb_mbb${i}_${subrange}_mssm-13TeV.root --setParameters mask_SR=0,r=0,par0=0.000232321,peak=270.117,slope_novoeff=0.0122963,tail=-0.878842,turnon_novoeff=281.955,width=51.8367,offsetTF=170,alphaTF=0 --freezeParameters offsetTF,par0,slopelinTF --cminDefaultMinimizerStrategy 0 -n Hbb_${subrange} -m ${i} --setParameterRanges r=-5,5:tail=-10,-0.5:par0=-0.001,0.001 -v 5 

    root_name=`readlink -f "higgsCombineHbb_${subrange}.AsymptoticLimits.mH${i}.root"`
	echo "$root_name" >> "$limit_file"	
	echo "$root_name" >> "Hbb.limits"

done


for i in 700 800 900
do

    subrange=SR3
    
    limit_file=Hbb.limits_${subrange}
[[ -f "$limit_file_${subrange}" ]] && rm "$limit_file_${subrange}"

	name=hbb_mbb${i}_${subrange}_mssm-13TeV.root
	echo "Process $i GeV Mass Point with: $name"

    peak=240
    tail=-0.711103
	width=57.801
	
	echo "Starting combine ${subrange} ${i}"

    echo "Expected/Observed Limits"	
    combine -M AsymptoticLimits -d hbb_mbb${i}_${subrange}_mssm-13TeV.root --setParameterRanges r=-3,3:tail=-1,-0.68:width=40,65 --setParameters mask_SR=0,r=0,tail=$tail,width=$width,peak=$peak,offsetTF=170,alphaTF=0 --freezeParameters offsetTF,tail,alphaTF --cminDefaultMinimizerStrategy 0 -n Hbb_${subrange} -m ${i} -v 5 

    root_name=`readlink -f "higgsCombineHbb_${subrange}.AsymptoticLimits.mH${i}.root"`
	echo "$root_name" >> "$limit_file"	
	echo "$root_name" >> "Hbb.limits"
	
done


for i in 1000 1200 1400 1600
do
    subrange=SR4
    
    limit_file=Hbb.limits_${subrange}
[[ -f "$limit_file_${subrange}" ]] && rm "$limit_file_${subrange}"

	name=hbb_mbb${i}_${subrange}_mssm-13TeV.root
	echo "Process $i GeV Mass Point with: $name"

    peak=240
    tail=-0.764043
	width=51.045
		
	echo "Starting combine ${subrange} ${i}"

    echo "Expected/Observed Limits"		
    combine -M AsymptoticLimits -d hbb_mbb${i}_${subrange}_mssm-13TeV.root --setParameterRanges r=-1,1:tail=-1,-0.68:width=40,65:steepnessTF=-0.003,0.03:slopelinTF=0.00001,0.001 --setParameters mask_SR=0,r=0,tail=$tail,width=$width,peak=$peak --freezeParameters offsetTF --cminDefaultMinimizerStrategy 0 -n Hbb_${subrange} -m ${i} -v 5 #steepnessTF=-0.003,0.03, nothing for linear slope

    root_name=`readlink -f "higgsCombineHbb_${subrange}.AsymptoticLimits.mH${i}.root"`
	echo "$root_name" >> "$limit_file"
	echo "$root_name" >> "Hbb.limits"	

done



echo "Merge Combination output:"

hadd -f combineMerge_SR1.root higgsCombineHbb_SR1.AsymptoticLimits.mH*.root
hadd -f combineMerge_SR2.root higgsCombineHbb_SR2.AsymptoticLimits.mH*.root
hadd -f combineMerge_SR3.root higgsCombineHbb_SR3.AsymptoticLimits.mH*.root
hadd -f combineMerge_SR4.root higgsCombineHbb_SR4.AsymptoticLimits.mH*.root

echo "Merge Done: combineMerge.root was created"

echo "run PlotLimit script"
echo "mhmod+ scenario"
PlotLimit -i Hbb.limits
PlotLimit -i Hbb.limits_SR1
PlotLimit -i Hbb.limits_SR2
PlotLimit -i Hbb.limits_SR3
PlotLimit -i Hbb.limits_SR4
echo "hMSSM benchmark"
#PlotLimit -M tanBeta -b ${CMSSW_BASE}/src/Analysis/MssmHbb/macros/signal/hMSSM_13TeV.root -i Hbb.limits

mv *.png ../results
mv *.pdf ../results

echo "Done"
