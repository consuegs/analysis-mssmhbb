#include "TH1D.h"
#include "TMath.h"
#include "TRandom.h"
using namespace RooFit;
using namespace std;

void RebinAndNormSignalTemplates(int ma = 300, double lumisf = 142.9, TString histname = "m12_aac_JER_up")
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

	TFile *fileIn = new TFile("mc-sig-" + Mass + "-NLO-deep-SR-3j.root");
	TH1D *hist = (TH1D*) fileIn->Get(histname);

	if (histname == "m12_aac_1GeV")
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
	else (hist->SetName(histname));

	double nBins = hist->GetNbinsX();
	int xMin = hist->GetXaxis()->GetXmin();
	int xMax = hist->GetXaxis()->GetXmax();
	double binWidth = (xMax - xMin) / nBins;
	cout << "m_{12}: " << ma << endl;
	cout << "Bin width: " << binWidth << endl;

	TFile f("SignalRootFiles_v1/mc-sig-" + Mass + "-NLO-deep-SR-3j.root", "UPDATE");
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
	int nUncertainties = 28;
	TString histname[28] = { "nentries", "m12_aac", "m12_aac_1GeV", "m12_aac_JER_up", "m12_aac_JER_down", "m12_aac_JES_up", "m12_aac_JES_down", "m12_aac_PU_up", "m12_aac_PU_down", "m12_aac_SFbtag_up", "m12_aac_SFbtag_down", "m12_aac_jet_trigeff_up", "m12_aac_jet_trigeff_down", "m12_aac_onlSFbtag_up", "m12_aac_onlSFbtag_down", "m12_SR1_1GeV", "m12_SR1_2GeV", "m12_SR1_5GeV", "m12_SR1_10GeV", "m12_SR2_1GeV", "m12_SR2_3GeV", "m12_SR2_5GeV", "m12_SR2_15GeV", "m12_SR3_5GeV", "m12_SR3_20GeV", "m12_SR4_5GeV", "m12_SR4_10GeV", "m12_SR4_25GeV"};

	for (int isample = 0; isample < nSamples; isample++)	// Loop over masses
	{
		for (int iuncertainty = 0; iuncertainty < nUncertainties; iuncertainty++)	// Loop over uncertainties
		{
			RebinAndNormSignalTemplates(mpoints[isample], lumisf[isample], histname[iuncertainty]);
		}	// End loop over histograms
	}	// End loop over masses

}
