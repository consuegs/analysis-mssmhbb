#!/bin/sh

#cp -r /nfs/dust/cms/user/consuegs/Analyses/Hbb_MSSM/analysis-mssmhbb/test/Hbb_MSSM/Run2017/Inputs/input_2017_FH .
#cp -r /nfs/dust/cms/user/consuegs/Analyses/Hbb_MSSM/analysis-mssmhbb/test/Hbb_MSSM/Run2018/Inputs/input_2018_FH .
#cp -r /nfs/dust/cms/user/consuegs/Analyses/Hbb_MSSM/analysis-mssmhbb/test/Hbb_MSSM/Run2018/Inputs/input_2018_2017TF_FH/ .

cd datacards/

for i in {300,350}

do

  echo "  "
  echo "  "
  
  eval "mass=${i}"
  

  echo "Copying files needed for limit calculation for Ma = $mass GeV"

  echo "2017"

  cp /nfs/dust/cms/user/consuegs/Analyses/Hbb_MSSM/analysis-mssmhbb/test/Hbb_MSSM/Run2017/Inputs/datacards/hbb_mbb${mass}_SR1* ./  
  
  mv hbb_mbb${mass}_SR1_mssm-13TeV.txt hbb_mbb${mass}_SR1_mssm-13TeV_2017_FH.txt
  mv hbb_mbb${mass}_SR1_mssm-13TeV.root hbb_mbb${mass}_SR1_mssm-13TeV_2017_FH.root
  
  echo "2018"
  
  cp /nfs/dust/cms/user/consuegs/Analyses/Hbb_MSSM/analysis-mssmhbb/test/Hbb_MSSM/Run2018/Inputs/datacards_2017TF/hbb_mbb${mass}_SR1* ./
  
  mv hbb_mbb${mass}_SR1_mssm-13TeV.txt hbb_mbb${mass}_SR1_mssm-13TeV_2018_FH.txt
  mv hbb_mbb${mass}_SR1_mssm-13TeV.root hbb_mbb${mass}_SR1_mssm-13TeV_2018_FH.root


done


for i in {400,450,500,600}

do

  echo "  "
  echo "  "
  
  eval "mass=${i}"
  

  echo "Copying files needed for limit calculation for Ma = $mass GeV"

  echo "2017"

  cp /nfs/dust/cms/user/consuegs/Analyses/Hbb_MSSM/analysis-mssmhbb/test/Hbb_MSSM/Run2017/Inputs/datacards/hbb_mbb${mass}_SR2* ./  
  
  mv hbb_mbb${mass}_SR2_mssm-13TeV.txt hbb_mbb${mass}_SR2_mssm-13TeV_2017_FH.txt
  mv hbb_mbb${mass}_SR2_mssm-13TeV.root hbb_mbb${mass}_SR2_mssm-13TeV_2017_FH.root
  
  echo "2018"
  
  cp /nfs/dust/cms/user/consuegs/Analyses/Hbb_MSSM/analysis-mssmhbb/test/Hbb_MSSM/Run2018/Inputs/datacards_2017TF/hbb_mbb${mass}_SR2* ./
  
  mv hbb_mbb${mass}_SR2_mssm-13TeV.txt hbb_mbb${mass}_SR2_mssm-13TeV_2018_FH.txt
  mv hbb_mbb${mass}_SR2_mssm-13TeV.root hbb_mbb${mass}_SR2_mssm-13TeV_2018_FH.root


done


for i in {700,800,900,1000}

do

  echo "  "
  echo "  "
  
  eval "mass=${i}"
  

  echo "Copying files needed for limit calculation for Ma = $mass GeV"

  echo "2017"

  cp /nfs/dust/cms/user/consuegs/Analyses/Hbb_MSSM/analysis-mssmhbb/test/Hbb_MSSM/Run2017/Inputs/datacards/hbb_mbb${mass}_SR3* ./  
  
  mv hbb_mbb${mass}_SR3_mssm-13TeV.txt hbb_mbb${mass}_SR3_mssm-13TeV_2017_FH.txt
  mv hbb_mbb${mass}_SR3_mssm-13TeV.root hbb_mbb${mass}_SR3_mssm-13TeV_2017_FH.root
  
  echo "2018"
  
  cp /nfs/dust/cms/user/consuegs/Analyses/Hbb_MSSM/analysis-mssmhbb/test/Hbb_MSSM/Run2018/Inputs/datacards_2017TF/hbb_mbb${mass}_SR3* ./
  
  mv hbb_mbb${mass}_SR3_mssm-13TeV.txt hbb_mbb${mass}_SR3_mssm-13TeV_2018_FH.txt
  mv hbb_mbb${mass}_SR3_mssm-13TeV.root hbb_mbb${mass}_SR3_mssm-13TeV_2018_FH.root


done


for i in {1200,1400,1600,1800}

do

  echo "  "
  echo "  "
  
  eval "mass=${i}"
  

  echo "Copying files needed for limit calculation for Ma = $mass GeV"

  echo "2017"

  cp /nfs/dust/cms/user/consuegs/Analyses/Hbb_MSSM/analysis-mssmhbb/test/Hbb_MSSM/Run2017/Inputs/datacards/hbb_mbb${mass}_SR4* ./  
  
  mv hbb_mbb${mass}_SR4_mssm-13TeV.txt hbb_mbb${mass}_SR4_mssm-13TeV_2017_FH.txt
  mv hbb_mbb${mass}_SR4_mssm-13TeV.root hbb_mbb${mass}_SR4_mssm-13TeV_2017_FH.root

  echo "2018"
    
  cp /nfs/dust/cms/user/consuegs/Analyses/Hbb_MSSM/analysis-mssmhbb/test/Hbb_MSSM/Run2018/Inputs/datacards_2017TF/hbb_mbb${mass}_SR4* ./
  
  mv hbb_mbb${mass}_SR4_mssm-13TeV.txt hbb_mbb${mass}_SR4_mssm-13TeV_2018_FH.txt
  mv hbb_mbb${mass}_SR4_mssm-13TeV.root hbb_mbb${mass}_SR4_mssm-13TeV_2018_FH.root


done

cd ../
