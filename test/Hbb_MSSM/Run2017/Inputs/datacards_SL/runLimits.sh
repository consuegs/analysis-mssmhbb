#!/bin/sh
echo "  "
echo " Running combine tool for all the mass points "
echo "  "

mass=mass
massf=massf

for i in {125,130,140,160,180,200,250,300,350,400,450,500,600,700}

do

  echo "  "
  echo "  "
  
  eval "mass=${i}"
  

  echo "Computing limits for Ma = $mass GeV"

  combine -M AsymptoticLimits -t -1 hbb_mbb${mass}_mssm-13TeV_2017_SL.txt --setParameterRanges r=-1,1 --setParameters mask_SR=1,r=0 --cminDefaultMinimizerStrategy 0 -n Hbb -m ${i} -v 5 

done
