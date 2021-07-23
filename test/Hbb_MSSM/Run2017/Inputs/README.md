# consuegs/analysis-mssmhbb/test/Hbb_MSSM/Run2017/Inputs 

**Macros and scripts useful for limit computation: MSSM Hbb all-hadronic analysis**


####  Workspaces to be used as input for combine tool

Workspaces can be produced by running the following macros,  one for each of the 4 analysis regions:

Binned signal:

`AnalysisWorkspaceSR{i}.C` 

`i=1,2,3,4`


Parametric signal pdf:

`AnalysisWorkspaceSR{i}_parametrized.C`


#### Input files needed to produce the workspaces


#### Datacard templates

Template for the production of datacards:

   Binned signal:

   `datacard_Analysis_template.txt`

   Parametric signal pdf:

   `datacard_Analysis_template_parametrized.txt`
   
The datacards can be produced running the bash scripts `DataCardProducer.sh` and `DataCardProducer_parametrized.sh`  


#### Limit computation 


Run combine tool locally:

`runLimits.sh`

or submit to condor

`HTC_qsub_seq.sh`

If jobs are submitted to condor the limit plot is obtained afterwards running the bash script: `PlotLimits.sh`

If combine tool runs locally, the script `runLimits.sh` already incorporates `PlotLimits.sh`

Limit plots will appear in folders: `/results` and `/results_parametrized`

#### CMSSW version
Mini-framework for signal and background parameterizations and the combine tool package are needed

Signal and bkgd models:

https://github.com/desy-cms/analysis-models


Combine tool:

http://cms-analysis.github.io/HiggsAnalysis-CombinedLimit/



If further clarifications are needed please contact: sandra.consuegra.rodriguez@desy.de, sandra.consuegra.rodriguez@cern.ch
                                            
Instructions last updated: 23.07.2021 
