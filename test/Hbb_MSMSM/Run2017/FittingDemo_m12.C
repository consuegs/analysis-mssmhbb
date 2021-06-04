#include "CMS_lumi.C"
using namespace RooFit;

void FittingDemo_m12(int ma = 700)
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

	TFile *fileIn = new TFile("SignalRootFiles_v1/mc-sig-" + Mass + "-NLO-deep-SR-3j.root");
	TH1D *hist = (TH1D*) fileIn->Get("m12_aac");
	int xMin = hist->GetXaxis()->GetXmin();
	int xMax = hist->GetXaxis()->GetXmax();
	int xMinFit, xMaxFit;

	if (ma < 400)
	{
		xMinFit = 200;
		xMaxFit = 650;
	}
	else if (ma < 1000)
	{
		xMinFit = 350;
		xMaxFit = 1190;
	}
	else
	{
		xMinFit = 500;
		xMaxFit = 1700;
	}

	// Bin width
	double nBins = hist->GetNbinsX();
	double binWidth = (xMax - xMin) / nBins;
	double nBinsInterval = (xMaxFit - xMin) / binWidth;
	cout << "m_{12}: " << ma << endl;
	cout << "Bin width: " << binWidth << endl;
	cout << "Get center value of x coordinate for first bin: " << hist->GetXaxis()->GetBinCenter(0) << endl;
	cout << "xMin: " << xMin << endl;
	cout << "xMax: " << xMax << endl;
	cout << "normalization: " << hist->GetSumOfWeights() << endl;
	cout << "Number of bins: " << nBins << endl;
	cout << "Number of bins in fitting interval: " << nBinsInterval << endl;

	// Declare observable x
	RooRealVar x("x", "x", xMinFit, xMaxFit);

	// Create a binned dataset that imports contents of TH1 and associates its contents to observable 'x'
	RooDataHist dh("dh", "dh", x, Import(*hist));

	// Build Bukin p.d.f
	RooRealVar Xp("Xp", "Xp", ma, xMinFit, xMaxFit);
	RooRealVar sigp("sigp", "sigp", 100, 20, 200);
	RooRealVar xi("xi", "xi", 0.2, -10, 10);
	RooRealVar rho1("rho1", "rho1", -0.07, -10., 0.5);
	RooRealVar rho2("rho2", "rho2", -0.3, -3., 3.);
	RooAbsPdf *PDF = new RooBukinPdf("Bukin", "Bukin", x, Xp, sigp, xi, rho1, rho2);

	// Perform fit and save result
	RooFitResult *r = PDF->fitTo(dh, Save(), Verbose(kFALSE));
	TF1 *funcModel = (TF1*) PDF->asTF(RooArgList(x), RooArgList(Xp, sigp, xi, rho1, rho2));

	// Summary printing: Basic info plus final values of floating fit parameters
	r->Print();

	TFile f("Figs/SignalFits/workspace_" + Mass + ".root", "RECREATE");
	r->Write("ws_" + Mass + "GeV");
	f.Close();

	// Extract covariance and correlation matrix as TMatrixDSym
	const TMatrixDSym &cor = r->correlationMatrix();
	const TMatrixDSym &cov = r->covarianceMatrix();

	// Print correlation, covariance matrix
	cout << "correlation matrix" << endl;
	cor.Print();
	cout << "covariance matrix" << endl;
	cov.Print();

	// Drawing in Canvas    
	TCanvas *c1 = new TCanvas("c1", "c1", 900, 900);
	c1->SetLeftMargin(0.12);
	c1->SetBottomMargin(0.1);

	TPad *upper = new TPad("upper", "pad", 0, 0.31, 1, 1);
	upper->Draw();
	upper->cd();
	upper->Modified();
	upper->SetTicks();
	upper->SetLeftMargin(0.09);
	upper->SetRightMargin(0.05);
	upper->SetBottomMargin(0.02);

	// Plot binned dataset showing Poisson error bars (RooFit default) and pdf
	RooPlot *frame = x.frame(Name("MMSM H->bb analysis"), Title("   "));
	frame->SetMarkerStyle(21);
	frame->SetMarkerSize(0.8);
	frame->SetStats(0);
	frame->GetXaxis()->SetTitle("m_{12}[GeV]");
	frame->GetYaxis()->SetTitle(Form("Events / %.0f GeV", binWidth));
	frame->GetYaxis()->SetTitleOffset(1.1);
	frame->GetYaxis()->SetTitleSize(0.04);
	frame->SetMarkerSize(0.4);
	frame->GetXaxis()->SetLabelSize(0.03);
	frame->GetYaxis()->SetLabelSize(0.03);
	frame->GetXaxis()->SetRangeUser(xMinFit, xMaxFit);

	// ---------------------------------------------------------------------------------------------
	dh.plotOn(frame, DataError(RooAbsData::SumW2));
	//PDF->plotOn(frame, VisualizeError(*r, 2, kFALSE), FillColor(kRed));
	PDF->plotOn(frame, LineColor(kBlue), FillColor(kRed));

	// Compute chi-square and p-value
	double chi = frame->chiSquare(5);
	double ndof = nBinsInterval - 5;
	double p_value = TMath::Prob(chi *ndof, ndof);
	cout << "chi^2 (m_{12}=" + Mass + " GeV) / ndof = " << Form("%.2f", chi *ndof) << "/" << nBinsInterval - 5 << endl;
	cout << "p-value = " << Form("%.3f", p_value) << endl;
	cout << "//////////////////////////////////////////" << endl;

	// Construct a histogram with the residuals of the data w.r.t. the curve ('curve' - histogram)
	RooHist *hresid = frame->residHist();

	// Construct a histogram with the pulls of the data w.r.t the curve (('curve' - histogram) / err_histogram)
	RooHist *hpull = frame->pullHist();

	//// Selecting legend names for 	////	
	for (int i = 0; i < frame->numItems(); i++)
	{
		TString obj_name = frame->nameOf(i);
		if (obj_name == "") continue;
	}
	TString names[] = { "h_dh",
		"PDF_Norm[x]",
		"" };
	TString signs[] = { "Simulated Signal",
		//  "Fit Error",
		"Global Fit",
	};

	hist->SetLineWidth(3);

	//// Legend	////
	float xMinLeg, xMaxLeg;
	if (ma == 900 || ma == 1200 || ma == 1400)
	{
		xMinLeg = 0.13;
		xMaxLeg = 0.46;
	}
	else
	{
		xMinLeg = 0.58;
		xMaxLeg = 0.92;
	}
	TLegend *legend = new TLegend(xMinLeg, 0.49, xMaxLeg, 0.75);
	legend->SetHeader("m_{12}=" + Mass + " GeV", "C");
	legend->SetTextSize(0.035);
	legend->AddEntry(PDF, signs[0], "lpe");
	legend->AddEntry(hist, signs[1], "l");
	legend->AddEntry((TObject*) 0, Form("#chi^{2}/ndof = %.1f/%.0f = %.1f ", chi *ndof, ndof, chi), "");
	legend->AddEntry((TObject*) 0, Form("p-value= %.2f", p_value), "");
	legend->AddEntry((TObject*) 0, Form("%.0d<m_{12}<%.0d", xMinFit, xMaxFit), "");
	frame->GetXaxis()->SetNdivisions(0);

	frame->Draw();
	legend->Draw();
	writeExtraText = true;
	extraText = "Work in progress";

	TLatex latex;
	latex.SetNDC();
	latex.SetTextAngle(0);
	latex.SetTextColor(kBlack);

	latex.SetTextFont(52);
	latex.SetTextAlign(15);
	latex.SetTextSize(0.04);
	latex.DrawLatex(0.2, 0.92, extraText);

	CMS_lumi(upper, 13, 33);
	c1->cd();

	TPad *lower = new TPad("lower", "pad", 0, 0, 1, 0.30);
	lower->Draw();
	lower->cd();
	lower->Modified();
	lower->SetTicks();
	lower->SetLeftMargin(0.2);
	lower->SetRightMargin(0.05);
	lower->SetTopMargin(0.026);
	lower->SetBottomMargin(0.35);
	lower->SetGridy();
	lower->SetTickx(1);
	lower->SetTicky(1);

    RooPlot *frame2 = x.frame(Title("   "));
	frame2->addPlotable(hpull, "P");
	frame2->SetStats(0);
	frame2->GetXaxis()->SetLabelFont(42);
	frame2->GetXaxis()->SetLabelOffset(0.03);
	frame2->GetXaxis()->SetLabelSize(0.14);
	frame2->GetXaxis()->SetTitleSize(0.13);
	frame2->GetXaxis()->SetTitleOffset(1.35);
	frame2->GetXaxis()->SetTitle("m_{12}[GeV]");
	frame2->GetXaxis()->SetTickLength(0.025);
	frame2->GetXaxis()->SetTickSize(0.08);
	frame2->GetYaxis()->SetRangeUser(-5.01, 5.01);
	frame2->GetXaxis()->SetRangeUser(xMinFit, xMaxFit);
	frame2->GetYaxis()->SetLabelOffset(0.008);
	frame2->GetYaxis()->SetLabelSize(0.08);
	frame2->GetYaxis()->SetTitleSize(0.1);
	frame2->GetYaxis()->SetNdivisions(6);
	frame2->GetYaxis()->SetTitleOffset(0.3);
	frame2->GetYaxis()->SetTitle("Pulls");
	frame2->GetYaxis()->SetTickLength(0.025);
	frame2->GetYaxis()->SetTickSize(0.02);
	frame2->SetLineColor(1);
	frame2->SetLineWidth(1);
	frame2->SetMarkerStyle(kFullCircle);
	frame2->SetMarkerColor(kBlack);
	frame2->SetMarkerSize(1);
	frame2->Draw();

	TLine *line = new TLine(xMinFit, 0, xMaxFit, 0);
	line->SetLineWidth(2);
	line->Draw();
	lower->Modified();
	lower->RedrawAxis();
	c1->SaveAs("Figs/SignalFits_v1/FittingDemo_" + Mass + "GeV.pdf");

	c1->cd();

	// Create a new frame to draw the residual distribution and add the distribution to the frame
	RooPlot *frame3 = x.frame(Title("Residual Distribution"));
	frame3->GetXaxis()->SetTitleOffset(1.35);
	frame3->GetYaxis()->SetTitleOffset(1.5);
	frame3->addPlotable(hresid, "P");
	frame3->GetXaxis()->SetTitle("m_{12}[GeV]");
	frame3->GetYaxis()->SetTitle(Form("Events / %.0f GeV", binWidth));
	frame3->Draw();
	c1->SaveAs("Figs/SignalFits_v1/Residuals/Residuals_" + Mass + "GeV.pdf");

	delete c1;
}

void PlotAll()
{

	gROOT->SetBatch();

	int nSamples = 12;

	//// Mass points	////
	int mpoints[13] = { 300, 350, 400, 450, 500, 600, 700, 800, 900, 1000, 1200, 1400, 1600 };

	//// Interpolated mass points	////
	int mpointsInt[13] = { 325, 375, 425, 475, 550, 650, 750, 850, 950, 1100, 1300, 1500, 1700 };

	for (int isample = 0; isample < nSamples; isample++)	// Loop over masses
	{
		FittingDemo_m12(mpoints[isample]);
	}	// End loop over masses

}
