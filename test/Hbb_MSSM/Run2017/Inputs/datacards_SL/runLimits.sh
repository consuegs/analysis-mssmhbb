#!/bin/sh

# script to run limit calculation from combination tools
# Documentation:
# https://twiki.cern.ch/twiki/bin/viewauth/CMS/SWGuideHiggsAnalysisCombinedLimit#Datacard_for_Shape_analyses
#

echo "combine -M Asymptotic -m MASS hbb_mbb*_mssm-13TeV.txt"

rm Hbb.limits Hbb.limits_SR1 Hbb.limits_SR2 Hbb.limits_SR3 Hbb.limits_SR4

for i in 125 130 140 160 180 200
do

    subrange=SR1
    
    limit_file=Hbb.limits_${subrange}
[[ -f "$limit_file_${subrange}" ]] && rm "$limit_file_${subrange}"

	name=hbb_mbb${i}_${subrange}_mssm-13TeV.root
	echo "Process $i GeV Mass Point with: $name"
		
    echo "Starting combine ${subrange} ${i}"

    echo "Expected/Observed Limits"	
    combine -M AsymptoticLimits -t -1 hbb_mbb${i}_${subrange}_mssm-13TeV.root --setParameterRanges r=-1,1 --setParameters mask_SR=1,r=0 --cminDefaultMinimizerStrategy 0 -n Hbb_${subrange} -m ${i} -v 5 

    root_name=`readlink -f "higgsCombineHbb_${subrange}.AsymptoticLimits.mH${i}.root"`
	echo "$root_name" >> "$limit_file"	
	echo "$root_name" >> "Hbb.limits"	

done


for i in 250 300 350
do

    subrange=SR2
    
    limit_file=Hbb.limits_${subrange}
[[ -f "$limit_file_${subrange}" ]] && rm "$limit_file_${subrange}"

	name=hbb_mbb${i}_${subrange}_mssm-13TeV.root
	echo "Process $i GeV Mass Point with: $name"	
	
	echo "Starting combine ${subrange} ${i}"

    echo "Expected/Observed Limits"	
    combine -M AsymptoticLimits -t -1 hbb_mbb${i}_${subrange}_mssm-13TeV.root --setParameterRanges r=-1,1 --setParameters mask_SR=1,r=0 --cminDefaultMinimizerStrategy 0 -n Hbb_${subrange} -m ${i} -v 5 

    root_name=`readlink -f "higgsCombineHbb_${subrange}.AsymptoticLimits.mH${i}.root"`
	echo "$root_name" >> "$limit_file"	
	echo "$root_name" >> "Hbb.limits"

done


for i in 400 450 500
do

    subrange=SR3
    
    limit_file=Hbb.limits_${subrange}
[[ -f "$limit_file_${subrange}" ]] && rm "$limit_file_${subrange}"

	name=hbb_mbb${i}_${subrange}_mssm-13TeV.root
	echo "Process $i GeV Mass Point with: $name"
	
	echo "Starting combine ${subrange} ${i}"

	echo "Expected/Observed Limits"	
	combine -M AsymptoticLimits -t -1 hbb_mbb${i}_${subrange}_mssm-13TeV.root --setParameterRanges r=-1,1 --setParameters mask_SR=1,r=0 --cminDefaultMinimizerStrategy 0 -n Hbb_${subrange} -m ${i} -v 5 

	root_name=`readlink -f "higgsCombineHbb_${subrange}.AsymptoticLimits.mH${i}.root"`
	echo "$root_name" >> "$limit_file"	
	echo "$root_name" >> "Hbb.limits"
	
done


for i in 600 700
do
    subrange=SR4
    
    limit_file=Hbb.limits_${subrange}
    [[ -f "$limit_file_${subrange}" ]] && rm "$limit_file_${subrange}"

    name=hbb_mbb${i}_${subrange}_mssm-13TeV.root
    echo "Process $i GeV Mass Point with: $name"
		
    echo "Starting combine ${subrange} ${i}"

    echo "Expected/Observed Limits"		
    combine -M AsymptoticLimits -t -1 hbb_mbb${i}_${subrange}_mssm-13TeV.root --setParameterRanges r=-1,1 --setParameters mask_SR=1,r=0 --cminDefaultMinimizerStrategy 0 -n Hbb_${subrange} -m ${i} -v 5 

    root_name=`readlink -f "higgsCombineHbb_${subrange}.AsymptoticLimits.mH${i}.root"`
    echo "$root_name" >> "$limit_file"
    echo "$root_name" >> "Hbb.limits"	
    
done

