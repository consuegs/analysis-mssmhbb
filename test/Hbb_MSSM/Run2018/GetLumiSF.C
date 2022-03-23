void GetLumiSF()
{

	float lumi_2018 = 54540;

	vector<int> masses = { 300, 350, 400, 450, 500, 600, 700, 800, 900, 1000, 1200, 1400, 1600, 1800 };
	vector<string> srmasses = { "300", "350", "400", "450", "500", "600", "700", "800", "900", "1000", "1200", "1400", "1600", "1800" };

	std::ofstream outtext("LumiSF_2018.txt");
	outtext << "Lumi Scale Factors:" << endl;
	outtext << endl;

	TString dir("/nfs/dust/cms/user/consuegs/Analyses/Hbb_MSSM/analysis-mssmhbb/test/Hbb_MSSM/Run2018/");

	for (unsigned int i = 0; i < masses.size(); ++i)
	{

		int mass = masses[i];

		TString srmass = srmasses[i];

		TFile *file = new TFile(dir + "/mssmHbb_FH_2018_MC_signal_MP_" + srmass + ".root", "READ");

		TH1D *hist = (TH1D*) file->Get("nentries");

		float lumiSF = (hist->GetBinContent(2) - hist->GetBinContent(1)) / lumi_2018;

		outtext << endl;
		outtext << mass << " GeV: " << setprecision(4) << lumiSF << endl;
		outtext << endl;
	}
}
