# consuegs/analysis-mssmhbb/test/Hbb_MSSM/ 

** Some additional macros and scripts useful for the MSSM Hbb all-hadronic analysis**

# Configuration files
Template for configuration files available separately for data, background MC, and signal MC samples for the 2017, and 2018 periods:

    SimpleMssmHbbAnalysis_data.cfg
    SimpleMssmHbbAnalysis_bkgd_mc.cfg
    SimpleMssmHbbAnalysis_signal_mc.cfg


## NAF Submission

Bash scripts to submit to the NAF condor queue are available:

`HTC_qsub_all.sh $1` - all jobs

`HTC_qsub_data.sh $1` - data only jobs 

`HTC_qsub_bkgd.sh $1` - background MC only jobs 

`HTC_qsub_signal.sh $1` - signal only jobs 

```bash
./HTC_qsub_all.sh $1
```
$1 - SR, CR, or VR


After the jobs are submitted directories called `Condor_SimpleMssmHbbAnalysis_${year}_FileListName` are created

`${year} = 2017, 2018`

The status of the jobs can be checked running the bash script `./checkstatus.sh $1`

If some jobs finished with an error they can be resubmitted running the bash script `./resubmit.sh $1`

Once the directory `Condor_SimpleMssmHbbAnalysis_${year}_FileListName` is created and all the jobs finished correctly, one can proceed to merge the output root files by running the bash scripts:

```bash
./hadd_all.sh $1 - merge all jobs
./hadd_data.sh $1 - merge data only jobs 
./hadd_bkgd.sh $1 - merge background MC only jobs 
./hadd_signal.sh $1 - merge signal only jobs 

```

## Description of organizational details

${year} directory:

`${your_directory}/Hbb_MSSM/Run${year}/`

Filelists and configuration files:

`ConfigFileMaker.sh`


### Interpolation procedure

`ForInterpolation.C:`

* For each interpolated mass point a horizontal interpolation between two neighboring template models is performed for all relevant histograms

(e.g for m12 = 325 GeV, official mass points 300 and 350 GeV are used, the following list of histograms is interpolated: 
 
 m12_aac, m12_aac_JER_up, m12_aac_JER_down, m12_aac_JES_up, m12_aac_JES_down, TH1F	m12_aac_PU_up, m12_aac_PU_down, m12_aac_SFbtag_up, 
 
 m12_aac_SFbtag_down, m12_aac_jet_trigeff_up, m12_aac_jet_trigeff_down, m12_aac_onlSFbtag_up, and m12_aac_onlSFbtag_down
 
* The values of the parameters of the fit for mass points 300, 350, 400, and 450 GeV are stored (to check the stability of the fit parameters as a function of the mass of the dijet system) 

`GetFittingPar()` `Parameters_ForInterpolation.root`  `GetFittingPar/`

* Create and save a root file per interpolated mass point with all the relevant histograms (identical to the output of running the analysis for the official mass points)

`SaveAll()`  `SignalRootFiles_v1/`


### Parametrization of signal and background

* Fit signal and background on the CR and SRs using the mini-framework created to study the signal and background parametrizations ([https://github.com/desy-cms/analysis-models](https://github.com/desy-cms/analysis-models))

`FitBkgdandSignal_unbinned.sh`  `results/`

`FitBkgdandSignal_binned.sh`    `results/`


### Creation of workspaces containg signal parametrization

`${your_directory}/Hbb_MSSM/Run2017/`

`CreateSignalTemplates_FH.C`

`CreateSignalTemplates_SL.C`

`${your_directory}/Hbb_MSSM/Run2018/`

`CreateSignalTemplates_FH.C`


### Creation of workspaces for statistical inference procedure

`${your_directory}/Hbb_MSSM/Run${year}/`

`AnalysisWorkspace${SR}.C`

`${SR} = 1, 2, 3, 4`


#### Limit computation 
`${your_directory}/Hbb_MSSM/Run${year}/Inputs/datacards/`

Run combine tool locally:

`runLimits.sh`


### Plotting macros 

#### Plot signal shapes of 3 mass points (e.g. 300, 350, and 400 GeV):

`PlotSignalDistributions.C`

`PlotAll()` `Figs/Signal_Shapes/`


#### Plot all signal shapes together:

`PlotSignalDistributions_all.C` 

`PlotAll()` `Figs/Signal_Shapes/`


#### Validation of signal morphing (comparing for an official mass point the shape of m12 obtained from the interpolation procedure and the output distribution from running the analysis):
 
`CheckInterpolation.C`

`PlotAll()` `Figs/Interpolation/`


#### Plot signal shapes of 3 mass points, one interpolated and two official mass points (e.g. 300, 325, and 350 GeV) (for the nominal shape and the up/down variations of JER and JES):

`PlotInterpolation.C`

`PlotAll()` `Figs/Interpolation/`


#### To plot the m12 distribution for the official mass points (all fitted with a bukin function using the RooBukin function implemented in the library RooFit)
  
`FittingDemo_m12.C`
 
`PlotAll()` `Figs/SignalFits_v1/`


#### To rebin and normalise to 1 pb the signal templates (normalization values taken from Paul's macro CombineAndNormSignalTemplates.C) - for ReReco dataset
 
`RebinAndNormSignalTemplates.C`

`SaveAll()` `SignalRootFiles_v1/AllSignals_v1.root`


#### To read the signal tree and fill a new tree with a subset of the total number of events

`CopyTree.C`

`CopyAll()` `SignalRootFiles_reducedstats/`


### Run 2 combination directory (work in progress)

`${your_directory}/Hbb_MSSM/Run2Combination/`

Script to copy the datacards from 2017 and 2018 folders:

`CopyAll.sh`

#### Run combine tool:

`runLimits.sh`

Plot limits:

`PlotLimits.C`


If further clarifications are needed please contact: [sandra.consuegra.rodriguez@desy.de](sandra.consuegra.rodriguez@desy.de), [sandra.consuegra.rodriguez@cern.ch](sandra.consuegra.rodriguez@cern.ch)

#### Information last updated: 25.03.2022
