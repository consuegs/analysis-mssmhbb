# consuegs/analysis-mssmhbb/test/Hbb_MSSM/Run2017/Inputs 

**Macros and scripts useful for limit computation: MSSM Hbb all-hadronic analysis**


####  Workspaces to be used as input for combine tool

Workspaces can be produced by running the following macros,  one for each of the 4 analysis regions:


Parametric signal pdf:

FH channel:

`AnalysisWorkspaceSR{i}_FH.C`

SL channel:

`AnalysisWorkspaceSR{i}_SL.C`


#### Input files needed to produce the workspaces


#### Datacard templates

Template for the production of datacards:

   Parametric signal pdf:

   `datacard_Analysis_template_FH.txt`, `datacard_Analysis_template_SL.txt`
   
The datacards can be produced running the bash script `DataCardProducer_FH.sh`, `DataCardProducer_SL.sh`  

#### Limit computation 


Run combine tool locally:

`runLimits.sh`

Produce limits plot:
`PlotLimits.C`


#### CMSSW version
Mini-framework for signal and background parameterizations and the combine tool package are needed

Signal and bkgd models:

https://github.com/desy-cms/analysis-models


Combine tool:

http://cms-analysis.github.io/HiggsAnalysis-CombinedLimit/



If further clarifications are needed please contact: sandra.consuegra.rodriguez@desy.de, sandra.consuegra.rodriguez@cern.ch
                                            
Instructions last updated: 13.04.2022 
