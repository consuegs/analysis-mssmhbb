#!/bin/sh 
# $1 - SR, CR or VR

#Background Model Fit 
FitModel -t JetHT_Run2017-deep-$1-3j.root -o  results/DataDrivenBkgdModel-$1-3j/BernsteinEffProd/200to500_binned --fit_min 200 --fit_max 500 --nbins 30 --type background --model berneffprod
FitModel -t JetHT_Run2017-deep-$1-3j.root -o  results/DataDrivenBkgdModel-$1-3j/ExtNovoEffProd/260to785_binned --fit_min 260 --fit_max 785 --nbins 30 --type background --model extnovoeffprod
FitModel -t JetHT_Run2017-deep-$1-3j.root -o  results/DataDrivenBkgdModel-$1-3j/Novosibirsk/390to1270_binned --fit_min 390 --fit_max 1270 --nbins 30 --type background --model mynovosibirsk
FitModel -t JetHT_Run2017-deep-$1-3j.root -o  results/DataDrivenBkgdModel-$1-3j/Novosibirsk/500to2000_binned --fit_min 500 --fit_max 2000 --nbins 30 --type background --model mynovosibirsk

#Signal Model Fit 
FitModel -i /nfs/dust/cms/user/consuegs/Analyses/Hbb_MSMSM/analysis-mssmhbb/test/Hbb_MSMSM/Run2017/SignalRootFiles_v1/mc-sig-300-NLO-deep-$1-3j.root -o results/mc-sig-300-NLO-deep-$1-3j_binned --fit_min 200 --fit_max 500 --nbins 30 --type background --model doublegausexp
FitModel -i /nfs/dust/cms/user/consuegs/Analyses/Hbb_MSMSM/analysis-mssmhbb/test/Hbb_MSMSM/Run2017/SignalRootFiles_v1/mc-sig-350-NLO-deep-$1-3j.root -o results/mc-sig-350-NLO-deep-$1-3j_binned --fit_min 200 --fit_max 500 --nbins 30 --type background --model doublegausexp
FitModel -i /nfs/dust/cms/user/consuegs/Analyses/Hbb_MSMSM/analysis-mssmhbb/test/Hbb_MSMSM/Run2017/SignalRootFiles_v1/mc-sig-400-NLO-deep-$1-3j.root -o results/mc-sig-400-NLO-deep-$1-3j_binned --fit_min 200 --fit_max 500 --nbins 30 --type background --model doublegausexp
FitModel -i /nfs/dust/cms/user/consuegs/Analyses/Hbb_MSMSM/analysis-mssmhbb/test/Hbb_MSMSM/Run2017/SignalRootFiles_v1/mc-sig-450-NLO-deep-$1-3j.root -o results/mc-sig-450-NLO-deep-$1-3j_binned --fit_min 260 --fit_max 785 --nbins 52 --type background --model doublegausexp
FitModel -i /nfs/dust/cms/user/consuegs/Analyses/Hbb_MSMSM/analysis-mssmhbb/test/Hbb_MSMSM/Run2017/SignalRootFiles_v1/mc-sig-500-NLO-deep-$1-3j.root -o results/mc-sig-500-NLO-deep-$1-3j_binned --fit_min 260 --fit_max 785 --nbins 52 --type background --model bukin
FitModel -i /nfs/dust/cms/user/consuegs/Analyses/Hbb_MSMSM/analysis-mssmhbb/test/Hbb_MSMSM/Run2017/SignalRootFiles_v1/mc-sig-600-NLO-deep-$1-3j.root -o results/mc-sig-600-NLO-deep-$1-3j_binned --fit_min 260 --fit_max 785 --nbins 52 --type background --model quadgausexp
FitModel -i /nfs/dust/cms/user/consuegs/Analyses/Hbb_MSMSM/analysis-mssmhbb/test/Hbb_MSMSM/Run2017/SignalRootFiles_v1/mc-sig-700-NLO-deep-$1-3j.root -o results/mc-sig-700-NLO-deep-$1-3j_binned --fit_min 390 --fit_max 1270 --nbins 44 --type background --model bukin
FitModel -i /nfs/dust/cms/user/consuegs/Analyses/Hbb_MSMSM/analysis-mssmhbb/test/Hbb_MSMSM/Run2017/SignalRootFiles_v1/mc-sig-800-NLO-deep-$1-3j.root -o results/mc-sig-800-NLO-deep-$1-3j_binned --fit_min 390 --fit_max 1270 --nbins 44 --type background --model bukin
FitModel -i /nfs/dust/cms/user/consuegs/Analyses/Hbb_MSMSM/analysis-mssmhbb/test/Hbb_MSMSM/Run2017/SignalRootFiles_v1/mc-sig-900-NLO-deep-$1-3j.root -o results/mc-sig-900-NLO-deep-$1-3j_binned --fit_min 390 --fit_max 1270 --nbins 44 --type background --model bukin
FitModel -i /nfs/dust/cms/user/consuegs/Analyses/Hbb_MSMSM/analysis-mssmhbb/test/Hbb_MSMSM/Run2017/SignalRootFiles_v1/mc-sig-1000-NLO-deep-$1-3j.root -o results/mc-sig-1000-NLO-deep-$1-3j_binned --fit_min 390 --fit_max 1270 --nbins 44 --type background --model bukin
FitModel -i /nfs/dust/cms/user/consuegs/Analyses/Hbb_MSMSM/analysis-mssmhbb/test/Hbb_MSMSM/Run2017/SignalRootFiles_v1/mc-sig-1200-NLO-deep-$1-3j.root -o results/mc-sig-1200-NLO-deep-$1-3j_binned --fit_min 500 --fit_max 2000 --nbins 60 --type background --model bukin
FitModel -i /nfs/dust/cms/user/consuegs/Analyses/Hbb_MSMSM/analysis-mssmhbb/test/Hbb_MSMSM/Run2017/SignalRootFiles_v1/mc-sig-1400-NLO-deep-$1-3j.root -o results/mc-sig-1400-NLO-deep-$1-3j_binned --fit_min 500 --fit_max 2000 --nbins 60 --type background --model bukin
FitModel -i /nfs/dust/cms/user/consuegs/Analyses/Hbb_MSMSM/analysis-mssmhbb/test/Hbb_MSMSM/Run2017/SignalRootFiles_v1/mc-sig-1600-NLO-deep-$1-3j.root -o results/mc-sig-1600-NLO-deep-$1-3j_binned --fit_min 500 --fit_max 2000 --nbins 60 --type background --model bukin

#Signal Model Fit (alternative functions)
FitModel -i /nfs/dust/cms/user/consuegs/Analyses/Hbb_MSMSM/analysis-mssmhbb/test/Hbb_MSMSM/Run2017/SignalRootFiles_v1/mc-sig-300-NLO-deep-$1-3j.root -o results/mc-sig-300-NLO-deep-$1-3j-bukin_binned --fit_min 200 --fit_max 500 --nbins 30 --type background --model bukin
FitModel -i /nfs/dust/cms/user/consuegs/Analyses/Hbb_MSMSM/analysis-mssmhbb/test/Hbb_MSMSM/Run2017/SignalRootFiles_v1/mc-sig-350-NLO-deep-$1-3j.root -o results/mc-sig-350-NLO-deep-$1-3j-bukin_binned --fit_min 200 --fit_max 500 --nbins 30 --type background --model bukin
FitModel -i /nfs/dust/cms/user/consuegs/Analyses/Hbb_MSMSM/analysis-mssmhbb/test/Hbb_MSMSM/Run2017/SignalRootFiles_v1/mc-sig-400-NLO-deep-$1-3j.root -o results/mc-sig-400-NLO-deep-$1-3j-bukin_binned --fit_min 200 --fit_max 500 --nbins 30 --type background --model bukin
FitModel -i /nfs/dust/cms/user/consuegs/Analyses/Hbb_MSMSM/analysis-mssmhbb/test/Hbb_MSMSM/Run2017/SignalRootFiles_v1/mc-sig-450-NLO-deep-$1-3j.root -o results/mc-sig-450-NLO-deep-$1-3j-bukin_binned --fit_min 260 --fit_max 785 --nbins 52 --type background --model bukin
FitModel -i /nfs/dust/cms/user/consuegs/Analyses/Hbb_MSMSM/analysis-mssmhbb/test/Hbb_MSMSM/Run2017/SignalRootFiles_v1/mc-sig-600-NLO-deep-$1-3j.root -o results/mc-sig-600-NLO-deep-$1-3j-bukin_binned --fit_min 260 --fit_max 785 --nbins 52 --type background --model bukin

#Signal Model Fit (interpolated mass points)
FitModel -i /nfs/dust/cms/user/consuegs/Analyses/Hbb_MSMSM/analysis-mssmhbb/test/Hbb_MSMSM/Run2017/SignalRootFiles_v1/mc-sig-325-NLO-deep-$1-3j.root -o results/mc-sig-325-NLO-deep-$1-3j_binned --fit_min 200 --fit_max 500 --nbins 30 --type background --model doublegausexp
FitModel -i /nfs/dust/cms/user/consuegs/Analyses/Hbb_MSMSM/analysis-mssmhbb/test/Hbb_MSMSM/Run2017/SignalRootFiles_v1/mc-sig-375-NLO-deep-$1-3j.root -o results/mc-sig-375-NLO-deep-$1-3j_binned --fit_min 200 --fit_max 500 --nbins 30 --type background --model doublegausexp
FitModel -i /nfs/dust/cms/user/consuegs/Analyses/Hbb_MSMSM/analysis-mssmhbb/test/Hbb_MSMSM/Run2017/SignalRootFiles_v1/mc-sig-425-NLO-deep-$1-3j.root -o results/mc-sig-425-NLO-deep-$1-3j_binned --fit_min 260 --fit_max 785 --nbins 52 --type background --model doublegausexp


