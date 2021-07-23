for subrange in SR1
do
    limit_file=Hbb.limits
    [[ -f "$limit_file" ]] && rm "$limit_file"
    if [ "$subrange" = "SR1" ]
    then masses=(300 325 350 375 400)
    fi
    echo "$subrange, masses ${masses[@]}"
    for mass in ${masses[@]}
    do
	    if [ ${mass} = 300 ]
	    then bias=1.116; offbtag=1.096; onlbtag=1.037; kintrig=1.016; purew=1.001
	    elif [ ${mass} = 325 ]
	    then bias=0.753; offbtag=1.093; onlbtag=1.039; kintrig=1.014; purew=1.002
        elif [ ${mass} = 350 ]
	    then bias=0.753; offbtag=1.093; onlbtag=1.039; kintrig=1.014; purew=1.002
	    elif [ ${mass} = 375 ]
	    then bias=0.753; offbtag=1.093; onlbtag=1.039; kintrig=1.014; purew=1.002
	    elif [ ${mass} = 400 ]
	    then bias=0.45; offbtag=1.091; onlbtag=1.041; kintrig=1.013; purew=1.003
	    elif [ ${mass} = 425 ]
	    then bias=0.45; offbtag=1.091; onlbtag=1.041; kintrig=1.013; purew=1.003
	    fi
        cd datacards/
	    cp ../datacard_Analysis_template.txt hbb_mbb${mass}_SR1_mssm-13TeV.txt
	
	    sed -i "s/MASS/${mass}/g" hbb_mbb${mass}_SR1_mssm-13TeV.txt
	    sed -i "s/SUBRANGE/${subrange}/g" hbb_mbb${mass}_SR1_mssm-13TeV.txt
	    sed -i "s/BIASRESULT/${bias}/g" hbb_mbb${mass}_SR1_mssm-13TeV.txt
	    sed -i "s/OFFBT/${offbtag}/g" hbb_mbb${mass}_SR1_mssm-13TeV.txt
        sed -i "s/ONLBT/${onlbtag}/g" hbb_mbb${mass}_SR1_mssm-13TeV.txt
        sed -i "s/KINTO/${kintrig}/g" hbb_mbb${mass}_SR1_mssm-13TeV.txt
        sed -i "s/PUVAL/${purew}/g" hbb_mbb${mass}_SR1_mssm-13TeV.txt
    
        echo "Datacard $mass GeV, $subrange created"
        text2workspace.py hbb_mbb${mass}_SR1_mssm-13TeV.txt 
    
        cd ../
    
    done
    
done






for subrange in SR2
do
    limit_file=Hbb.limits
    [[ -f "$limit_file" ]] && rm "$limit_file"
    if [ "$subrange" = "SR2" ]
    then masses=(400 425 450 500 600 700)
    fi
    echo "$subrange, masses ${masses[@]}"
    for mass in ${masses[@]}
    do
	    if [ ${mass} = 400 ]
        then bias=0.465; offbtag=1.112; onlbtag=1.042; kintrig=1.013; purew=1.002
        elif [ ${mass} = 425 ]
        then bias=0.465; offbtag=1.112; onlbtag=1.042; kintrig=1.013; purew=1.002
	    elif [ ${mass} = 450 ]
        then bias=0.339; offbtag=1.109; onlbtag=1.044; kintrig=1.012; purew=1.001
        elif [ ${mass} = 500 ]
        then bias=0.276; offbtag=1.104; onlbtag=1.046; kintrig=1.012; purew=1.001
	    elif [ ${mass} = 600 ]
        then bias=0.183; offbtag=1.101; onlbtag=1.051; kintrig=1.011; purew=1.002
	    elif [ ${mass} = 700 ]
        then bias=0.102; offbtag=1.097; onlbtag=1.056; kintrig=1.011; purew=1.002
        fi
        cd datacards/
	    cp ../datacard_Analysis_template.txt hbb_mbb${mass}_SR2_mssm-13TeV.txt
	
	    sed -i "s/MASS/${mass}/g" hbb_mbb${mass}_SR2_mssm-13TeV.txt
	    sed -i "s/SUBRANGE/${subrange}/g" hbb_mbb${mass}_SR2_mssm-13TeV.txt
	    sed -i "s/BIASRESULT/${bias}/g" hbb_mbb${mass}_SR2_mssm-13TeV.txt
	    sed -i "s/OFFBT/${offbtag}/g" hbb_mbb${mass}_SR2_mssm-13TeV.txt
        sed -i "s/ONLBT/${onlbtag}/g" hbb_mbb${mass}_SR2_mssm-13TeV.txt
        sed -i "s/KINTO/${kintrig}/g" hbb_mbb${mass}_SR2_mssm-13TeV.txt
        sed -i "s/PUVAL/${purew}/g" hbb_mbb${mass}_SR2_mssm-13TeV.txt
    
        echo "Datacard $mass GeV, $subrange created"
        text2workspace.py hbb_mbb${mass}_SR2_mssm-13TeV.txt 
    
        cd ../
    
    done
    
done




peak=240
for subrange in SR3
do
    limit_file=Hbb.limits
    [[ -f "$limit_file" ]] && rm "$limit_file"
    if [ "$subrange" = "SR3" ]
    then masses=(700 800 900 1000)
         tail=-0.711103
	     width=57.801
    fi
    echo "$subrange, masses ${masses[@]}"
    for mass in ${masses[@]}
    do
	    if [ ${mass} = 700 ]
        then bias=0.038; offbtag=1.115; onlbtag=1.057; kintrig=1.011; purew=1.002
        elif [ ${mass} = 800 ]
        then bias=0.026; offbtag=1.115; onlbtag=1.062; kintrig=1.011; purew=1.002
        elif [ ${mass} = 900 ]
        then bias=0.021; offbtag=1.113; onlbtag=1.067; kintrig=1.011; purew=1.001
        elif [ ${mass} = 1000 ]
        then bias=0.017; offbtag=1.112; onlbtag=1.072; kintrig=1.011; purew=1.001
        fi
        cd datacards/
	    cp ../datacard_Analysis_template.txt hbb_mbb${mass}_SR3_mssm-13TeV.txt
	
	    sed -i "s/MASS/${mass}/g" hbb_mbb${mass}_SR3_mssm-13TeV.txt
	    sed -i "s/SUBRANGE/${subrange}/g" hbb_mbb${mass}_SR3_mssm-13TeV.txt
	    sed -i "s/BIASRESULT/${bias}/g" hbb_mbb${mass}_SR3_mssm-13TeV.txt
	    sed -i "s/OFFBT/${offbtag}/g" hbb_mbb${mass}_SR3_mssm-13TeV.txt
        sed -i "s/ONLBT/${onlbtag}/g" hbb_mbb${mass}_SR3_mssm-13TeV.txt
        sed -i "s/KINTO/${kintrig}/g" hbb_mbb${mass}_SR3_mssm-13TeV.txt
        sed -i "s/PUVAL/${purew}/g" hbb_mbb${mass}_SR3_mssm-13TeV.txt
    
        echo "Datacard $mass GeV, $subrange created"
        text2workspace.py hbb_mbb${mass}_SR3_mssm-13TeV.txt 
    
        cd ../
    
    done
    
done




peak=240
for subrange in SR4
do
    limit_file=Hbb.limits
    [[ -f "$limit_file" ]] && rm "$limit_file"
    if [ "$subrange" = "SR4" ]
    then masses=(1000 1200 1400 1600)
         tail=-0.764043
	     width=51.0459
    fi
    echo "$subrange, masses ${masses[@]}"
    for mass in ${masses[@]}
    do
	    if [ ${mass} = 1000 ]
        then bias=0.017; offbtag=1.129; onlbtag=1.073; kintrig=1.011; purew=1.001
        elif [ ${mass} = 1200 ]
        then bias=0.011; offbtag=1.124; onlbtag=1.083; kintrig=1.011; purew=1.000
        elif [ ${mass} = 1400 ]
        then bias=0.011; offbtag=1.119; onlbtag=1.094; kintrig=1.011; purew=1.001
        elif [ ${mass} = 1600 ]
        then bias=0.010; offbtag=1.116; onlbtag=1.105; kintrig=1.011; purew=1.000
        fi
        cd datacards/
	    cp ../datacard_Analysis_template.txt hbb_mbb${mass}_SR4_mssm-13TeV.txt
	
	    sed -i "s/MASS/${mass}/g" hbb_mbb${mass}_SR4_mssm-13TeV.txt
	    sed -i "s/SUBRANGE/${subrange}/g" hbb_mbb${mass}_SR4_mssm-13TeV.txt
	    sed -i "s/BIASRESULT/${bias}/g" hbb_mbb${mass}_SR4_mssm-13TeV.txt
	    sed -i "s/OFFBT/${offbtag}/g" hbb_mbb${mass}_SR4_mssm-13TeV.txt
        sed -i "s/ONLBT/${onlbtag}/g" hbb_mbb${mass}_SR4_mssm-13TeV.txt
        sed -i "s/KINTO/${kintrig}/g" hbb_mbb${mass}_SR4_mssm-13TeV.txt
        sed -i "s/PUVAL/${purew}/g" hbb_mbb${mass}_SR4_mssm-13TeV.txt
    
        echo "Datacard $mass GeV, $subrange created"
        text2workspace.py hbb_mbb${mass}_SR4_mssm-13TeV.txt 
    
        cd ../
    
    done
    
done
