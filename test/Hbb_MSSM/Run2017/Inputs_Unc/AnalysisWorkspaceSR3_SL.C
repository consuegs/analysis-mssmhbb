/////////////////////////////////////////////////////////////////////////////////////////
//
//    Original code from Paul Asmuss (https://github.com/pasmuss/analysis-combine)
//    Edited by Sandra Consuegra Rodríguez (sandra.consuegra.rodriguez@desy.de)
//    Edited by Chayanit Asawatangtrakuldee for Semi-leptonic channel (chayanit@cern.ch)
//
//    This code creates workspaces needed to to be used as input for statistical analysis 
//
/////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
#include "TH1.h"
#include "TStyle.h"
#include "TMath.h"
#include <iostream>
#include "RooWorkspace.h"
using namespace std;
using namespace RooFit;

int AnalysisWorkspaceSR3_SL()
{

        std::ofstream textout("figs/AnalysisWorkspaceSR3_SL.txt");
	TString dir("/nfs/dust/cms/user/consuegs/Analyses/Hbb_MSSM/analysis-mssmhbb/test/Hbb_MSSM/Run2017/");

	int rebin = 10;

	// As usual, load the combine library to get access to the RooParametricHist
	gSystem->Load("libHiggsAnalysisCombinedLimit.so");

	vector<double> lumiscalefactors = { 53.34, 53.48, 53.85, 54.77, 58.91 };	//SR3
	vector<string> srmasses = { "400", "450", "500", "600", "700" };	//SR3

	TString Tsrmasses[5] = { "400", "450", "500", "600", "700" };	//SR3

	if (!(lumiscalefactors.size() == srmasses.size()))
	{
		cout << "Number of mass points and lumi scale factors does not agree. Please check what you provided." << endl;
		return -1;
	}
	map<string, double> assignedlumisf;
	for (unsigned int massvalue = 0; massvalue < srmasses.size(); massvalue++)
	{
		assignedlumisf[srmasses[massvalue]] = 1. / lumiscalefactors[massvalue];
	}

	// A search in a mbb tail, define mbb as our variable
	RooRealVar mbb("mbb", "m_{12}", 240, 800);	//SR3: 400, 450, 500, 600, 700
	RooArgList vars(mbb);

	for (unsigned int mass = 0; mass < srmasses.size(); mass++)
	{
		cout << endl;
		cout << endl;
		cout << "mass " << srmasses[mass];

		///
		/// GET SIG NORMALIZATION 
		///

		TFile *f_signal_in = new TFile(dir + "/forSandra/Sep2022_v6/SL/Central/SL_SUSYGluGluToBBHToBB_M-" + Tsrmasses[mass] + "_2017-v6.root", "READ");	//SR (always), 3j (for now: inclusive)
		TH1F *h_signal_in = (TH1F*) f_signal_in->Get("mbb");
		double lumisf = assignedlumisf[srmasses[mass]];
		cout << "  lumi sf = " << lumisf;
		double normSignal = h_signal_in->GetSum() *lumisf;
		cout << "  norm signal = " << normSignal << std::endl;
		h_signal_in->Scale(lumisf);
		RooDataHist sigHist("sigHist", "sigHist", mbb, h_signal_in);

		///
		/// GET DATA_OBS HISTS FOR CR/SR 
		///

		TFile *f_cr_in = new TFile(dir + "/forSandra/Feb2022_v6/SL/Semilep_CR_BTagCSV_UL2017-v6.root", "READ");	//CR, SL 2017
		TH1F *h_cr_in = (TH1F*) f_cr_in->Get("mbb");
		h_cr_in->SetName("h_cr_in");
		h_cr_in->Rebin(rebin);
		int normCR = h_cr_in->GetEntries();
		cout << "normCR: " << normCR << endl;
		RooDataHist RDHCR("RDHCR", "CR", vars, h_cr_in);

		TFile *f_sr_in = new TFile(dir + "/forSandra/April2022_v6/SL/Semilep_SR_BTagCSV_UL2017-v6.root", "READ");
		TH1F *SRHist = (TH1F*) f_cr_in->Get("mbb");	//data_obs SR -> now using the data in CR with normalization from SR
		SRHist->SetName("SRHist");
		SRHist->Rebin(rebin);
		TH1F *SRHist_norm = (TH1F*) f_sr_in->Get("mbb");
		int normSR = SRHist_norm->GetEntries();
		RooDataHist RDHSR("RDHSR", "SR", vars, SRHist);

		///
		/// GET BG PARAMETRIZATION FROM ROOFIT
		///

		TFile *f_bgfit = new TFile(dir + "/forSandra/Feb2022_v6/SL/UL2017_background_novosibirsk_240to800_5GeV/workspace/FitContainer_workspace.root", "READ");
		RooWorkspace *w_bgfit = (RooWorkspace*) f_bgfit->Get("workspace");
		RooAbsPdf *background = w_bgfit->pdf("background");
		background->SetName("background");
		RooRealVar background_norm("background_norm", "Number of background events", normCR, 0, 1000000);

		///
		/// GET SIG PARAMETRIZATION FROM ROOFIT
		///

		TFile *f_signal_in_unbinned = new TFile(dir + "/input_doubleCB_SL/signal_m" + Tsrmasses[mass] + "_SR3.root", "READ");
		RooWorkspace *w_signalfit = (RooWorkspace*) f_signal_in_unbinned->Get("w");
		RooAbsPdf *signalx = w_signalfit->pdf("signal_dcb");
		signalx->SetName("signal");
		//RooRealVar signal_norm("signal_norm", "signal_norm", normSignal);

		TFile *f_signal_in_unbinned_JER_Up = new TFile(dir + "/input_doubleCB_SL/signal_m" + Tsrmasses[mass] + "_SR3_JER_1sigmaup.root", "READ");
		RooWorkspace *w_signalfit_JER_Up = (RooWorkspace*) f_signal_in_unbinned_JER_Up->Get("w");
		RooAbsPdf *signalx_JER_Up = w_signalfit_JER_Up->pdf("signal_dcb");

		TFile *f_signal_in_unbinned_JER_Down = new TFile(dir + "/input_doubleCB_SL/signal_m" + Tsrmasses[mass] + "_SR3_JER_1sigmadown.root", "READ");
		RooWorkspace *w_signalfit_JER_Down = (RooWorkspace*) f_signal_in_unbinned_JER_Down->Get("w");
		RooAbsPdf *signalx_JER_Down = w_signalfit_JER_Down->pdf("signal_dcb");

		TFile *f_signal_in_unbinned_JES_Up = new TFile(dir + "/input_doubleCB_SL/signal_m" + Tsrmasses[mass] + "_SR3_JES_1sigmaup.root", "READ");
		RooWorkspace *w_signalfit_JES_Up = (RooWorkspace*) f_signal_in_unbinned_JES_Up->Get("w");
		RooAbsPdf *signalx_JES_Up = w_signalfit_JES_Up->pdf("signal_dcb");

		TFile *f_signal_in_unbinned_JES_Down = new TFile(dir + "/input_doubleCB_SL/signal_m" + Tsrmasses[mass] + "_SR3_JES_1sigmadown.root", "READ");
		RooWorkspace *w_signalfit_JES_Down = (RooWorkspace*) f_signal_in_unbinned_JES_Down->Get("w");
		RooAbsPdf *signalx_JES_Down = w_signalfit_JES_Down->pdf("signal_dcb");
		
		//TFile *f_signal_in_unbinned_JKTE_Up = new TFile(dir + "/input_doubleCB_SL/signal_m" + Tsrmasses[mass] + "_SR3_JKTE_1sigmaup.root", "READ");
                //RooWorkspace *w_signalfit_JKTE_Up = (RooWorkspace*) f_signal_in_unbinned_JKTE_Up->Get("w");
                //RooAbsPdf *signalx_JKTE_Up = w_signalfit_JKTE_Up->pdf("signal_dcb");
       
                //TFile *f_signal_in_unbinned_JKTE_Down = new TFile(dir + "/input_doubleCB_SL/signal_m" + Tsrmasses[mass] + "_SR3_JKTE_1sigmadown.root", "READ");
                //RooWorkspace *w_signalfit_JKTE_Down = (RooWorkspace*) f_signal_in_unbinned_JKTE_Down->Get("w");
                //RooAbsPdf *signalx_JKTE_Down = w_signalfit_JKTE_Down->pdf("signal_dcb");

		RooRealVar *mean_ws = (RooRealVar*) w_signalfit->var("mean");
		RooRealVar *sigma_ws = (RooRealVar*) w_signalfit->var("sigma");
		RooRealVar *alpha1_ws = (RooRealVar*) w_signalfit->var("alpha1");
		RooRealVar *alpha2_ws = (RooRealVar*) w_signalfit->var("alpha2");
		RooRealVar *n1_ws = (RooRealVar*) w_signalfit->var("n1");
		RooRealVar *n2_ws = (RooRealVar*) w_signalfit->var("n2");
		mean_ws->setConstant(true);
		sigma_ws->setConstant(true);
		alpha1_ws->setConstant(true);
		alpha2_ws->setConstant(true);
		n1_ws->setConstant(true);
		n2_ws->setConstant(true);
		cout << "mean       = " << mean_ws->getVal() << endl;
		cout << "sigma     = " << sigma_ws->getVal() << endl;
		cout << "alpha1     = " << alpha1_ws->getVal() << endl;
		cout << "alpha2 = " << alpha2_ws->getVal() << endl;
		cout << "n1 = " << n1_ws->getVal() << endl;
		cout << "n2 = " << n2_ws->getVal() << endl;

		RooRealVar *mean_JES_Up = (RooRealVar*) w_signalfit_JES_Up->var("mean");
		RooRealVar *mean_JES_Down = (RooRealVar*) w_signalfit_JES_Down->var("mean");

		mean_JES_Up->setConstant(true);
		mean_JES_Down->setConstant(true);

		RooRealVar *sigma_JER_Up = (RooRealVar*) w_signalfit_JER_Up->var("sigma");
		RooRealVar *sigma_JER_Down = (RooRealVar*) w_signalfit_JER_Down->var("sigma");

		sigma_JER_Up->setConstant(true);
		sigma_JER_Down->setConstant(true);		
		
		//RooRealVar *sigma_JKTE_Up = (RooRealVar*) w_signalfit_JKTE_Up->var("sigma");
		//RooRealVar *sigma_JKTE_Down = (RooRealVar*) w_signalfit_JKTE_Down->var("sigma");

		//sigma_JKTE_Up->setConstant(true);
		//sigma_JKTE_Down->setConstant(true);
		
	        ///
		/// SYSTEMATIC VARIATIONS OF THE SIGNAL SHAPE PARAMETERS
		///
		RooRealVar theta_JES("CMS_JES_2017", "CMS_JES_2017", 0., -5., 5.);
		RooRealVar theta_JER("CMS_JER_2017", "CMS_JER_2017", 0., -5., 5.);
		//RooRealVar theta_JKTE("CMS_JKTE_2017", "CMS_JKTE_2017", 0., -5., 5.);	

		double Mean = 0.5 *(mean_JES_Up->getVal() + mean_JES_Down->getVal());
		double d_Mean = mean_JES_Up->getVal() - Mean;

		double Sigma_JER = 0.5 *(sigma_JER_Up->getVal() + sigma_JER_Down->getVal());
		double d_Sigma_JER = sigma_JER_Up->getVal() - Sigma_JER;		
		
		//double Sigma_JKTE =  0.5 *(sigma_JKTE_Up->getVal() + sigma_JKTE_Down->getVal());
		//double d_Sigma_JKTE = sigma_JKTE_Up->getVal() - Sigma_JKTE;
		
		//double Sigma = 0.5 *(Sigma_JER + Sigma_JKTE);
		double Sigma = 0.5 *(Sigma_JER);

		RooRealVar shift_JES_mean("shift_JES_mean", "shift_JES_mean", d_Mean, d_Mean - 1.0, d_Mean + 1.0);
		RooRealVar shift_JER_Sigma("shift_JER_Sigma", "shift_JER_Sigma", d_Sigma_JER, d_Sigma_JER - 1.0, d_Sigma_JER + 1.0);
		//RooRealVar shift_JKTE_Sigma("shift_JKTE_Sigma", "shift_JKTE_Sigma", d_Sigma_JKTE, d_Sigma_JKTE - 1.0, d_Sigma_JKTE + 1.0);

		RooRealVar mean("mean", "mean", 300, 280, 2000);
		RooRealVar sigma("sigma", "sigma", 30, 20, 90);
		RooRealVar alpha1("alpha1", "alpha1", 0.8, 0.1, 20);
		RooRealVar alpha2("alpha2", "alpha2", 20, 0.5, 35);
		RooRealVar n1("n1", "n1", 130, 1, 200);
		RooRealVar n2("n2", "n2", 15, 1, 25);

		mean.setVal(Mean);
		sigma.setVal(Sigma);
		alpha1.setVal(alpha1_ws->getVal());
		alpha2.setVal(alpha2_ws->getVal());
		n1.setVal(n1_ws->getVal());
		n2.setVal(n2_ws->getVal());

		mean.setConstant(true);
		sigma.setConstant(true);
		alpha1.setConstant(true);
		alpha2.setConstant(true);
		n1.setConstant(true);
		n2.setConstant(true);

		RooFormulaVar mean_shifted("mean_shifted",
			"@0 + @1*@2",
			RooArgList(mean, theta_JES, shift_JES_mean));
		RooFormulaVar sigma_shifted("sigma_shifted",
			"@0 + @1*@2",
			RooArgList(sigma, theta_JER, shift_JER_Sigma));
			
		//RooFormulaVar sigma_shifted("sigma_shifted",
		//	"@0 + @1*@2 + @3*@4",
		//	RooArgList(sigma, theta_JER, shift_JER_Sigma, theta_JKTE, shift_JKTE_Sigma));

		double normSR_JES_Up, normSR_JES_Down, normSR_JER_Up, normSR_JER_Down;

		TFile fileJesUp(dir + "/forSandra/Sep2022_v6/SL/JECup/SL_SUSYGluGluToBBHToBB_M-" + Tsrmasses[mass] + "_2017-v6.root");
		TH1F *SRHist_JES_Up = (TH1F*) fileJesUp.Get("mbb");
		normSR_JES_Up = SRHist_JES_Up->GetSumOfWeights() *lumisf;

		TFile fileJesDown(dir + "/forSandra/Sep2022_v6/SL/JECdown/SL_SUSYGluGluToBBHToBB_M-" + Tsrmasses[mass] + "_2017-v6.root");
		TH1F *SRHist_JES_Down = (TH1F*) fileJesDown.Get("mbb");
		normSR_JES_Down = SRHist_JES_Down->GetSumOfWeights() *lumisf;

		TFile fileJerUp(dir + "/forSandra/Sep2022_v6/SL/JERup/SL_SUSYGluGluToBBHToBB_M-" + Tsrmasses[mass] + "_2017-v6.root");
		TH1F *SRHist_JER_Up = (TH1F*) fileJerUp.Get("mbb");
		normSR_JER_Up = SRHist_JER_Up->GetSumOfWeights() *lumisf;

		TFile fileJerDown(dir + "/forSandra/Sep2022_v6/SL/JERdown/SL_SUSYGluGluToBBHToBB_M-" + Tsrmasses[mass] + "_2017-v6.root");
		TH1F *SRHist_JER_Down = (TH1F*) fileJerDown.Get("mbb");
		normSR_JER_Down = SRHist_JER_Down->GetSumOfWeights() *lumisf;

		RooDoubleCB signal("signal", "DoubleCB", mbb, mean_shifted, sigma_shifted, alpha1, n1, alpha2, n2);

		double d_norm_JES_Up = normSR_JES_Up - normSignal;
		double d_norm_JES_Down = normSignal - normSR_JES_Down;
		double d_norm_JER_Up = normSR_JER_Up - normSignal;
		double d_norm_JER_Down = normSignal - normSR_JER_Down;

		RooRealVar norm("norm", "norm", normSignal, 0., 2. *normSignal);
		RooRealVar norm_JES_Up("norm_JES_Up", "norm_JES_Up", d_norm_JES_Up, -100., 100.);
		RooRealVar norm_JES_Down("norm_JES_Down", "norm_JES_Down", d_norm_JES_Down, -100., 100.);
		RooRealVar norm_JER_Up("norm_JER_Up", "norm_JER_Up", d_norm_JER_Up, -100., 100.);
		RooRealVar norm_JER_Down("norm_JER_Down", "norm_JER_Down", d_norm_JER_Down, -100., 100.);

		RooFormulaVar signal_norm("signal_norm",
			"@0 + (@1>=0.0)*@1*@2 + (@1 < 0.0)*@1*@3",
			RooArgList(norm, theta_JES, norm_JES_Up, norm_JES_Down));

		norm.setVal(normSignal);
		norm_JES_Up.setVal(d_norm_JES_Up);
		norm_JES_Down.setVal(d_norm_JES_Down);
		norm_JER_Up.setVal(d_norm_JER_Up);
		norm_JER_Down.setVal(d_norm_JER_Down);

		norm.setConstant(true);
		norm_JES_Up.setConstant(true);
		norm_JES_Down.setConstant(true);
		norm_JER_Up.setConstant(true);
		norm_JER_Down.setConstant(true);

		textout << "mass = " << Tsrmasses[mass] << endl;
		textout << "signal normalization -> " << endl;
		textout << "norm          = " << normSignal << endl;
		textout << "norm_JES_Up   = " << normSR_JES_Up << endl;
		textout << "norm_JES_Down = " << normSR_JES_Down << endl;
		textout << "norm_JER_Up   = " << normSR_JER_Up << endl;
		textout << "norm_JER_Down = " << normSR_JER_Down << endl;
		textout << endl;

		RooPlot *xframe = mbb.frame();
		sigHist.plotOn(xframe, LineColor(1), MarkerColor(1));
		signalx->plotOn(xframe, LineColor(2));
		TCanvas *c1 = new TCanvas("c1", "c1", 600, 600);
		xframe->Draw();
		c1->Update();
		c1->Print("figs/sig_SR3_" + Tsrmasses[mass] + ".png");
		c1->Print("figs/sig_SR3_" + Tsrmasses[mass] + ".pdf");
		delete c1;

		///
		/// DEFINE TRANSFER FACTOR PDF
		///	

                RooRealVar offsetTF("offsetTF", "offset of TF in x direction", 30, -100, 100);
                RooRealVar steepnessTF("steepnessTF", "Steepness of rise in TF", 0.015, 0.001, 0.050);
                RooArgList varsTF(mbb, offsetTF, steepnessTF);
                RooGenericPdf TF("TF", "TF", "(1/(1+TMath::Exp(-steepnessTF*(mbb-offsetTF))))", varsTF);     //standard logistic
		cout << "RDHSR sum entries: " << RDHSR.sumEntries() << endl;
		RooRealVar signalregion_norm("signalregion_norm", "Signal normalization", normSR, 0.9 *normSR, 1.1 *normSR);

		//Output file
		TFile *fOut = new TFile("input_2017_SL/signal_workspace_" + Tsrmasses[mass] + "_SR3.root", "RECREATE");
		RooWorkspace wspace("wspace", "wspace");

		wspace.import(RDHCR);
		wspace.import(RDHSR);
		wspace.import(signal);
		wspace.import(*background);
		wspace.import(background_norm);
		wspace.import(signal_norm);
		wspace.import(TF);
		wspace.factory("PROD::signalregion(background,TF)");
		wspace.import(signalregion_norm);
		wspace.Write();
		cout << "File created: signal_workspace_" + Tsrmasses[mass] + "_SR3.root" << endl;
		fOut->Close();
	}
	return 0;
}
