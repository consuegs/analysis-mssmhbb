#include "TH1D.h"
#include "TMath.h"
#include "TRandom.h"
using namespace RooFit;

void RebinAndNormSignalTemplates(int ma = 300, double lumisf = 142.9, TString fileString = "_JERup")
{

	gROOT->SetBatch();
	// Silence INFO messages
	RooMsgService::instance().setGlobalKillBelow(RooFit::FATAL);
	// Silence additional MINUIT output 
	RooMsgService::instance().setSilentMode(true);
	// Silence Info in TCanvas::Print: messages
	gErrorIgnoreLevel = kWarning;

	string mass = to_string(ma);
	TString Mass(mass);

	double sf = 1 / lumisf;

	TFile *fileIn = new TFile("mc-sig-" + mass + "-NLO-deep-SR-3j.root");
	TH1D *hist = (TH1D*) fileIn->Get("m12_aac" + fileString);

	if (fileString == "_1GeV")
	{
		hist->SetName("m12_aac_binForFit");
		if (ma < 600)
		{
			hist->Rebin(10);
		}
		else if (ma < 1000)
		{
			hist->Rebin(20);
		}
		else
		{
			hist->Rebin(25);
		}
	hist->Scale(sf);		
	}
	else (hist->SetName("m12_aac" + fileString));

	double nBins = hist->GetNbinsX();
	int xMin = hist->GetXaxis()->GetXmin();
	int xMax = hist->GetXaxis()->GetXmax();
	double binWidth = (xMax - xMin) / nBins;
	cout << "m_{12}: " << ma << endl;
	cout << "Bin width: " << binWidth << endl;

	TFile f("SignalRootFiles_v1/mc-sig-" + mass + "-NLO-deep-SR-3j.root", "UPDATE");
	hist->Write();
	f.Close();
}

void SaveAll()
{

	gROOT->SetBatch();

	int nSamples = 13;

	//// Mass points	////
	int mpoints[13] = { 300, 350, 400, 450, 500, 600, 700, 800, 900, 1000, 1200, 1400, 1600 };
	double lumisf[13] = { 142.9, 69.29, 75.24, 75.45, 64.51, 77.85, 70.42, 72.21, 75.66, 74.27, 71.75, 73.48, 75.7 };

	//// Uncertainty strings 	////
	int nUncertainties = 14;
	TString fileString[14] = { "", "_1GeV", "_JER_up", "_JER_down", "_JES_up", "_JES_down", "_PU_up", "_PU_down", "_SFbtag_up", "_SFbtag_down", "_jet_trigeff_up", "_jet_trigeff_down", "_onlSFbtag_up", "_onlSFbtag_down" };

	for (int isample = 0; isample < nSamples; isample++)	// Loop over masses
	{
		for (int iuncertainty = 0; iuncertainty < nUncertainties; iuncertainty++)	// Loop over uncertainties
		{
			RebinAndNormSignalTemplates(mpoints[isample], lumisf[isample], fileString[iuncertainty]);
		}	// End loop over histograms
	}	// End loop over masses

}
