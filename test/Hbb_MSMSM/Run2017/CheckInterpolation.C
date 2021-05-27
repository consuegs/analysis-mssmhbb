#include "th1fmorph.cc"
#include "CMS_lumi.C"

void CheckInterpolation(int ma = 350,	// value to interpolate
	int maLow = 400,	// lower value
	int maHigh = 450,
	int xMax = 600)	// upper value)
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
    TFile *file = new TFile("AllSignals.root");
	
	TH1F *histLow = (TH1F*) file->Get("m12_" + MassLow + "GeV_20GeVbinning");
	TH1F *histHigh = (TH1F*) file->Get("m12_" + MassHigh + "GeV_20GeVbinning");
	TH1F *hist = (TH1F*) file->Get("m12_" + Mass + "GeV_20GeVbinning");

	hist->SetTitle("");

	//// Histogram normalization	///
	double norm = 1.0 / hist->GetSumOfWeights();
	double normLow = 1.0 / histLow->GetSumOfWeights();
	double normHigh = 1.0 / histHigh->GetSumOfWeights();
	int nBins = hist->GetNbinsX();
	for (int iB = 1; iB <= nBins; ++iB)
	{
		double x = norm *hist->GetBinContent(iB);
		double ex = norm *hist->GetBinError(iB);
		hist->SetBinContent(iB, x);
		hist->SetBinError(iB, ex);

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

	hist->GetXaxis()->SetTitle("m_{12}[GeV]");
	hist->GetYaxis()->SetTitle("Normalized to unity");
	hist->GetYaxis()->SetTitleOffset(1.3);
	hist->GetYaxis()->SetTitleSize(0.06);
	hist->SetMarkerSize(1.2);
	hist->GetXaxis()->SetLabelSize(0);
	hist->GetYaxis()->SetLabelSize(0.06);
	hist->GetXaxis()->SetRangeUser(200, xMax);

	double yMax = hist->GetMaximum();

	float x_leg_min, factor;
	if (ma < 600)
	{
		x_leg_min = 0.64;
		factor = 1.1;
	}
	else
	{
		x_leg_min = 0.72;
		factor = 1.4;
	}

	if (logY) hist->GetYaxis()->SetRangeUser(0.001, 1);
	else hist->GetYaxis()->SetRangeUser(0.0, factor *yMax);

	hist->SetLineColor(kBlack);
	histI->SetLineColor(kCyan);
	histI->SetFillColor(kCyan);
	histI->SetFillStyle(1001);

	TCanvas *canv1 = new TCanvas("canv1", "canv1", 900, 900);
	TPad *upper = new TPad("upper", "pad", 0, 0.31, 1, 1);
	upper->Draw();
	upper->cd();
	upper->SetFillColor(0);
	upper->SetBorderMode(0);
	upper->SetBorderSize(10);
	upper->SetTickx(1);
	upper->SetTicky(1);
	upper->SetLeftMargin(0.17);
	upper->SetRightMargin(0.05);
	upper->SetBottomMargin(0.02);
	upper->SetFrameFillStyle(0);
	upper->SetFrameLineStyle(0);
	upper->SetFrameLineWidth(2);
	upper->SetFrameBorderMode(0);
	upper->SetFrameBorderSize(10);

	hist->Draw("e1");
	histI->Draw("same");
	hist->Draw("e1same");

	TLegend *leg = new TLegend(x_leg_min, 0.49, 0.90, 0.69);
	leg->SetFillStyle(0);
	leg->SetFillColor(0);
	leg->SetBorderSize(0);
	leg->SetHeader("m_{12} = " + Mass + " GeV");
	leg->SetTextSize(0.044);
	leg->AddEntry(hist, "Actual", "lpe");
	leg->AddEntry(histI, "Interpolated", "f");
	if (drawLeg) leg->Draw();
	if (logY) upper->SetLogy(true);

	writeExtraText = true;
	extraText = "Work in progress";
	CMS_lumi(upper, 13, 33);

	canv1->cd();

	TH1D *ratioH = (TH1D*) hist->Clone("ratioH");
	ratioH->SetStats(0);
	ratioH->GetXaxis()->SetLabelFont(42);
	ratioH->GetXaxis()->SetLabelOffset(0.03);
	ratioH->GetXaxis()->SetLabelSize(0.12);
	ratioH->GetXaxis()->SetTitleSize(0.13);
	ratioH->GetXaxis()->SetTitleOffset(1.35);
	ratioH->GetXaxis()->SetTickLength(0.025);
	ratioH->GetXaxis()->SetTickSize(0.08);
	ratioH->GetYaxis()->SetRangeUser(0., 1.99);
	ratioH->GetYaxis()->SetLabelOffset(0.008);
	ratioH->GetYaxis()->SetLabelSize(0.08);
	ratioH->GetYaxis()->SetTitleSize(0.11);
	ratioH->GetYaxis()->SetNdivisions(6);
	ratioH->GetYaxis()->SetTitleOffset(0.45);
	ratioH->GetYaxis()->SetTitle("Ratio    ");
	ratioH->GetYaxis()->SetTickLength(0.025);
	ratioH->GetYaxis()->SetTickSize(0.02);
	ratioH->SetLineColor(kBlack);
	ratioH->SetLineWidth(1);
	ratioH->SetLineStyle(1);
	ratioH->SetMarkerStyle(kFullCircle);
	ratioH->SetMarkerColor(kBlack);
	ratioH->SetMarkerSize(1);

	for (int iB = 1; iB <= nBins; ++iB)
	{
		float x1 = hist->GetBinContent(iB);
		float x2 = histI->GetBinContent(iB);
		if (x1 > 0 && x2 > 0)
		{
			float e1 = hist->GetBinError(iB);
			float ratio = x1 / x2;
			float eratio = e1 / x2;
			ratioH->SetBinContent(iB, ratio);
			ratioH->SetBinError(iB, eratio);
		}
		else
		{
			ratioH->SetBinContent(iB, 1000);
		}
	}

	// ------------>Primitives in pad: lower
	TPad *lower = new TPad("lower", "pad", 0, 0, 1, 0.30);
	lower->Draw();
	lower->cd();
	lower->SetFillColor(0);
	lower->SetBorderMode(0);
	lower->SetBorderSize(10);
	lower->SetGridy();
	lower->SetTickx(1);
	lower->SetTicky(1);
	lower->SetLeftMargin(0.17);
	lower->SetRightMargin(0.05);
	lower->SetTopMargin(0.026);
	lower->SetBottomMargin(0.35);
	lower->SetFrameFillStyle(0);
	lower->SetFrameLineStyle(0);
	lower->SetFrameLineWidth(2);
	lower->SetFrameBorderMode(0);
	lower->SetFrameBorderSize(10);
	lower->SetFrameFillStyle(0);
	lower->SetFrameLineStyle(0);
	lower->SetFrameLineWidth(2);
	lower->SetFrameBorderMode(0);
	lower->SetFrameBorderSize(10);

	ratioH->Draw("e1");

	lower->Modified();
	lower->RedrawAxis();
	canv1->cd();
	canv1->SetSelected(canv1);

	canv1->Print("Figs/Interpolation/Interpolation_mass" + Mass + "_interpolated.png");
	canv1->Print("Figs/Interpolation/Interpolation_mass" + Mass + "_interpolated.pdf");
	delete canv1;

}

void PlotAll()
{

	gROOT->SetBatch();

	int nSamples = 13;

	//// Mass points	////
	int mpoints[13] = { 300, 350, 400, 450, 500, 600, 700, 800, 900, 1000, 1200, 1400, 1600 };

	//// Maximum vale for x coordinate m12 plot 	////
	int xMax[11] = { 600, 700, 800, 800, 900, 1000, 1100, 1300, 1400, 1700, 2000 };

	for (int isample = 1; isample < nSamples - 1; isample++)	// Loop over masses
	{
		CheckInterpolation(mpoints[isample], mpoints[isample - 1], mpoints[isample + 1], xMax[isample - 1]);
	}	// End loop over masses

	//// Extrapolation for mass point 1600	////
	CheckInterpolation(1600, 1200, 1400, 2300);
}
