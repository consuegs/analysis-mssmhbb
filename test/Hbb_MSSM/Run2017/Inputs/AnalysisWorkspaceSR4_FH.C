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

int AnalysisWorkspaceSR4_FH()
{

	TString dir("/nfs/dust/cms/user/consuegs/Analyses/Hbb_MSSM/analysis-mssmhbb/test/Hbb_MSSM/Run2017/");

	int rebin = 10;

	// As usual, load the combine library to get access to the RooParametricHist
	gSystem->Load("libHiggsAnalysisCombinedLimit.so");

	vector<double> lumiscalefactors = { 58.04, 56.04, 54.45, 53.08, 49.24 };	//SR4
	vector<string> srmasses = { "1000", "1200", "1400", "1600", "1800" };	//SR4

	TString Tsrmasses[5] = { "1000", "1200", "1400", "1600", "1800" };	//SR4

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
	RooRealVar mbb("mbb", "m_{12}", 500, 2000);	//SR 4: 1000/1200/1400/1600/1800
	RooArgList vars(mbb);

	for (unsigned int mass = 0; mass < srmasses.size(); mass++)
	{
		cout << endl;
		cout << endl;
		cout << "mass " << srmasses[mass];

		///
		/// GET SIG NORMALIZATION 
		///

		TFile *f_signal_in = new TFile(dir + "/forSandra/Sep2022_v6/FH/Central/FH_SUSYGluGluToBBHToBB_M-" + Tsrmasses[mass] + "_2017-v6.root", "READ");	//SR (always), 3j (for now: inclusive)
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

		TFile *f_cr_in = new TFile(dir + "/forSandra/April2022_v6/FH/FullhadCR_BTagCSV_UL2017-v6.root", "READ");	//CR, 3j, full 2017
		TH1F *h_cr_in = (TH1F*) f_cr_in->Get("mbb");
		h_cr_in->SetName("h_cr_in");
		h_cr_in->Rebin(rebin);
		int normCR = h_cr_in->GetEntries();
		cout << "normCR: " << normCR << endl;
		RooDataHist RDHCR("RDHCR", "CR", vars, h_cr_in);

		TFile *f_sr_in = new TFile(dir + "/forSandra/April2022_v6/FH/FullhadSR_BTagCSV_UL2017-v6.root", "READ");
		TH1F *SRHist = (TH1F*) f_cr_in->Get("mbb");	//data_obs SR -> now using the data in CR with normalization from SR
		SRHist->SetName("SRHist");
		SRHist->Rebin(rebin);
		TH1F *SRHist_norm = (TH1F*) f_sr_in->Get("mbb");
		int normSR = SRHist_norm->GetEntries();
		RooDataHist RDHSR("RDHSR", "SR", vars, SRHist);

		///
		/// GET BG PARAMETRIZATION FROM ROOFIT
		///

		TFile *f_bgfit = new TFile(dir + "/forSandra/April2022_v6/FH/UL2017_background_novosibirsk_500to2000_25GeV/workspace/FitContainer_workspace.root", "READ");
		RooWorkspace *w_bgfit = (RooWorkspace*) f_bgfit->Get("workspace");
		RooAbsPdf *background = w_bgfit->pdf("background");
		RooRealVar background_norm("background_norm", "Number of background events", normCR, 0, 1000000);

		///
		/// GET SIG PARAMETRIZATION FROM ROOFIT
		///

		TFile *f_signal_in_unbinned = new TFile(dir + "/input_doubleCB_FH/signal_m" + Tsrmasses[mass] + "_SR4.root", "READ");
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
		c1->Print("figs/sig_SR4_" + Tsrmasses[mass] + ".png");
		c1->Print("figs/sig_SR4_" + Tsrmasses[mass] + ".pdf");
		delete c1;

		///
		/// DEFINE TRANSFER FACTOR PDF
		///		
		
		RooRealVar offsetTF("offsetTF", "offset of TF in y direction", -590, -750, -250);
		RooRealVar slopelinTF("slopelinTF", "Slope of linear part of TF", 1.86e-4, -1e-4, 3e-4);
		RooRealVar steepnessTF("steepnessTF", "steepnes of erf", 0.0037, 0.0001, 0.03);
		RooArgList varsTF(mbb, offsetTF, slopelinTF, steepnessTF);
		RooGenericPdf TF("TF", "TF", "TMath::Erf(steepnessTF*(mbb-offsetTF))*(1-slopelinTF*mbb)", varsTF);
		cout << "RDHSR sum entries: " << RDHSR.sumEntries() << endl;
		RooRealVar signalregion_norm("signalregion_norm", "Signal normalization", normSR, 0.9 *normSR, 1.1 *normSR);

		//Output file
		TFile *fOut = new TFile("input_2017_FH/signal_workspace_" + Tsrmasses[mass]  + "_SR4.root", "RECREATE");
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
		cout << "File created: signal_workspace_" + Tsrmasses[mass] + "_SR4.root" << endl;
		fOut->Close();
	}
	return 0;
}
