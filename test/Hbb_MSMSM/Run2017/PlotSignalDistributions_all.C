#include "TH1.h"
#include "HbbStylesNew.cc"
#include "CMS_lumi.C"

void PlotSignalDistributions_all()
{

    gROOT->SetBatch();

	HbbStylesNew style;
	style.SetStyle();

	gStyle->SetOptStat(0);
	
	Int_t nSamples = 13;
	TString points[13] = { "300", "350", "400", "450", "500", "600", "700", "800", "900", "1000", "1200", "1400", "1600" };
	
	//// Input files	////
	TFile *file = new TFile("AllSignals/AllSignals.root", "READ");
	
	TH1F *hist[nSamples];
	
	for (int isample = 0; isample < nSamples; isample++)
	{
		hist[isample] = (TH1F*) file->Get("m12_" + points[isample] + "GeV_20GeVbinning");
	}

	TCanvas *can = style.MakeCanvas("can", "signal masses, after cuts, SR", 700, 700);
	can->SetLeftMargin(0.17);

	style.InitHist(hist[0], "m_{12}[GeV]", "Entries / 20 GeV", kBlue, 0);
	hist[0]->GetYaxis()->SetRangeUser(0.1, 1.4 * hist[1]->GetMaximum());
	hist[0]->GetXaxis()->SetRangeUser(0, 2500);
	can->SetLogy(0);
	hist[0]->GetXaxis()->SetNdivisions(505);
	hist[0]->GetYaxis()->SetTitleOffset(1.5);
	hist[0]->Draw("HIST");
	style.InitHist(hist[1], "m_{12}[GeV]", "Entries / 20 GeV", kGreen, 0);
	hist[1]->Draw("HIST SAME");
	style.InitHist(hist[2], "m_{12}[GeV]", "Entries / 20 GeV", kRed, 0);
	hist[2]->Draw("HIST SAME");
	style.InitHist(hist[3], "m_{12}[GeV]", "Entries / 20 GeV", 5, 0);
	hist[3]->Draw("HIST SAME");
	style.InitHist(hist[4], "m_{12}[GeV]", "Entries / 20 GeV", 6, 0);
	hist[4]->Draw("HIST SAME");
	style.InitHist(hist[5], "m_{12}[GeV]", "Entries / 20 GeV", 7, 0);
	hist[5]->Draw("HIST SAME");
	style.InitHist(hist[6], "m_{12}[GeV]", "Entries / 20 GeV", kGreen+4, 0);
	hist[6]->Draw("HIST SAME");
	style.InitHist(hist[7], "m_{12}[GeV]", "Entries / 20 GeV", 9, 0);
	hist[7]->Draw("HIST SAME");
	style.InitHist(hist[8], "m_{12}[GeV]", "Entries / 20 GeV", kPink, 0);
	hist[8]->Draw("HIST SAME");
	style.InitHist(hist[9], "m_{12}[GeV]", "Entries / 20 GeV", kOrange+7, 0);
	hist[9]->Draw("HIST SAME");
	style.InitHist(hist[10], "m_{12}[GeV]", "Entries / 20 GeV", kMagenta+4, 0);
	hist[10]->Draw("HIST SAME");
	style.InitHist(hist[11], "m_{12}[GeV]", "Entries / 20 GeV", kCyan+4, 0);
	hist[11]->Draw("HIST SAME");
	style.InitHist(hist[12], "m_{12}[GeV]", "Entries / 20 GeV", kGray+3, 0);
	hist[12]->Draw("HIST SAME");

	TLegend *leg = new TLegend(0.55, 0.30, 0.95, 0.75);
	style.SetLegendStyle(leg);	
	for (int isample = 0; isample < nSamples; isample++)
	{
		leg->AddEntry(hist[isample], "m_{A/H} = " + points[isample] + " GeV", "L");
	}
	
	leg->Draw("SAME");
	writeExtraText = true;
	extraText = "Work in progress";
	CMS_lumi(can, 13, 33);

	can->Update();
	can->SaveAs("Figs/Signal_Shapes/signal_shapes_all.pdf");
	can->SaveAs("Figs/Signal_Shapes/signal_shapes_all.png");
	can->SaveAs("Figs/Signal_Shapes/signal_shapes_all.root");
	
	delete can;
}
