#!/bin/sh
# $1 - SR, CR or VR

if [ -e $1.root ]
then
    rm $1.root
fi
 
 
if [ -d "Condor_SimpleMssmHbbAnalysis_2017_"$1"/finished_jobs/root_files" ] 
then
    rm -r Condor_SimpleMssmHbbAnalysis_2017_$1/finished_jobs/root_files
fi

mkdir Condor_SimpleMssmHbbAnalysis_2017_$1/finished_jobs/root_files


find Condor_SimpleMssmHbbAnalysis_2017_$1/  -name "$1.root" -print0 | while IFS= read -r -d '' path
do

    counter=$(( $counter +1 ))
    
    base=$(basename --suffix=".root"  "$path")
    new_path="Condor_SimpleMssmHbbAnalysis_2017_"$1"/finished_jobs/root_files"/"$base""_"$counter".root"
    cp "$path" "$new_path"
done

hadd -k $1.root Condor_SimpleMssmHbbAnalysis_2017_$1/finished_jobs/root_files/*.root
