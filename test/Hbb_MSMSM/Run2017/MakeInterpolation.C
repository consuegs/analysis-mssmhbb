#include "th1fmorph.cc"
#include "CMS_lumi.C"

void MakeInterpolation(int ma = 425,	// value to interpolate
	int maLow = 400,	// lower value
	int maHigh = 450,	// higher value
	int xMax = 700,
	TString fileString = "_JERup")
{

	// Silence INFO messages
	gROOT->SetBatch();
	gStyle->SetOptStat(0);

	bool logY = false;
	bool drawLeg = true;

	string mass = to_string(ma);
	string massLow = to_string(maLow);
	string massHigh = to_string(maHigh);

	TString Mass(mass);
	TString MassLow(massLow);
	TString MassHigh(massHigh);

	//// Input files	////
	TFile *file = new TFile("AllSignals/AllSignals" + fileString + ".root");

	TString SRLow, SRHigh, SR;

	if (maLow < 400)
	{
		SRLow = "_SR1_1";
	}
	else if (maLow < 700)
	{
		SRLow = "_SR2_1";
	}
	else if (maLow < 1000)
	{
		SRLow = "_SR3_5";
	}
	else(SRLow = "_SR4_10");

	if (maHigh < 400)
	{
		SRHigh = "_SR1_1";
	}
	else if (maHigh < 700)
	{
		SRHigh = "_SR2_1";
	}
	else if (maHigh < 1000)
	{
		SRHigh = "_SR3_5";
	}
	else(SRHigh = "_SR4_10");

	TH1F *histLow = (TH1F*) file->Get("m12_" + MassLow + "GeV" + SRLow + "GeVbinning");
	TH1F *histHigh = (TH1F*) file->Get("m12_" + MassHigh + "GeV" + SRHigh + "GeVbinning");
	
    TH1F *histLow_20GeVbinning = (TH1F*) file->Get("m12_" + MassLow + "GeV_20GeVbinning");
	TH1F *histHigh_20GeVbinning = (TH1F*) file->Get("m12_" + MassHigh + "GeV_20GeVbinning");

	std::cout << histLow << ":" << histHigh << ":" << std::endl;

	// To interpolate number of final events
	Int_t nSamples = 13;
	Float_t mpoints[13] = { 300, 350, 400, 450, 500, 600, 700, 800, 900, 1000, 1200, 1400, 1600 };
	TString points[13] = { "300", "350", "400", "450", "500", "600", "700", "800", "900", "1000", "1200", "1400", "1600" };

	TH1D *hist[nSamples], *hist_20GeVbinning[nSamples];
	Float_t norm[nSamples], norm_20GeVbinning[nSamples];

	for (int isample = 0; isample < nSamples; isample++)
	{

		if (mpoints[isample] < 400)
		{
			SR = "_SR1_1";
		}
		else if (mpoints[isample] < 700)
		{
			SR = "_SR2_1";
		}
		else if (mpoints[isample] < 1000)
		{
			SR = "_SR3_5";
		}
		else(SR = "_SR4_10");

		hist[isample] = (TH1D*) file->Get("m12_" + points[isample] + "GeV" + SR + "GeVbinning");
		hist_20GeVbinning[isample] = (TH1D*) file->Get("m12_" + points[isample] + "GeV_20GeVbinning");
		norm[isample] = hist[isample]->GetSumOfWeights();
		norm_20GeVbinning[isample] = hist_20GeVbinning[isample]->GetSumOfWeights();
		cout << "Number of events SR (normalized to 1pb, constrained to the respective fit range) m_{12} = " << mpoints[isample] << ": " << norm[isample] << endl;
		cout << "Number of events SR (normalized to 1pb) m_{12} = " << mpoints[isample] << ": " << norm_20GeVbinning[isample] << endl;
	}

	gROOT->Reset();
	
	TFile *f = new TFile("AllSignals_interpolated.root", "UPDATE");

	TCanvas *canv1 = new TCanvas("canv1", "canv1", 900, 900);
	canv1->SetMargin(0.12, 0.05, 0.1, 0.07);
	canv1->GetFrame()->SetFillColor(21);

	// Create a 2-d histogram to define the range
	TH2F *hr = new TH2F("", "", 1, 0, 1600, 1, 160, 500);
	hr->SetXTitle("m_{12}[GeV]");
	hr->SetYTitle("Number of events");
	hr->Draw();
	TGraph *gr1 = new TGraph(nSamples, mpoints, norm);
	gr1->SetMarkerColor(kBlue);
	gr1->SetMarkerStyle(21);
	gr1->Draw("LP");

	// Use a cubic spline to smooth the graphs
	TSpline3 *s1 = new TSpline3("grs", gr1);
	s1->SetLineColor(kRed);
	s1->Draw("same");

	writeExtraText = true;
	extraText = "Work in progress";
	CMS_lumi(canv1, 13, 33);

	canv1->SaveAs("Figs/Interpolation/NEvents_SR.png");
	canv1->SaveAs("Figs/Interpolation/NEvents_SR.pdf");

	cout << "Number of events SR (normalized to 1pb, constrained to the respective fit range) m_{12} = " << ma << " (interpolated): " << s1->Eval(ma) << endl;
	
	TH2F *hr2 = new TH2F("", "", 1, 0, 1600, 1, 160, 500);
	TGraph *gr2 = new TGraph(nSamples, mpoints, norm_20GeVbinning);
    TSpline3 *s2 = new TSpline3("grs2", gr2);
    
    delete hr2;
    
    delete canv1;

	if (fileString == "")
	{
		TH1D *m12_norm = new TH1D("m12_" + Mass +"GeV_norm", "", 1, 0., 2.);
		int nBins1 = 2;
		for (int iB = 1; iB <= nBins1; ++iB)
		{
			double x = 1;
			m12_norm->SetBinContent(iB, s1->Eval(ma));
		}
	}

	//// Signal morphing	///
	TH1F *histI = th1fmorph("", "", histLow, histHigh, maLow, maHigh, ma, s1->Eval(ma), 0);

	if (ma < 400)
	{
		histI->SetName("m12_" + Mass + "GeV_SR1_1GeVbinning" + fileString);
	}
	else if (ma < 700)
	{
		histI->SetName("m12_" + Mass + "GeV_SR2_1GeVbinning" + fileString);
	}
	else if (ma < 1000)
	{
		histI->SetName("m12_" + Mass + "GeV_SR3_5GeVbinning" + fileString);
	}
	else
	{
		histI->SetName("m12_" + Mass + "GeV_SR4_10GeVbinning" + fileString);
	}

	histI->GetXaxis()->SetRangeUser(0, xMax);
	
    TH1F *histI_20GeVbinning = th1fmorph("", "", histLow_20GeVbinning, histHigh_20GeVbinning, maLow, maHigh, ma, s2->Eval(ma), 0);
    histI_20GeVbinning->GetXaxis()->SetRangeUser(0, xMax);
    histI_20GeVbinning->SetName("m12_" + Mass + "GeV_20GeVbinning");
    
    TH1F *histI_style = (TH1F*) histI_20GeVbinning->Clone();

	TCanvas *canv2 = new TCanvas("canv2", "canv2", 900, 900);
	canv2->SetMargin(0.12, 0.05, 0.1, 0.07);
	histI_style->SetLineColor(kCyan);
	histLow->SetLineColor(kBlue);
	histLow->SetLineWidth(2);
	histHigh->SetLineColor(kRed);
	histHigh->SetLineWidth(2);
	histI_style->SetFillColor(kCyan);
	histI_style->SetFillStyle(1001);
	histI_style->GetXaxis()->SetLabelSize(0.035);
	histI_style->GetYaxis()->SetLabelSize(0.035);
	histI_style->GetXaxis()->SetTitle("m_{12}[GeV]");
	histI_style->GetYaxis()->SetTitleOffset(1.6);
	histI_style->GetXaxis()->SetTitleOffset(1.2);
	histI_style->GetYaxis()->SetTitle("Events");
	histI_style->GetXaxis()->SetRangeUser(200, xMax);
	double yMax = histI_style->GetMaximum();

	if (logY) histI_style->GetYaxis()->SetRangeUser(0.001, 1);
	else histI_style->GetYaxis()->SetRangeUser(0.0, 1.25 *yMax);

	histI_style->Draw();
	histHigh->Draw("sameh");
	histLow->Draw("sameh");

	TLegend *leg = new TLegend(0.69, 0.54, 0.85, 0.74);
	leg->SetFillStyle(0);
	leg->SetFillColor(0);
	leg->SetBorderSize(0);
	leg->SetHeader("m_{12} = " + Mass + " GeV");
	leg->SetTextSize(0.03);
	leg->AddEntry(histI_style, "Interpolated", "f");
	leg->AddEntry(histLow, "m_{12} = " + MassLow + " GeV", "lp");
	leg->AddEntry(histHigh, "m_{12} = " + MassHigh + " GeV", "lp");
	if (drawLeg) leg->Draw();
	if (logY) canv2->SetLogy(true);

	writeExtraText = true;
	extraText = "Work in progress";
	CMS_lumi(canv2, 13, 33);

	canv2->RedrawAxis();
	canv2->Update();

	canv2->Print("Figs/Interpolation/Interpolation_mass" + Mass + fileString + ".png");
	canv2->Print("Figs/Interpolation/Interpolation_mass" + Mass + fileString + ".pdf");
	delete canv2;
	
	if (fileString != "") {delete histI_20GeVbinning;}
	delete histI_style;
    
    f->Write();
    

	f->Close();
}

void PlotAll()
{

	gROOT->SetBatch();

	int nSamples = 12;
	int nUncertainties = 5;

	//// Mass points	////
	int mpoints[13] = { 300, 350, 400, 450, 500, 600, 700, 800, 900, 1000, 1200, 1400, 1600 };

	//// Interpolated mass points	////
	int mpointsInt[12] = { 325, 375, 425, 475, 550, 650, 750, 850, 950, 1100, 1300, 1500 };

	//// Maximum vale for x coordinate m12 plot 	////
	int xMax[12] = { 650, 650, 700, 800, 900, 1100, 1300, 1400, 1600, 1800, 2200, 2500 };

	//// Uncertainty strings 	////
	TString fileString[5] = { "", "_JERup", "_JERdown", "_JESup", "_JESdown" };

	for (int iuncertainty = 0; iuncertainty < nUncertainties; iuncertainty++)	// Loop over uncertainties
	{

		for (int isample = 0; isample < nSamples; isample++)	// Loop over masses
		{
			MakeInterpolation(mpointsInt[isample], mpoints[isample], mpoints[isample + 1], xMax[isample], fileString[iuncertainty]);
		}	// End loop over masses

	}	// End loop over uncertainties
}
