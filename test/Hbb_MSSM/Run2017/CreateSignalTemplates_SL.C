#include "CMS_lumi.C"
using namespace RooFit;

// SR1 : 120-300
// SR2 : 160-450
// SR3 : 240-800
// former SR3 (240-580) and SR4 (350-800) merged

map<int, double> lumi_sf = {
	{125,48.91},
	{130,49.75},
	{140,50.26},
	{160,51.06},
	{180,50.03},
	{200,51.49},
	{250,50.87},
	{300,52.28},
	{350,53.77},
	{400,54.45},
	{450,53.67},
	{500,54.19},
	{600,59.09},
	{700,59.03},
};

map<int, int> mass_region = {
	{125,1},
	{130,1},
	{140,1},
	{160,1},
	{180,1},
	{200,1},
	{250,1},
	{300,2},
	{350,2},
	{400,2},
	{450,3},
	{500,3},
	{600,3},
	{700,3},
};

map<int, int> mass_binning = {
	{125,1},
	{130,1},
	{140,1},
	{160,1},
	{180,1},
	{200,1},
	{250,1},
	{300,1},
	{350,1},
	{400,1},
	{450,1},
	{500,1},
	{600,1},
	{700,1},
};

map<int, double> mbb_low = {
	{1,120.},
	{2,160.},
	{3,240.},
};

map<int, double> mbb_high = {
	{1,300.},
	{2,450.},
	{3,800.},
};

TString dir("/nfs/dust/cms/user/consuegs/Analyses/Hbb_MSSM/analysis-mssmhbb/test/Hbb_MSSM/Run2017/forSandra/Sep2022_v6/SL/Central");

map<TString, TString> histName_suffix = {
		{
		"nominal", "" },
};

TString IntToStr(int i)
{

	char c[10];
	if (i < 10)
		sprintf(c, "%1i", i);
	else if (i < 100)
		sprintf(c, "%2i", i);
	else if (i < 1000)
		sprintf(c, "%3i", i);
	else
		sprintf(c, "%4i", i);

	TString ST(c);

	return ST;
}
// initial fit parameters for double-sided crystall ball
// mass, mean, sigma, alpha1, alpha2, n1, n2
map<int, vector < double>> mass_fit = {
    { 125,{ 115.,25.,2.0,1.3, 12.,1.1}},
    { 130,{ 120.,25.,2.0,1.3, 12.,1.1}},
    { 140,{ 130.,25.,2.0,1.3, 12.,1.1}}, 
    { 160,{ 150.,25.,2.0,1.3, 12.,1.1}},
    { 180,{ 170.,25.,2.0,1.3, 12.,1.1}},
    { 200,{ 190.,25.,2.0,1.3, 12.,1.1}},
    { 250,{ 240.,25.,2.0,1.3, 12.,1.1}},
    { 300,{ 290.,30.,1.8,1.3, 12.,1.1}},
    { 350,{ 340.,35.,1.4,1.7,125.,1.0}},
    { 400,{ 380.,37.,0.9,1.6,132.,1.4}},
    { 450,{ 425.,41.,0.8,1.7,136.,1.4}},
    { 500,{ 470.,44.,0.7,1.8,133.,1.4}},
    { 600,{ 570.,48.,0.5,2.0,116.,0.8}},
    { 700,{ 670.,49.,0.5,1.6,118.,2.0}},
  
};

vector<int> masses = { 125, 130, 140, 160, 180, 200, 250, 300, 350, 400, 450, 500, 600, 700 };

std::ofstream outtext("signal_out_SL.txt");

void CreateSignalPDF(int mass,
	int region,
	vector<TString> histNames,
	map<TString, TH1D*> Hists,
	RooWorkspace *w,
	double mbb_min,
	double mbb_max)
{

	TH1::SetDefaultSumw2(true);

	std::map<TString, double> mapMean;
	std::map<TString, double> mapSigma;
	std::map<TString, double> mapAlpha1;
	std::map<TString, double> mapAlpha2;
	std::map<TString, double> mapN1;
	std::map<TString, double> mapN2;
	std::map<TString, double> mapNorm;

	double Mean = mass_fit[mass][0];
	double Sigma = mass_fit[mass][1];
	double Alpha1 = mass_fit[mass][2];
	double Alpha2 = mass_fit[mass][3];
	double N1 = mass_fit[mass][4];
	double N2 = mass_fit[mass][5];

	outtext << "++++++++++++++++++++++++++++++++++" << std::endl;
	outtext << std::endl;
	outtext << "Mass : " << mass << "  SR" << region << std::endl;

	for (auto histName: histNames)
	{

		outtext << std::endl;
		outtext << std::endl;
		outtext << "Histogram name : " << histName << std::endl;
		outtext << std::endl;

		TH1D *hist = Hists[histName];
		if (mass < 180)
		{
			hist->Rebin(3);
		}
		else
		{
			hist->Rebin(10);
		}

		// Bin width
		double nBinsFullRange = hist->GetNbinsX();
		double nBins = 0;
		for (int i = 1; i <= hist->GetNbinsX(); ++i)
		{
			double center = hist->GetBinCenter(i);
			if (center > mbb_min && center < mbb_max)
				++nBins;
		}

		double binWidth = (mbb_max - mbb_min) / nBins;

		for (int iB = 1; iB <= nBinsFullRange; ++iB)
		{
			if (hist->GetBinContent(iB) < 0)
			{
				hist->SetBinContent(iB, 0.);
			}
		}
		double norm = hist->GetSumOfWeights() / lumi_sf[mass];

		outtext << "signal normalization = " << norm << endl;
		outtext << endl;

		RooRealVar mbbx("mbbx", "M_{12}", mbb_min, mbb_max);

		RooRealVar meanx("mean", "Mean", Mean, 0.5 *Mean, 1.5 *Mean);
		RooRealVar sigmax("sigma", "Width", Sigma, 0., 2.0 *Sigma);

		RooRealVar alpha1x("alpha1", "Alpha1", Alpha1, 0, 50 *Alpha1);
		RooRealVar n1x("n1", "N1", N1, 0, 50 *N1);

		RooRealVar alpha2x("alpha2", "Alpha2", Alpha2, 0, 50 *Alpha2);
		RooRealVar n2x("n2", "N2", N2, 0, 50 *N2);

		RooDoubleCB cbx("cb", "CBshape", mbbx, meanx, sigmax, alpha1x, n1x, alpha2x, n2x);

		RooDataHist sig("sig", "sig", mbbx, hist);

		RooFitResult *res = cbx.fitTo(sig, Save(), SumW2Error(kTRUE));
		res->Print();
		outtext << "Fit result with DoubleCB[" << mbb_min << "," << mbb_max << "] -> " << std::endl;
		outtext << "Mean   = " << meanx.getVal() << " +/- " << meanx.getError() << std::endl;
		outtext << "Sigma  = " << sigmax.getVal() << " +/- " << sigmax.getError() << std::endl;
		outtext << "Alpha1 = " << alpha1x.getVal() << " +/- " << alpha1x.getError() << std::endl;
		outtext << "N1     = " << n1x.getVal() << " +/- " << n1x.getError() << std::endl;
		outtext << "Alpha2 = " << alpha2x.getVal() << " +/- " << alpha2x.getError() << std::endl;
		outtext << "N2     = " << n2x.getVal() << " +/- " << n2x.getError() << std::endl;

		TString Mass = IntToStr(mass);
		TString Region = IntToStr(region);

		TCanvas *c1 = new TCanvas("c1", "", 700, 700);
		RooPlot *frame1 = mbbx.frame(Name("MMSM H->bb analysis"), Title("   "));
		frame1->GetXaxis()->SetTitle("m_{12}[GeV]");
		frame1->GetYaxis()->SetTitle(Form("Events / %.0f GeV", binWidth));
		sig.plotOn(frame1, MarkerSize(1.1));
		cbx.plotOn(frame1, LineColor(kRed), LineWidth(3));
		c1->SetLeftMargin(0.1);
		c1->SetBottomMargin(0.1);
		gPad->SetLeftMargin(0.13);
		frame1->Draw();

		//// Selecting legend names for 	////	
		for (int i = 0; i < frame1->numItems(); i++)
		{
			TString obj_name = frame1->nameOf(i);
			if (obj_name == "") continue;
		}
		TString names[] = { "h_sig",
			"PDF_Norm[x]",
			"" };
		TString signs[] = { "Simulated Signal",
			//  "Fit Error",
			"Global Fit",
		};
		//// Legend	////
		float xpad1Leg;
		if (mass == 500 || mass == 600 || mass == 700)
		{
			xpad1Leg = 0.42;
		}
		else
		{
			xpad1Leg = 0.98;
		}

		int fitRangeMin, fitRangeMax;
		if (mass < 250)
		{
			fitRangeMin = 120;
			fitRangeMax = 300;
		}
		else if (mass >= 250 &mass < 400)
		{
			fitRangeMin = 160;
			fitRangeMax = 450;
		}
		else if (mass >= 400 &mass < 600)
		{
			fitRangeMin = 240;
			fitRangeMax = 580;
		}
		else
		{
			fitRangeMin = 350;
			fitRangeMax = 800;
		}
    
		int nParameters = res->floatParsFinal().getSize();
		double chi = frame1->chiSquare(nParameters);
		double ndof = nBins - nParameters;
		double p_value = TMath::Prob(chi *ndof, ndof);
		cout << "M_{12} = " + Mass + " GeV: " << endl;
		cout << "Bin width: " << binWidth << endl;
		cout << "Number of parameters of double sided crystal ball = " << nParameters << endl;
		cout << "chi^2 / ndof = " << Form("%.2f", chi *ndof) << " / " << nBins - nParameters << " = " << chi << endl;
		cout << "p-value = " << Form("%.2f", p_value) << endl;
		cout << "//////////////////////////////////////////" << endl;

		TPad * pad1;
		pad1 = new TPad("pad1", "", 0, 0.1, 1, 1);
		pad1->SetBottomMargin(0.2);
		pad1->SetRightMargin(0.05);
		pad1->SetLeftMargin(0.16);
		pad1->Draw();
		pad1->cd();
		frame1->GetXaxis()->SetTitleOffset(999);	//Effectively turn off x axis title on main plot
		frame1->GetXaxis()->SetLabelOffset(999);	//Effectively turn off x axis label on main plot
		frame1->GetYaxis()->SetTitleSize(0.038);
		frame1->GetYaxis()->SetTitleOffset(1.6);
		frame1->GetYaxis()->SetLabelSize(0.033);
		frame1->Draw();

		float lumi_2017_SL = 36.67;

		std::string lumistr(Form("%.1f", lumi_2017_SL));
		std::string chi2str(Form("#chi^{2}/ndof = %.2f ", chi));
		std::string probstr(Form("p-value= %.2f", p_value));

		TLatex latex;
		latex.SetTextFont(61);
		latex.SetTextSize(0.06);
		latex.SetTextAlign(11);
		latex.DrawLatexNDC(pad1->GetLeftMargin(), 1.02 - c1->GetTopMargin(),
			std::string("CMS").c_str());
		latex.SetTextFont(52);
		latex.SetTextSize(0.04);
		latex.DrawLatexNDC(pad1->GetLeftMargin() + 0.12, 1.02 - c1->GetTopMargin(),
			std::string("Work in progress").c_str());
		latex.SetTextFont(43);
		latex.SetTextSize(22);
		latex.DrawLatexNDC(0.71, 1.02 - c1->GetTopMargin(),
			(lumistr + std::string(" fb^{-1} (13 TeV)")).c_str());
		latex.SetTextAlign(33);
		latex.SetTextSize(18);
		latex.SetTextColor(kBlack);
		latex.DrawLatexNDC(xpad1Leg - pad1->GetRightMargin(), 0.98 - pad1->GetTopMargin(),
			(std::string("M_{12} = ") + Mass + std::string(" GeV")));
		latex.SetTextColor(kBlue + 2);
		latex.DrawLatexNDC(xpad1Leg - pad1->GetRightMargin() + 0.01, 0.93 - pad1->GetTopMargin(),
			chi2str.c_str());
		latex.SetTextColor(kGreen + 2);
		latex.DrawLatexNDC(xpad1Leg - pad1->GetRightMargin(), 0.88 - pad1->GetTopMargin(),
			probstr.c_str());
		latex.SetTextColor(kOrange + 2);
		std::string minstr(Form("%.0d", fitRangeMin));
		std::string maxstr(Form("%.0d", fitRangeMax));
		latex.DrawLatexNDC(xpad1Leg - pad1->GetRightMargin(), 0.83 - pad1->GetTopMargin(),
			(minstr + std::string("<M_{12}<") + maxstr).c_str());

		// Construct a histogram with the pulls of the data w.r.t the curve (('curve' - histogram) / err_histogram)
		RooHist *hpull = frame1->pullHist();
		hpull->SetMarkerSize(0.8);	
		std::unique_ptr<RooPlot> frame2(mbbx.frame());
		frame2->addPlotable(hpull, "P");

		c1->cd();
		TPad *pad2 = new TPad("pad2", "", 0, 0.0, 1, 0.265);
		pad2->SetTopMargin(1);
		pad2->SetBottomMargin(0.33);
		pad2->SetLeftMargin(pad1->GetLeftMargin());
		pad2->SetRightMargin(pad1->GetRightMargin());
		pad2->SetGridy();
		pad2->Draw();
		pad2->cd();
		frame2->SetTitle("");
		frame2->GetXaxis()->SetTitleSize(0.15);
		frame2->GetXaxis()->SetTitleOffset(0.9);
		frame2->GetXaxis()->SetLabelSize(0.115);
		frame2->GetXaxis()->SetLabelOffset(0.010);
		frame2->SetYTitle("Pulls");
		frame2->GetYaxis()->CenterTitle(kTRUE);
		frame2->GetYaxis()->SetTitleSize(0.14);
		frame2->GetYaxis()->SetTitleOffset(0.4);
		frame2->GetYaxis()->SetNdivisions(3, 5, 0);
		frame2->GetYaxis()->SetLabelSize(0.115);
		frame2->GetYaxis()->SetLabelOffset(0.011);
		frame2->SetMinimum(-5.);
		frame2->SetMaximum(+5.);
		frame2->Draw();

		c1->Print("Figs/SL/Mass" + Mass + "_SR" + Region + "_" + histName + "_doubleCB.png");
		c1->Print("Figs/SL/Mass" + Mass + "_SR" + Region + "_" + histName + "_doubleCB.pdf");
		delete c1;

		mapMean[histName] = meanx.getVal();
		mapSigma[histName] = sigmax.getVal();
		mapAlpha1[histName] = alpha1x.getVal();
		mapAlpha2[histName] = alpha2x.getVal();
		mapN1[histName] = n1x.getVal();
		mapN2[histName] = n2x.getVal();
		mapNorm[histName] = norm;
	}

	double norm_Val = mapNorm["nominal"];
	double mean_Val = mapMean["nominal"];
	double sigma_Val = mapSigma["nominal"];
	double alpha1_Val = mapAlpha1["nominal"];
	double alpha2_Val = mapAlpha2["nominal"];
	double n1_Val = mapN1["nominal"];
	double n2_Val = mapN2["nominal"];

	RooRealVar mbb("mbb", "M_{12}", mbb_min, mbb_max);
	RooRealVar mean("mean", "mean", 0.5 *mean_Val, 2 *mean_Val);
	RooRealVar sigma("sigma", "sigma", 0.5 *sigma_Val, 2 *sigma_Val);
	RooRealVar alpha1("alpha1", "alpha1", 0.5 *alpha1_Val, 2 *alpha1_Val);
	RooRealVar alpha2("alpha2", "alpha2", 0.5 *alpha2_Val, 2 *alpha2_Val);
	RooRealVar n1("n1", "n1", 0.5 *n1_Val, 2 *n1_Val);
	RooRealVar n2("n2", "n2", 0.5 *n2_Val, 2 *n2_Val);

	RooRealVar norm_dcb("norm_dcb", "norm_dcb", 0.5 *norm_Val, 2 *norm_Val);

	mean.setVal(mean_Val);
	sigma.setVal(sigma_Val);
	alpha1.setVal(alpha1_Val);
	alpha2.setVal(alpha2_Val);
	n1.setVal(n1_Val);
	n2.setVal(n2_Val);

	norm_dcb.setVal(norm_Val);

	mean.setConstant(true);
	sigma.setConstant(true);
	alpha1.setConstant(true);
	alpha2.setConstant(true);
	n1.setConstant(true);
	n2.setConstant(true);

	norm_dcb.setConstant(true);

	RooDoubleCB signal_dcb("signal_dcb", "DoubleCB", mbb, mean, sigma, alpha1, n1, alpha2, n2);

	outtext << endl;
	outtext << endl;
	outtext << "norm   = " << norm_Val << endl;
	outtext << "mean   = " << mean_Val << endl;
	outtext << "sigma  = " << sigma_Val << endl;
	outtext << endl;
	outtext << "Evaluation function within fitted range" << endl;
	int nbins = Hists["nominal"]->GetNbinsX();
	outtext << "number of bins = " << nbins << endl;

	for (int ib = 1; ib <= nbins; ++ib)
	{
		double xbin = Hists["nominal"]->GetXaxis()->GetBinCenter(ib);
		char xbinCh[10];
		sprintf(xbinCh, "%6.1f", xbin);
		TString xbinStr(xbinCh);
		mbb.setVal(xbin);
		double pdf = signal_dcb.getVal();
		outtext << xbinStr << " : " << pdf << endl;
	}

	outtext << endl;
	outtext << endl;

	w->import(signal_dcb);
	w->import(norm_dcb);

}

void CreateSignalTemplates_SL()
{

	vector<TString> histNames = { "nominal" };

	for (unsigned int i = 0; i < masses.size(); ++i)
	{

		RooWorkspace *w = new RooWorkspace("wsignal", "signal");

		int mass = masses[i];
		int region = mass_region[mass];
		int bin = mass_binning[mass];
		TString Mass = IntToStr(mass);
		TString Region = IntToStr(region);
		TString Bin = IntToStr(bin);
		map<TString, TH1D*> Hists;
		double mbb_min = mbb_low[region];
		double mbb_max = mbb_high[region];
		for (auto histName: histNames)
		{
			TFile *file = new TFile(dir + "/SL_SUSYGluGluToBBHToBB_M-" + Mass + "_2017-v6.root", "READ");
			TH1D *hist = (TH1D*) file->Get("mbb");
			Hists[histName] = hist;
		}
		CreateSignalPDF(mass, region, histNames, Hists, w, mbb_min, mbb_max);
		TFile *fileOutput = new TFile("input_doubleCB_SL/signal_m" + Mass + "_SR" + Region + ".root", "recreate");
		fileOutput->cd("");
		w->Write("w");
		fileOutput->Write();
		fileOutput->Close();
	}
}
