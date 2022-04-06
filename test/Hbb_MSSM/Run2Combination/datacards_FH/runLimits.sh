#!/bin/sh
echo "  "
echo " Running combine tool for all the mass points "
echo "  "

mass=mass
massf=massf

mass=mass

for i in {300,350}

do

  echo "  "
  echo "  "
  
  eval "mass=${i}"
  

  echo "Computing limits for Ma = $mass GeV"
  
  combineCards.py Run2017_FH=hbb_mbb${mass}_SR1_mssm-13TeV_2017_FH.txt Run2018_FH=hbb_mbb${mass}_SR1_mssm-13TeV_2018_FH.txt > hbb_mbb${mass}_SR1_mssm-13TeV_Run2.txt

  combine -M AsymptoticLimits -t -1 hbb_mbb${mass}_SR1_mssm-13TeV_Run2.txt --setParameterRanges r=-1,1 --setParameters mask_SR=1,r=0 --cminDefaultMinimizerStrategy 0 -n Hbb_SR1 -m ${i} -v 5 

done


for i in {400,450,500,600}

do

  echo "  "
  echo "  "
  
  eval "mass=${i}"
  

  echo "Computing limits for Ma = $mass GeV"
  
  combineCards.py Run2017_FH=hbb_mbb${mass}_SR2_mssm-13TeV_2017_FH.txt Run2018_FH=hbb_mbb${mass}_SR2_mssm-13TeV_2018_FH.txt > hbb_mbb${mass}_SR2_mssm-13TeV_Run2.txt

  combine -M AsymptoticLimits -t -1 hbb_mbb${mass}_SR2_mssm-13TeV_Run2.txt --setParameterRanges r=-1,1 --setParameters mask_SR=1,r=0 --cminDefaultMinimizerStrategy 0 -n Hbb_SR2 -m ${i} -v 5 

done


for i in {700,800,900,1000}

do

  echo "  "
  echo "  "
  
  eval "mass=${i}"
  

  echo "Computing limits for Ma = $mass GeV"
  
  combineCards.py Run2017_FH=hbb_mbb${mass}_SR3_mssm-13TeV_2017_FH.txt Run2018_FH=hbb_mbb${mass}_SR3_mssm-13TeV_2018_FH.txt > hbb_mbb${mass}_SR3_mssm-13TeV_Run2.txt

  combine -M AsymptoticLimits -t -1 hbb_mbb${mass}_SR3_mssm-13TeV_Run2.txt --setParameterRanges r=-1,1 --setParameters mask_SR=1,r=0 --cminDefaultMinimizerStrategy 0 -n Hbb_SR3 -m ${i} -v 5

done


for i in {1200,1400,1600,1800}

do

  echo "  "
  echo "  "
  
  eval "mass=${i}"
  

  echo "Computing limits for Ma = $mass GeV"
  
  
  combineCards.py Run2017_FH=hbb_mbb${mass}_SR4_mssm-13TeV_2017_FH.txt Run2018_FH=hbb_mbb${mass}_SR4_mssm-13TeV_2018_FH.txt > hbb_mbb${mass}_SR4_mssm-13TeV_Run2.txt

  combine -M AsymptoticLimits -t -1 hbb_mbb${mass}_SR4_mssm-13TeV_Run2.txt --setParameterRanges r=-1,1 --setParameters mask_SR=1,r=0 --cminDefaultMinimizerStrategy 0 -n Hbb_SR4 -m ${i} -v 5

done

