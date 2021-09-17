#Configuration files:


#data
samples_data=(BTagCSV_Run2017C
BTagCSV_Run2017D
BTagCSV_Run2017E
BTagCSV_Run2017F
)

j=1 

while [ $j -le ${#samples_data[@]} ] 
do
    echo "Creating configuration file for data sample" ${samples_data[$j]}-deep-SR-3j 
    cp SimpleMssmHbbAnalysis_data.cfg ${samples_data[$j]}-deep-SR-3j.cfg
    sed -i 's/JetHT_Run2017C/'${samples_data[$j]}'/g' ${samples_data[$j]}-deep-SR-3j.cfg
    echo "Creating configuration file for data sample" ${samples_data[$j]}-deep-CR-3j
    cp ${samples_data[$j]}-deep-SR-3j.cfg ${samples_data[$j]}-deep-CR-3j.cfg   
    sed -i 's/signalRegion = true/signalRegion = false/g' ${samples_data[$j]}-deep-CR-3j.cfg
    sed -i 's/-SR-3j/-CR-3j/g' ${samples_data[$j]}-deep-CR-3j.cfg   
    echo "Creating configuration file for data sample" ${samples_data[$j]}-deep-VR-3j
    cp ${samples_data[$j]}-deep-CR-3j.cfg ${samples_data[$j]}-deep-VR-3j.cfg
    sed  -i '51i validationRegion = true' ${samples_data[$j]}-deep-VR-3j.cfg
    sed  -i 's/-CR-3j/-VR-3j/g' ${samples_data[$j]}-deep-VR-3j.cfg
    
    j=`expr $j + 1` 
done


#signal MC	
for k in 300 350 400 450 500 600 700 800 900 1000 1200 1400 1600
do

    echo "Creating configuration file for signal sample" mc-sig-${k}-NLO-deep-SR-3j
    cp SimpleMssmHbbAnalysis_signal_mc.cfg mc-sig-${k}-NLO-deep-SR-3j.cfg
    sed -i 's/SUSYGluGluToBBHToBB_M-300/SUSYGluGluToBBHToBB_M-'$k'/g' mc-sig-${k}-NLO-deep-SR-3j.cfg
    sed -i 's/mc-sig-300-NLO-deep-SR-3j/mc-sig-'$k'-NLO-deep-SR-3j/g' mc-sig-${k}-NLO-deep-SR-3j.cfg
    echo "Creating configuration file for signal sample" mc-sig-${k}-NLO-deep-CR-3j
    cp mc-sig-${k}-NLO-deep-SR-3j.cfg mc-sig-${k}-NLO-deep-CR-3j.cfg
    sed -i 's/signalRegion = true/signalRegion = false/g' mc-sig-${k}-NLO-deep-CR-3j.cfg
    sed -i 's/-SR-3j/-CR-3j/g' mc-sig-${k}-NLO-deep-CR-3j.cfg
    echo "Creating configuration file for signal sample" mc-sig-${k}-NLO-deep-VR-3j
    cp mc-sig-${k}-NLO-deep-CR-3j.cfg mc-sig-${k}-NLO-deep-VR-3j.cfg
    sed  -i '51i validationRegion = true' mc-sig-${k}-NLO-deep-VR-3j.cfg
    sed  -i 's/-CR-3j/-VR-3j/g' mc-sig-${k}-NLO-deep-VR-3j.cfg
    
   
done


#background MC
samples_bkgMC=(QCD_HT100to200
QCD_HT200to300
QCD_HT300to500
QCD_HT500to700
QCD_HT700to1000
QCD_HT1000to1500
QCD_HT1500to2000
QCD_HT2000toInf 
QCD-BGenFilter_HT100to200
QCD-BGenFilter_HT200to300
QCD-BGenFilter_HT300to500
QCD-BGenFilter_HT500to700
QCD-BGenFilter_HT700to1000
QCD-BGenFilter_HT1000to1500
QCD-BGenFilter_HT1500to2000
QCD-BGenFilter_HT2000toInf 
QCD-bEnriched_HT100to200
QCD-bEnriched_HT200to300
QCD-bEnriched_HT300to500
QCD-bEnriched_HT500to700
QCD-bEnriched_HT700to1000
QCD-bEnriched_HT1000to1500
QCD-bEnriched_HT1500to2000
QCD-bEnriched_HT2000toInf 
)

l=1

while [ $l -le ${#samples_bkgMC[@]} ] 
do
    echo "Creating configuration file for background MC sample" ${samples_bkgMC[$l]}-deep-SR-3j 
    cp SimpleMssmHbbAnalysis_bkgd_mc.cfg ${samples_bkgMC[$l]}-deep-SR-3j.cfg
    sed -i 's/QCD_HT100to200/'${samples_bkgMC[$l]}-deep'/g' ${samples_bkgMC[$l]}-deep-SR-3j.cfg
    echo "Creating configuration file for background MC sample" ${samples_bkgMC[$l]}-deep-CR-3j
    cp ${samples_bkgMC[$l]}-deep-SR-3j.cfg ${samples_bkgMC[$l]}-deep-CR-3j.cfg
    sed -i 's/signalRegion = true/signalRegion = false/g' ${samples_bkgMC[$l]}-deep-CR-3j.cfg
    sed -i 's/-SR-3j/-CR-3j/g' ${samples_bkgMC[$l]}-deep-CR-3j.cfg
    echo "Creating configuration file for background MC sample" ${samples_bkgMC[$l]}-deep-VR-3j
    cp ${samples_bkgMC[$l]}-deep-CR-3j.cfg ${samples_bkgMC[$l]}-deep-VR-3j.cfg
    sed  -i '51i validationRegion = true' ${samples_bkgMC[$l]}-deep-VR-3j.cfg
    sed  -i 's/-CR-3j/-VR-3j/g' ${samples_bkgMC[$l]}-deep-VR-3j.cfg    
      
    l=`expr $l + 1` 
done
