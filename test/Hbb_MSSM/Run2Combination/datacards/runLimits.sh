#!/bin/sh
echo "  "
echo " Running combine tool for all the mass points "
echo "  "

mass=mass
massf=massf

for i in {125,130,140,160,180,200,250}

do

  echo "  "
  echo "  "
  
  eval "mass=${i}"
  

  echo "Computing limits for Ma = $mass GeV"
 
  cp hbb_mbb${mass}_mssm-13TeV_2017_SL.txt hbb_mbb${mass}_mssm-13TeV_Run2.txt

  combine -M AsymptoticLimits -t -1 hbb_mbb${mass}_mssm-13TeV_Run2.txt --setParameterRanges r=-1,1 --setParameters mask_SR=1,r=0 --cminDefaultMinimizerStrategy 0 -n Hbb -m ${i} -v 5 

done


for i in {300,350,400,450,500,600,700}

do

  echo "  "
  echo "  "
  
  eval "mass=${i}"
  

  echo "Computing limits for Ma = $mass GeV"
  
  combineCards.py Run2017_FH=hbb_mbb${mass}_mssm-13TeV_2017_FH.txt Run2018_FH=hbb_mbb${mass}_mssm-13TeV_2018_FH.txt Run2017_SL=hbb_mbb${mass}_mssm-13TeV_2017_SL.txt > hbb_mbb${mass}_mssm-13TeV_Run2.txt

  combine -M AsymptoticLimits -t -1 hbb_mbb${mass}_mssm-13TeV_Run2.txt --setParameterRanges r=-1,1 --setParameters mask_SR=1,r=0 --cminDefaultMinimizerStrategy 0 -n Hbb -m ${i} -v 5 

done


for i in {800,900,1000,1200,1400,1600,1800}

do

  echo "  "
  echo "  "
  
  eval "mass=${i}"
  

  echo "Computing limits for Ma = $mass GeV"
  
  combineCards.py Run2017_FH=hbb_mbb${mass}_mssm-13TeV_2017_FH.txt Run2018_FH=hbb_mbb${mass}_mssm-13TeV_2018_FH.txt > hbb_mbb${mass}_mssm-13TeV_Run2.txt

  combine -M AsymptoticLimits -t -1 hbb_mbb${mass}_mssm-13TeV_Run2.txt --setParameterRanges r=-1,1 --setParameters mask_SR=1,r=0 --cminDefaultMinimizerStrategy 0 -n Hbb -m ${i} -v 5 

done

