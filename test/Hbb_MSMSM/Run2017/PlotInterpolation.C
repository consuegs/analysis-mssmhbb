#include "th1fmorph.cc"
#include "CMS_lumi.C"

void PlotInterpolation(int ma = 325,	// value to interpolate
	int maLow = 300,	// lower value
	int maHigh = 350,
	int xMax = 600,	// canv1 value)
	TString fileString = "")
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
	
	TH1F *histLow = (TH1F*) file->Get("m12_" + MassLow + "GeV_20GeVbinning");
	TH1F *histHigh = (TH1F*) file->Get("m12_" + MassHigh + "GeV_20GeVbinning");

	//// Histogram normalization	///
	double normLow = 1.0 / histLow->GetSumOfWeights();
	double normHigh = 1.0 / histHigh->GetSumOfWeights();
	int nBins = histLow->GetNbinsX();
	for (int iB = 1; iB <= nBins; ++iB)
	{
		double x1 = normLow *histLow->GetBinContent(iB);
		double ex1 = normLow *histLow->GetBinError(iB);
		histLow->SetBinContent(iB, x1);
		histLow->SetBinError(iB, ex1);

		double x2 = normHigh *histHigh->GetBinContent(iB);
		double ex2 = normHigh *histHigh->GetBinError(iB);
		histHigh->SetBinContent(iB, x2);
		histHigh->SetBinError(iB, ex2);
	}

	//// Signal morphing	///
	TH1F *histI = th1fmorph("", "", histLow, histHigh, maLow, maHigh, ma, double(1.0), 0);

	for (int iB = 1; iB <= nBins; ++iB)
	{
		double xI = histI->GetBinContent(iB);
		double eI = histI->GetBinError(iB);
		histI->SetBinError(iB, 0);
	}

	histI->GetXaxis()->SetTitle("m_{12}[GeV]");
	histI->GetYaxis()->SetTitle("Normalized to unity");
	histI->GetYaxis()->SetTitleOffset(1.6);
	histI->GetYaxis()->SetTitleSize(0.03);
	histI->SetMarkerSize(0.8);
	histI->GetYaxis()->SetLabelSize(0.03);
	histI->GetXaxis()->SetRangeUser(200, xMax);

	double yMax = histLow->GetMaximum();

	if (logY) histI->GetYaxis()->SetRangeUser(0.001, 1);
	else histI->GetYaxis()->SetRangeUser(0.0, 1.1 *yMax);

	histI->SetLineColor(kCyan);
	histI->SetFillColor(kCyan);
	histI->SetFillStyle(1001);
	histLow->SetLineWidth(2);
	histHigh->SetLineWidth(2);

	TCanvas *canv1 = new TCanvas("canv1", "canv1", 900, 900);
    canv1->SetMargin(0.12, 0.05, 0.1, 0.07);
	canv1->GetFrame()->SetFillColor(21);

    histI->Draw("");
	histLow->Draw("histsame");
	histHigh->Draw("histsame");

	TLegend *leg = new TLegend(0.64, 0.49, 0.90, 0.69);
	leg->SetFillStyle(0);
	leg->SetFillColor(0);
	leg->SetBorderSize(0);
	leg->SetHeader("m_{12} = " + Mass + " GeV");
	leg->SetTextSize(0.03);
	leg->AddEntry(histI, "Interpolated", "f");
	histLow->SetLineColor(4);
	leg->AddEntry(histLow, "m_{12} = " + MassLow + " GeV", "l");
	histLow->SetLineColor(2);
	leg->AddEntry(histHigh, "m_{12} = " + MassHigh + " GeV", "l");
	if (drawLeg) leg->Draw();
	if (logY) canv1->SetLogy(true);

	writeExtraText = true;
	extraText = "Work in progress";
	CMS_lumi(canv1, 13, 33);

	canv1->Print("Figs/Interpolation/Interpolation_mass" + Mass + fileString + "_interpolated_2.png");
	canv1->Print("Figs/Interpolation/Interpolation_mass" + Mass + fileString + "_interpolated_2.pdf");
	delete canv1;

}

void PlotAll()
{

	gROOT->SetBatch();

	int nSamples = 3;
	int nUncertainties = 5;

	//// Interpolated mass points	////
	int mpointsInt[3] = { 325, 375, 425 };
	int mpoints[4] = { 300, 350, 400, 450};

	//// Maximum vale for x coordinate m12 plot 	////
	int xMax[3] = { 700, 700, 800 };
	
	//// Uncertainty strings 	////
	TString fileString[5] = { "", "_JERup", "_JERdown", "_JESup", "_JESdown" };
    
    for (int iuncertainty = 0; iuncertainty < nUncertainties; iuncertainty++)	// Loop over uncertainties
	{

	    for (int isample = 0; isample < nSamples; isample++)	// Loop over masses
	        {   
		    PlotInterpolation(mpointsInt[isample], mpoints[isample], mpoints[isample + 1], xMax[isample], fileString[iuncertainty]);
	        }	// End loop over masses
	
	}	// End loop over uncertainties
}
