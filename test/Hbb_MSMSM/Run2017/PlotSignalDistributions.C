#include "TH1.h"
#include "HbbStylesNew.cc"
#include "CMS_lumi.C"

void PlotSignalDistributions(TString m1 = "350", TString m2 = "600", TString m3 = "1200", float xMax = 1500)
{

    gROOT->SetBatch();

	HbbStylesNew style;
	style.SetStyle();

	gStyle->SetOptStat(0);

    //// Input files	////
	TFile *file = new TFile("AllSignals.root", "READ");

	//// Mass	////
	TH1F *hist_m_m1 = (TH1F*) file->Get("m12_" + m1 + "GeV_20GeVbinning");
	TH1F *hist_m_m2 = (TH1F*) file->Get("m12_" + m2 + "GeV_20GeVbinning");
	TH1F *hist_m_m3 = (TH1F*) file->Get("m12_" + m3 + "GeV_20GeVbinning");
	
	//// Checking bin width	////
	float Hist_xMin = 0;
	float Hist_xMax = 3000;
	float binWidth = (Hist_xMax - Hist_xMin) / hist_m_m3->GetNbinsX();
	cout << "Number of bins: " << hist_m_m3->GetNbinsX() << endl;
	cout << "Bin width: " << binWidth << " GeV" << endl;

	TCanvas *can = style.MakeCanvas("can", "signal masses, after cuts, SR", 700, 700);
	can->SetLeftMargin(0.17);
	
	float yMax;
	if (xMax==1000){yMax = 1.2 * hist_m_m3->GetMaximum();}
	else  {yMax = 1.2 * hist_m_m1->GetMaximum();}

	style.InitHist(hist_m_m1, "m_{12}[GeV]", "Entries / 20 GeV", kBlue, 0);
	hist_m_m1->GetYaxis()->SetRangeUser(0.1, yMax);
	hist_m_m1->GetXaxis()->SetRangeUser(0, xMax);
	can->SetLogy(0);
	hist_m_m1->GetXaxis()->SetNdivisions(505);
	hist_m_m1->GetYaxis()->SetTitleOffset(1.5);
	hist_m_m1->Draw("HIST");
	style.InitHist(hist_m_m2, "m_{12}[GeV]", "Entries / 20 GeV", kGreen, 0);
	hist_m_m2->Draw("HIST SAME");
	style.InitHist(hist_m_m3, "m_{12}[GeV]", "Entries / 20 GeV", kRed, 0);
	hist_m_m3->Draw("HIST SAME");

	TLegend *leg = new TLegend(0.65, 0.60, 0.9, 0.75);
	style.SetLegendStyle(leg);
	leg->AddEntry(hist_m_m1, "m_{A/H} = " + m1 + " GeV", "L");
	leg->AddEntry(hist_m_m2, "m_{A/H} = " + m2 + " GeV", "L");
	leg->AddEntry(hist_m_m3, "m_{A/H} = " + m3 + " GeV", "L");
	leg->Draw("SAME");
	writeExtraText = true;
	extraText = "Work in progress";
	CMS_lumi(can, 13, 33);

	can->Update();
	can->SaveAs("Figs/Signal_Shapes/signal_shapes_" + m1 + "_" + m2 + "_" + m3 + ".pdf");
	can->SaveAs("Figs/Signal_Shapes/signal_shapes_" + m1 + "_" + m2 + "_" + m3 + ".png");
	can->SaveAs("Figs/Signal_Shapes/signal_shapes_" + m1 + "_" + m2 + "_" + m3 + ".root");
	
	delete can;
}


void PlotAll()
{

	gROOT->SetBatch();

	//// Mass points	////
	int nSamples = 13;

	TString points[13] = { "300", "350", "400", "450", "500", "600", "700", "800", "900", "1000", "1200", "1400", "1600" };

	PlotSignalDistributions(points[0], points[1], points[2], 1000);
	PlotSignalDistributions(points[3], points[4], points[5], 1200);
	PlotSignalDistributions(points[6], points[7], points[8], 1500);
	PlotSignalDistributions(points[9], points[10], points[11], 2500);
	PlotSignalDistributions(points[10], points[11], points[12], 2500);
	PlotSignalDistributions(points[1], points[5], points[10], 1700);
}
