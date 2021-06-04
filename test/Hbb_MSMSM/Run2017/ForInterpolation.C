#include "th1fmorph.cc"
#include "CMS_lumi.C"
using namespace RooFit;

void GetFittingPar( bool IsBinnedFit = true )
{
	
	TString folderString, outputString, pdfname; 

    if (IsBinnedFit)
		{
			folderString = "NLO-deep-SR-3j_binned";
			outputString = "_binnedFit";
			pdfname = "background";
			
		}
	else 
		{
			folderString = "NLO-deep-SR-3j";
			outputString = "_unbinnedFit";
			pdfname = "signal";
		}

	///////////////////////////////// Parameter Strings	//////////////////////////////////////////
	int nParameters = 5;
	TString Parameters[5] = { "mean", "sigmaL", "sigmaR", "tail_shift", "tail_sigma" };

	//// Mass points	////
	int nSamples = 4;
	float points[4] = { 300, 350, 400, 450};
	TString mpoints[4] = { "300", "350", "400", "450"};

	TGraphErrors *gr[nParameters];

	for (int i = 0; i < nParameters; i++)
	{
		gr[i] = new TGraphErrors(nSamples);
	}

	for (int isample = 0; isample < nSamples; isample++)	// Loop over samples
	{

		// Open input file with workspace 
		TFile *f = new TFile("results/mc-sig-" + mpoints[isample] + "-" + folderString + "/workspace/FitContainer_workspace.root");

		// Retrieve workspace from file
		RooWorkspace *w = (RooWorkspace*) f->Get("workspace");

		std::cout << Parameters[0] << ": " << w->var(Parameters[0])->getValV() << " +/- " << w->var(Parameters[0])->getError() << std::endl;
		std::cout << Parameters[1] << ": " << w->var(Parameters[1])->getValV() << " +/- " << w->var(Parameters[1])->getError() << std::endl;
		std::cout << Parameters[2] << ": " << w->var(Parameters[2])->getValV() << " +/- " << w->var(Parameters[2])->getError() << std::endl;
		std::cout << Parameters[3] << ": " << w->var(Parameters[3])->getValV() << " +/- " << w->var(Parameters[3])->getError() << std::endl;
		std::cout << Parameters[4] << ": " << w->var(Parameters[4])->getValV() << " +/- " << w->var(Parameters[4])->getError() << std::endl;

		gr[0]->SetPoint(isample, points[isample], w->var(Parameters[0])->getValV());
		gr[0]->SetPointError(isample, 0., w->var(Parameters[0])->getError());
		gr[0]->GetYaxis()->SetRangeUser(280, 520);
		gr[1]->SetPoint(isample, points[isample], w->var(Parameters[1])->getValV());
		gr[1]->SetPointError(isample, 0., w->var(Parameters[1])->getError());
		gr[1]->GetYaxis()->SetRangeUser(20, 120);
		gr[2]->SetPoint(isample, points[isample], w->var(Parameters[2])->getValV());
		gr[2]->SetPointError(isample, 0., w->var(Parameters[2])->getError());
		gr[2]->GetYaxis()->SetRangeUser(0, 80);
		gr[3]->SetPoint(isample, points[isample], w->var(Parameters[3])->getValV());
		gr[3]->SetPointError(isample, 0., w->var(Parameters[3])->getError());
		gr[3]->GetYaxis()->SetRangeUser(340, 600);
		gr[4]->SetPoint(isample, points[isample], w->var(Parameters[4])->getValV());
		gr[4]->SetPointError(isample, 0., w->var(Parameters[4])->getError());
		gr[4]->GetYaxis()->SetRangeUser(-50, 400);

	}	// End loop over samples

	//// Save TGraphErrors which will serve as input for interpolation procedure////
	TFile f("Parameters_ForInterpolation" + outputString + ".root", "RECREATE");
	TCanvas *canv = new TCanvas("canv", "canv", 900, 900);
	canv->SetMargin(0.12, 0.05, 0.1, 0.07);
	canv->GetFrame()->SetFillColor(21);

	for (int i = 0; i < nParameters; i++)
	{
		gr[i]->Write(Parameters[i]);
		gr[i]->SetTitle("");
		gr[i]->SetMarkerColor(kBlue);
		gr[i]->SetMarkerStyle(21);
		gr[i]->Draw("ALP");
		gr[i]->GetYaxis()->SetTitle("Parameter value");
		gr[i]->GetYaxis()->SetTitleOffset(1.5);
		gr[i]->GetXaxis()->SetTitle("m_{12}[GeV]");

		TLegend *leg = new TLegend(0.66, 0.72, 0.92, 0.74);
		leg->SetTextFont(42);
		leg->SetTextSize(0.04);
		leg->SetLineWidth(0);
		leg->AddEntry(gr[i], Parameters[i], "lp");
		leg->Draw();

        writeExtraText = true;
		extraText = "Work in progress";
		CMS_lumi(canv, 13, 33);

		canv->SaveAs("Figs/FittingPar/" + Parameters[i] + outputString + ".pdf");
		canv->Update();
	}
	delete canv;

}

void ForInterpolation(int ma = 325,	// value to interpolate
	int maLow = 300,	// lower value
	int maHigh = 350,	// higher value
	TString fileString = "")
{

	// Silence INFO messages
	gROOT->SetBatch();
	gStyle->SetOptStat(0);

	string mass = to_string(ma);
	string massLow = to_string(maLow);
	string massHigh = to_string(maHigh);

	TString Mass(mass);
	TString MassLow(massLow);
	TString MassHigh(massHigh);

	//// Input files	////
	TFile *fileLow = new TFile("SignalRootFiles_v1/mc-sig-" + MassLow + "-NLO-deep-SR-3j.root");
	TFile *fileHigh = new TFile("SignalRootFiles_v1/mc-sig-" + MassHigh + "-NLO-deep-SR-3j.root");

	TH1F *histLow = (TH1F*) fileLow->Get("m12_aac" + fileString);
	TH1F *histHigh = (TH1F*) fileHigh->Get("m12_aac" + fileString);

	// To interpolate number of final events
	Int_t nSamples = 13;
	Float_t mpoints[13] = { 300, 350, 400, 450, 500, 600, 700, 800, 900, 1000, 1200, 1400, 1600 };
	TString points[13] = { "300", "350", "400", "450", "500", "600", "700", "800", "900", "1000", "1200", "1400", "1600" };

	TH1D *hist[nSamples];
	Float_t norm[nSamples];

	for (int isample = 0; isample < nSamples; isample++)	// Loop over masses
	{
		//// Input files	////
		TFile *file = new TFile("SignalRootFiles_v1/mc-sig-" + points[isample] + "-NLO-deep-SR-3j.root");
		hist[isample] = (TH1D*) file->Get("m12_aac" + fileString);
		norm[isample] = hist[isample]->GetSumOfWeights();
	}	// End loop over masses

	TFile *f = new TFile("SignalRootFiles_v1/mc-sig-" + Mass + "-NLO-deep-SR-3j.root", "UPDATE");

	TGraph *gr1 = new TGraph(nSamples, mpoints, norm);
	// Use a cubic spline to smooth the graphs
	TSpline3 *s1 = new TSpline3("grs", gr1);
	//// Signal morphing	///
	TH1F *histI = th1fmorph("", "", histLow, histHigh, maLow, maHigh, ma, s1->Eval(ma), 0);
	histI->SetName("m12_aac" + fileString);
	histI->GetXaxis()->SetRangeUser(0, 3000);

	f->Write();
	f->Close();

}

void SaveAll()
{

	gROOT->SetBatch();

	int nSamplesInt = 3;
	int nUncertainties = 14;

	//// Interpolated mass points	////
	int mpointsInt[3] = { 325, 375, 425 };
	int mpoints[4] = { 300, 350, 400, 450 };

	//// Uncertainty strings 	////
	TString fileString[14] = { "", "_binForFit", "_JER_up", "_JER_down", "_JES_up", "_JES_down", "_PU_up", "_PU_down", "_SFbtag_up", "_SFbtag_down", "_jet_trigeff_up", "_jet_trigeff_down", "_onlSFbtag_up", "_onlSFbtag_down" };

    bool IsBinnedFit = true;
    
    GetFittingPar(IsBinnedFit);

	for (int iuncertainty = 0; iuncertainty < nUncertainties; iuncertainty++)	// Loop over uncertainties
	{
		for (int isample = 0; isample < nSamplesInt; isample++)	// Loop over interpolated masses
		{
			ForInterpolation(mpointsInt[isample], mpoints[isample], mpoints[isample + 1], fileString[iuncertainty]);
		}	// End loop over interpolated masses

	}	// End loop over uncertainties

}
