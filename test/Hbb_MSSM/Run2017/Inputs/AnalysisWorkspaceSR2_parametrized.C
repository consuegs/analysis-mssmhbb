/////////////////////////////////////////////////////////////////////////////////////////
//
//    Original code from Paul Asmuss (https://github.com/pasmuss/analysis-combine)
//    Edited by Sandra Consuegra Rodríguez (sandra.consuegra.rodriguez@desy.de)
//
//    This code creates workspaces needed to to be used as input for statistical analysis 
//
/////////////////////////////////////////////////////////////////////////////////////////

#include "tdrstyle.C"
#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
#include "TH1.h"
#include "TStyle.h"
#include "TMath.h"
#include <iostream>
#include "RooWorkspace.h"
#include "HbbStylesNew.cc"
using namespace std;
using namespace RooFit;

int AnalysisWorkspaceSR2_parametrized()
{

	int normCR = 882853;	//FR2
	int normSR = 130003;	//FR2
	int rebin = 1;

	TString dir("/nfs/dust/cms/user/consuegs/Analyses/Hbb_MSSM/analysis-mssmhbb/test/Hbb_MSSM/Run2017/");

	// As usual, load the combine library to get access to the RooParametricHist
	gSystem->Load("libHiggsAnalysisCombinedLimit.so");

	vector<double> lumiscalefactors = { 75.24, 75.45, 64.51, 77.85, 70.42 };	//SR2
	vector<string> allmasses = { "400", "450", "500", "600", "700" };	//SR2

	TString Tsrmasses[5] = { "400", "450", "500", "600", "700" };	//SR2
	TString Tfunc[5] = {"dgaus","dgaus","bukin","qgaus","bukin"};

	if (!(lumiscalefactors.size() == allmasses.size()))
	{
		cout << "Number of mass points and lumi scale factors does not agree. Please check what you provided." << endl;
		return -1;
	}
	map<string, double> assignedlumisf;
	for (unsigned int massvalue = 0; massvalue < allmasses.size(); massvalue++)
	{
		assignedlumisf[allmasses[massvalue]] = 1. / lumiscalefactors[massvalue];
	}

	// A search in a mbb tail, define mbb as our variable
	RooRealVar mbb("mbb", "m_{12}", 260, 785);	//SR 2: 400/450/500/600/700
	RooArgList vars(mbb);
	vector<string> srmasses = { "400", "450", "500", "600", "700" };

	for (unsigned int mass = 0; mass < srmasses.size(); mass++)
	{
	  cout << endl;
	  cout << endl;
		cout << "mass " << srmasses[mass] << endl;
		// GET SIG NORMALIZATION

		TFile *f_signal_in = new TFile(dir+"/mc-sig-" + Tsrmasses[mass] + "-NLO-deep-SR-3j.root", "READ");	//SR (always), 3j (for now: inclusive)
		TH1F *h_signal_in = (TH1F*) f_signal_in->Get("m12_SR2_1GeV");
		double lumisf = assignedlumisf[srmasses[mass]];
		cout << "  lumi sf = " << lumisf;
		double normSignal = h_signal_in->GetSum()*lumisf;
		cout << "  norm signal = " << normSignal << std::endl;
		h_signal_in->Scale(lumisf);
		RooDataHist sigHist("sigHist","sigHist",mbb,h_signal_in);

		///
		/// GET DATA_OBS HISTS FOR CR/SR (CR FROM ANALYSIS MACRO, SR FOR NOW FROM TOYS)
		///

		TFile *f_cr_in = new TFile(dir+"/DataRootFiles/rereco-CDEF-deep-CR-3j.root", "READ");	//CR, 3j, full 2017
		TH1F *h_cr_in = (TH1F*) f_cr_in->Get("m12_SR2_1GeV");
		h_cr_in->SetName("h_cr_in");
		h_cr_in->Rebin(rebin);
		RooDataHist RDHCR("RDHCR", "CR", vars, h_cr_in);

		TFile *f_sr_in = new TFile(dir+"/DataRootFiles/rereco-CDEF-deep-SR-3j.root", "READ");
		TH1F *SRHist = (TH1F*) f_sr_in->Get("m12_SR2_1GeV");	//data_obs SR
		SRHist->SetName("SRHist");
		SRHist->Rebin(rebin);
		normSR = SRHist->Integral();
		RooDataHist RDHSR("RDHSR", "SR", vars, SRHist);

		///
		/// GET BG PARAMETRIZATION FROM ROOFIT
		///

		//TFile *f_bgfit = new TFile("../results/DataDrivenBkgdModel-CR-3j/ExtNovoEffProd/260to785/workspace/FitContainer_workspace.root", "READ");	//SR2
		TFile *f_bgfit = new TFile(dir+"/Inputs_Paul/FinalVersionAnalysis2017FH/BGparam/260to785/workspace/FitContainer_workspace.root", "READ");	//SR2
		RooWorkspace *w_bgfit = (RooWorkspace*) f_bgfit->Get("workspace");
		RooAbsPdf *background = w_bgfit->pdf("background");
		background->SetName("background");
		RooRealVar background_norm("background_norm", "Number of background events", normCR, 0, 1000000);

		///
		// GET SIG PARAMETERIZATION FROM ROOFIT
		///

		//TFile *f_signal_in_unbinned = new TFile(dir+"/Inputs/input_parametrized/ReReco_signal_M-" + Tsrmasses[mass] + "/workspace/FitContainer_workspace.root", "READ");
		TFile *f_signal_in_unbinned = new TFile(dir+"/Inputs/input/ReReco_signal_M-" + Tsrmasses[mass] + "/workspace/FitContainer_workspace.root", "READ");
		RooWorkspace *w_signalfit = (RooWorkspace*) f_signal_in_unbinned->Get("workspace");
		//RooAbsPdf *signal = w_signalfit->pdf("signal");
		RooAbsPdf *signal = w_signalfit->pdf("background");
		signal->SetName("signal");
		RooRealVar signal_norm("signal_norm", "signal_norm", normSignal);

		if (Tfunc[mass]=="dgaus") {
		  RooRealVar * mean = (RooRealVar*)w_signalfit->var("mean");
		  RooRealVar * sigmaL = (RooRealVar*)w_signalfit->var("sigmaL");
		  RooRealVar * sigmaR = (RooRealVar*)w_signalfit->var("sigmaR");
		  RooRealVar * tail_shift = (RooRealVar*)w_signalfit->var("tail_shift");
		  RooRealVar * tail_sigma = (RooRealVar*)w_signalfit->var("tail_sigma");
		  mean->setConstant(true);
		  sigmaL->setConstant(true);
		  sigmaR->setConstant(true);
		  tail_shift->setConstant(true);
		  tail_sigma->setConstant(true);
		  cout << "mean       = " << mean->getVal() << endl;
		  cout << "sigmaL     = " << sigmaL->getVal() << endl;
		  cout << "sigmaR     = " << sigmaR->getVal() << endl;
		  cout << "tail_shift = " << tail_shift->getVal() << endl;
		  cout << "tail_sigma = " << tail_sigma->getVal() << endl;
		}
		else if (Tfunc[mass]=="qgaus") {
		  RooRealVar * mean = (RooRealVar*)w_signalfit->var("mean");
		  RooRealVar * sigmaL1 = (RooRealVar*)w_signalfit->var("sigmaL1");
		  RooRealVar * sigmaL2 = (RooRealVar*)w_signalfit->var("sigmaL2");
		  RooRealVar * sigmaR1 = (RooRealVar*)w_signalfit->var("sigmaR1");
		  RooRealVar * sigmaR2 = (RooRealVar*)w_signalfit->var("sigmaR2");
		  RooRealVar * tail_shift = (RooRealVar*)w_signalfit->var("tail_shift");
		  RooRealVar * tail_sigma = (RooRealVar*)w_signalfit->var("tail_sigma"); 
		  RooRealVar * norm_g1 = (RooRealVar*)w_signalfit->var("norm_g1");
		  RooRealVar * norm_g2 = (RooRealVar*)w_signalfit->var("norm_g2");
		  mean->setConstant(true);
		  sigmaL1->setConstant(true);
		  sigmaL2->setConstant(true);
		  sigmaR1->setConstant(true);
		  sigmaR2->setConstant(true);
		  tail_shift->setConstant(true);
		  tail_sigma->setConstant(true);
		  norm_g1->setConstant(true);
		  norm_g2->setConstant(true);
		  cout << "mean       = " << mean->getVal() << endl;
		  cout << "sigmaL1    = " << sigmaL1->getVal() << endl;
		  cout << "sigmaL2    = " << sigmaL2->getVal() << endl;
		  cout << "sigmaR1    = " << sigmaR1->getVal() << endl;
		  cout << "sigmaR2    = " << sigmaR2->getVal() << endl;
		  cout << "tail_shift = " << tail_shift->getVal() << endl;
		  cout << "tail_sigma = " << tail_sigma->getVal() << endl;
		  cout << "norm_g1    = " << norm_g1->getVal() << endl;
		  cout << "norm_g2    = " << norm_g2->getVal() << endl;
		}
		else if (Tfunc[mass]=="bukin") {
		  RooRealVar * Xp = (RooRealVar*)w_signalfit->var("Xp");
		  RooRealVar * sigp = (RooRealVar*)w_signalfit->var("sigp");
		  RooRealVar * xi = (RooRealVar*)w_signalfit->var("xi");
		  RooRealVar * rho1 = (RooRealVar*)w_signalfit->var("rho1");
		  RooRealVar * rho2 = (RooRealVar*)w_signalfit->var("rho2");
		  Xp->setConstant(true);
		  sigp->setConstant(true);
		  xi->setConstant(true);
		  rho1->setConstant(true);
		  rho2->setConstant(true);
		  cout << "Xp   = " << Xp->getVal() << endl;
		  cout << "sigp = " << sigp->getVal() << endl;
		  cout << "xi   = " << xi->getVal() << endl;
		  cout << "rho1 = " << rho1->getVal() << endl;
		  cout << "rho2 = " << rho2->getVal() << endl;
		}

		RooPlot * xframe = mbb.frame();
		sigHist.plotOn(xframe,LineColor(1),MarkerColor(1));
		signal->plotOn(xframe,LineColor(2));
		TCanvas * c1 = new TCanvas("c1","c1",600,600);
		xframe->Draw();
		c1->Update();
		c1->Print("sig_SR2_"+Tsrmasses[mass]+".png");
		delete c1;

		/// DEFINE SIGNAL AND TRANSFER FACTOR PDF(S)
		/// TAKE CARE OF PROPER TF USAGE PER SR
		/// SRs 1/2: EXT ERF; SRs 3/4: LIN --> PERHAPS GO FOR OVERALL EXT ERF (P=54%, BETTER THAN INDIVIDUAL SRs)
		/// APPROACH APR 28: USE FULL RANGE TF AS TEST
		///

		RooRealVar alphaTF("alphaTF", "for extended logistic: upwards or downwards", 0.75, 0.0, 5);	//p0	//alpha
		RooRealVar offsetTF("offsetTF", "offset of TF in y direction", 400, 100, 750);	//p1	//x0	// lin: 0.15,0.1,0.5	// eml 400,100,750
		RooRealVar steepnessTF("steepnessTF", "Steepness of rise in TF", 0.0085, 0.0001, 0.1);	//p2	//k
		RooRealVar slopelinTF("slopelinTF", "Slope of linear part of TF", 3.5e-4, -5e-5, 8e-4);	//p3	//lin: -1.55e-5,-4e-5,2e-5	// eml 2.58e-4,-2e-5,4e-4
		RooArgList varsTF(mbb, alphaTF, offsetTF, steepnessTF, slopelinTF);
		RooGenericPdf TF("TF", "TF", "(1+alphaTF*TMath::Exp(-steepnessTF*(mbb-offsetTF)))/(1+TMath::Exp(-steepnessTF*(mbb-offsetTF)))*(1-slopelinTF*mbb)", varsTF);
		//RooGenericPdf TF("TF","TF","offsetTF-mbb*slopelinTF",varsTF);
		RooRealVar signalregion_norm("signalregion_norm", "Signal normalization", normSR, 0.9 *normSR, 1.1 *normSR);

		//Output file
		TFile *fOut = new TFile("input_parametrized/ReReco_signal_M-" + Tsrmasses[mass] + "/workspace/SR2/signal_workspace.root", "RECREATE");
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
		cout << "File created: signal_workspace.root" << endl;
		fOut->Close();
	}
	return 0;
}
