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

int AnalysisWorkspaceSR1_2017TF()
{

	TString dir("/nfs/dust/cms/user/consuegs/Analyses/Hbb_MSSM/analysis-mssmhbb/test/Hbb_MSSM/Run2018/");

	int rebin = 10;

	// As usual, load the combine library to get access to the RooParametricHist
	gSystem->Load("libHiggsAnalysisCombinedLimit.so");

	vector<double> lumiscalefactors = { 29.89, 29.82 };	//SR1
	vector<string> srmasses = { "300", "350" };	//SR1

	TString Tsrmasses[2] = { "300", "350" };	//SR1

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
	RooRealVar mbb("mbb", "m_{12}", 220, 520);	//SR 1: 300/350
	RooArgList vars(mbb);

	for (unsigned int mass = 0; mass < srmasses.size(); mass++)
	{
		cout << endl;
		cout << endl;
		cout << "mass " << srmasses[mass];

		///
		/// GET SIG NORMALIZATION 
		///

		TFile *f_signal_in = new TFile(dir + "/mssmHbb_FH_2018_MC_signal_MP_" + Tsrmasses[mass] + ".root", "READ");	//SR (always), 3j (for now: inclusive)
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

		TFile *f_cr_in = new TFile(dir + "/mssmhbb_FH_2018_DataABCD_CR.root", "READ");	//CR, 3j, full 2018
		TH1F *h_cr_in = (TH1F*) f_cr_in->Get("mbb");
		h_cr_in->SetName("h_cr_in");
		h_cr_in->Rebin(rebin);
		int normCR = h_cr_in->GetEntries();
		cout << "normCR: " << normCR << endl;
		RooDataHist RDHCR("RDHCR", "CR", vars, h_cr_in);

		TFile *f_sr_in = new TFile(dir + "/mssmhbb_FH_2018_DataABCD_CR.root", "READ");
		TH1F *SRHist = (TH1F*) f_sr_in->Get("mbb");	//data_obs SR
		SRHist->SetName("SRHist");
		SRHist->Rebin(rebin);
		//int normSR = SRHist->GetEntries();
		int normSR = 280889;
		cout << "normSR: " << normSR << endl;
		RooDataHist RDHSR("RDHSR", "SR", vars, SRHist);

		///
		/// GET BG PARAMETRIZATION FROM ROOFIT
		///

		TFile *f_bgfit = new TFile(dir + "/workspaces_mssmhbb_UL2018/UL_2018_background_FR1_260to550_extnovosibirsk/workspace/FitContainer_workspace.root", "READ");
		RooWorkspace *w_bgfit = (RooWorkspace*) f_bgfit->Get("workspace");
		RooAbsPdf *background = w_bgfit->pdf("background");
		background->SetName("background");
		RooRealVar background_norm("background_norm", "Number of background events", normCR, 0, 1000000);

		///
		/// GET SIG PARAMETRIZATION FROM ROOFIT
		///

		TFile *f_signal_in_unbinned = new TFile(dir + "/input_doubleCB/signal_m" + Tsrmasses[mass] + "_SR1.root", "READ");
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
		c1->Print("figs/sig_SR1_" + Tsrmasses[mass] + ".png");
		c1->Print("figs/sig_SR1_" + Tsrmasses[mass] + ".pdf");
		delete c1;

		///
		/// DEFINE TRANSFER FACTOR PDF
		///	

		RooRealVar offsetTF("offsetTF", "offset of TF in x direction", 195, 100, 250);
		RooRealVar steepnessTF("steepnessTF", "Steepness of rise in TF", 0.0056, 0.001, 0.05);
		RooRealVar slopelinTF("slopelinTF", "Slope of lienar decrease for extended functions", 2.41e-5, 1e-6, 1e-4);
		RooRealVar alpha("alpha", "Modification of shape", 0.38, 0.0, 2.0);
		RooArgList varsTF(mbb, alpha, offsetTF, steepnessTF, slopelinTF);
		RooGenericPdf TF("TF", "TF", "(1+alpha*TMath::Exp(-steepnessTF*(mbb-offsetTF)))/(1+TMath::Exp(-steepnessTF*(mbb-offsetTF)))*(1-slopelinTF*mbb)", varsTF);	//(ext) (mod) logistic
		cout << "RDHSR sum entries: " << RDHSR.sumEntries() << endl;
		RooRealVar signalregion_norm("signalregion_norm", "Signal normalization", normSR, 0.9 *normSR, 1.1 *normSR);

		//Output file
		TFile *fOut = new TFile("input_2018_2017TF_FH/signal_workspace_" + Tsrmasses[mass] + ".root", "RECREATE");
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
		cout << "File created: signal_workspace_" + Tsrmasses[mass] + ".root" << endl;
		fOut->Close();
	}
	return 0;
}
