#!/bin/sh

# script to run limit calculation from combination tools
# Documentation:
# https://twiki.cern.ch/twiki/bin/viewauth/CMS/SWGuideHiggsAnalysisCombinedLimit#Datacard_for_Shape_analyses
#

echo "combine -M Asymptotic -m MASS hbb_mbb*_mssm-13TeV.txt"

rm Hbb.limits Hbb.limits_SR1 Hbb.limits_SR2 Hbb.limits_SR3 Hbb.limits_SR4

for i in 300 350
do

    subrange=SR1
    
    limit_file=Hbb.limits_${subrange}
[[ -f "$limit_file_${subrange}" ]] && rm "$limit_file_${subrange}"

	name=hbb_mbb${i}_${subrange}_mssm-13TeV.root
	echo "Process $i GeV Mass Point with: $name"
		
    echo "Starting combine ${subrange} ${i}"

    echo "Expected/Observed Limits"	
    combine -M AsymptoticLimits -t -1 hbb_mbb${i}_${subrange}_mssm-13TeV.root --setParameters mask_SR=0,r=0 --cminDefaultMinimizerStrategy 0 -n Hbb_${subrange} --setParameterRanges r=-20,20:slopelinTF=-3e-4,3e-4:steepnessTF=0.0001,0.05:offsetTF=-250,250 -m ${i} -v 5
  
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
    combine -M AsymptoticLimits -t -1 hbb_mbb${i}_${subrange}_mssm-13TeV.root --setParameters mask_SR=0,r=0,r=0,peak=270.117,tail=-0.878842,width=51.8367,offsetTF=170,alphaTF=0 --freezeParameters offsetTF,slopelinTF --cminDefaultMinimizerStrategy 0 -n Hbb_${subrange} -m ${i} --setParameterRanges r=-5,5:tail=-10,-0.5 -v 5 

    root_name=`readlink -f "higgsCombineHbb_${subrange}.AsymptoticLimits.mH${i}.root"`
	echo "$root_name" >> "$limit_file"	
	echo "$root_name" >> "Hbb.limits"

done


for i in 700 800 900 1000
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
	combine -M AsymptoticLimits -t -1 hbb_mbb${i}_${subrange}_mssm-13TeV.root --setParameterRanges mask_SR=0,r=0,r=-3,3:tail=-1,-0.68:width=40,65 --setParameters r=0,tail=$tail,width=$width,peak=$peak,offsetTF=170,alphaTF=0 --freezeParameters offsetTF,tail,alphaTF --cminDefaultMinimizerStrategy 0 -n Hbb_${subrange} -m ${i} -v 5 

	root_name=`readlink -f "higgsCombineHbb_${subrange}.AsymptoticLimits.mH${i}.root"`
	echo "$root_name" >> "$limit_file"	
	echo "$root_name" >> "Hbb.limits"
	
done


for i in 1200 1400 1600 1800
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
    combine -M AsymptoticLimits -t -1 hbb_mbb${i}_${subrange}_mssm-13TeV.root --setParameterRanges mask_SR=0,r=0,r=-1,1:tail=-1,-0.68:width=40,65:steepnessTF=-0.003,0.03:slopelinTF=0.00001,0.001 --setParameters r=0,tail=$tail,width=$width,peak=$peak --freezeParameters offsetTF --cminDefaultMinimizerStrategy 0 -n Hbb_${subrange} -m ${i} -v 5 #steepnessTF=-0.003,0.03, nothing for linear slope

    root_name=`readlink -f "higgsCombineHbb_${subrange}.AsymptoticLimits.mH${i}.root"`
    echo "$root_name" >> "$limit_file"
    echo "$root_name" >> "Hbb.limits"	
    
done

