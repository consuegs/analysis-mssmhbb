/////////////////////////////////////////////////////////////////////////////////////////
//
//    Original code from Paul Asmuss (https://github.com/pasmuss/analysis-combine)
//    Edited by Sandra Consuegra Rodríguez (sandra.consuegra.rodriguez@desy.de)
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

int AnalysisWorkspaceSR2_OldMatchS()
{

	std::ofstream textout("figs/AnalysisWorkspaceSR2_OldMatchS.txt");
	TString dir("/nfs/dust/cms/user/consuegs/Analyses/Hbb_MSSM/analysis-mssmhbb/test/Hbb_MSSM/Run2018/");

	int rebin = 1;

	// As usual, load the combine library to get access to the RooParametricHist
	gSystem->Load("libHiggsAnalysisCombinedLimit.so");

	vector<double> lumiscalefactors = { 29.64, 23.26, 29.35, 36.57, 36.43 };	//SR2
	vector<string> srmasses = { "400", "450", "500", "600", "700" };	//SR2

	TString Tsrmasses[5] = { "400", "450", "500", "600", "700" };	//SR2

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
	RooRealVar mbb("mbb", "m_{12}", 320, 800);	//SR 2: 400/450/500/600/700
	RooArgList vars(mbb);

	for (unsigned int mass = 0; mass < srmasses.size(); mass++)
	{
		cout << endl;
		cout << endl;
		cout << "mass " << srmasses[mass];

		///
		/// GET SIG NORMALIZATION 
		/// 

		TFile *f_signal_in = new TFile(dir + "/mssmHbb_FH_2018_MC_signal_MP_" + Tsrmasses[mass] + ".root", "READ");		
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
		
		TFile *f_cr_in = new TFile(dir + "/mssmhbb_FH_2018_DataABCD_CR_threshold_130-130.root", "READ");
		TH1F *h_cr_in = (TH1F*) f_cr_in->Get("mbb");
		h_cr_in->SetName("h_cr_in");
		h_cr_in->Rebin(rebin);
		int normCR = h_cr_in->GetEntries();
		cout << "normCR: " << normCR << endl;
		RooDataHist RDHCR("RDHCR", "CR", vars, h_cr_in);
		
		TFile *f_sr_in = new TFile(dir + "/mssmhbb_FH_2018_DataABCD_SR.root", "READ");
		TH1F *SRHist_norm = (TH1F*) f_sr_in->Get("mbb");
		TH1F *SRHist = (TH1F*) f_cr_in->Get("mbb");	//data_obs CR -> now using the data in CR with normalization from SR
		SRHist->SetName("SRHist");
		SRHist->Rebin(rebin);
		int normSR = SRHist_norm->GetEntries();
		cout << "normSR: " << normSR << endl;
		RooDataHist RDHSR("RDHSR", "SR", vars, SRHist);

		///
		/// GET BG PARAMETRIZATION FROM ROOFIT
		///

		TFile *f_bgfit = new TFile(dir + "/workspaces_mssmhbb_UL2018/UL_2018_background_FR2_320to800_extnovosibirsk/workspace/FitContainer_workspace.root", "READ");
		RooWorkspace *w_bgfit = (RooWorkspace*) f_bgfit->Get("workspace");
		RooAbsPdf *background = w_bgfit->pdf("background");
		RooRealVar background_norm("background_norm", "Number of background events", normCR, 0.9 *normCR, 1.1 *normCR);
		
		///
		/// GET SIG PARAMETRIZATION FROM ROOFIT
		///

		TFile *f_signal_in_unbinned = new TFile(dir + "/input_doubleCB/signal_m" + Tsrmasses[mass] + "_SR2.root", "READ");
		RooWorkspace *w_signalfit = (RooWorkspace*) f_signal_in_unbinned->Get("w");
		RooAbsPdf *signal = w_signalfit->pdf("signal_dcb");
		signal->SetName("signal");
		RooRealVar signal_norm("signal_norm", "signal_norm", normSignal);

		RooRealVar * mean = (RooRealVar*)w_signalfit->var("mean");
		RooRealVar * sigma = (RooRealVar*)w_signalfit->var("sigma");
		RooRealVar * alpha1 = (RooRealVar*)w_signalfit->var("alpha1");
		RooRealVar * alpha2 = (RooRealVar*)w_signalfit->var("alpha2");
		RooRealVar * n1 = (RooRealVar*)w_signalfit->var("n1");
		RooRealVar * n2 = (RooRealVar*)w_signalfit->var("n2");
		mean->setConstant(true);
		sigma->setConstant(true);
		alpha1->setConstant(true);
		alpha2->setConstant(true);
		n1->setConstant(true);
		n2->setConstant(true);
		cout << "mean       = " << mean->getVal() << endl;
		cout << "sigma     = " << sigma->getVal() << endl;
		cout << "alpha1     = " << alpha1->getVal() << endl;
		cout << "alpha2 = " << alpha2->getVal() << endl;
		cout << "n1 = " << n1->getVal() << endl;
		cout << "n2 = " << n2->getVal() << endl;

		RooPlot *xframe = mbb.frame();
		sigHist.plotOn(xframe, LineColor(1), MarkerColor(1));
		signal->plotOn(xframe, LineColor(2));
		TCanvas *c1 = new TCanvas("c1", "c1", 600, 600);
		xframe->Draw();
		c1->Update();
		c1->Print("figs_OldMatchS/sig_SR2_" + Tsrmasses[mass] + ".png");
		c1->Print("figs_OldMatchS/sig_SR2_" + Tsrmasses[mass] + ".pdf");
		delete c1;

		///
		/// DEFINE TRANSFER FACTOR PDF
		///		
		
		double x0_centralValue = -1.43012e+04;
		double k_centralValue = -2.40384e-04;
		double norm_centralValue = -1.45644e-01;

		RooRealVar x0("x0", "x0", x0_centralValue, 100 *x0_centralValue, 0.01 *x0_centralValue);
		RooRealVar k("k", "k", k_centralValue, 100 *k_centralValue, 0.01 *k_centralValue);
		RooRealVar norm("norm", "norm", norm_centralValue, 100 *norm_centralValue, 0.01 *norm_centralValue);
		RooArgList varsTF(mbb, x0, k, norm);
		RooGenericPdf TF("TF", "TF", "norm*erf(k*(mbb-x0))", varsTF);	
		cout << "RDHSR sum entries: " << RDHSR.sumEntries() << endl;
		RooRealVar signalregion_norm("signalregion_norm", "Signal normalization", normSR, 0.9 *normSR, 1.1 *normSR);

		norm.setConstant(true);
		cout << "x0       = " << x0.getVal() << endl;
		cout << "k     = " << k.getVal() << endl;
		cout << "norm     = " << norm.getVal() << endl;

		//Output file
		TFile *fOut = new TFile("input_2018_FH_OldMatchS/signal_workspace_" + Tsrmasses[mass] + "_SR2.root", "RECREATE");
		RooWorkspace wspace("wspace", "wspace");

		wspace.import(RDHCR);
		wspace.import(RDHSR);
		wspace.import(*signal);
		wspace.import(*background);
		wspace.import(background_norm);
		wspace.import(signal_norm);
		wspace.import(TF);
		wspace.factory("PROD::signalregion(background,TF)");
		wspace.import(signalregion_norm);
		wspace.Write();
		cout << "File created: signal_workspace_" + Tsrmasses[mass] + "_SR2.root" << endl;
		fOut->Close();
	}
	return 0;
}
