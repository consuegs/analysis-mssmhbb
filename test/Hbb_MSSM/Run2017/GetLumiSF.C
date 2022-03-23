void GetLumiSF()
{

	float lumi_2017_FH = 36260;
	float lumi_2017_SL = 36670;

	vector<int> masses_FH = { 300, 350, 400, 450, 500, 600, 700, 800, 900, 1000, 1200, 1400, 1600, 1800 };
	vector<string> srmasses_FH = { "300", "350", "400", "450", "500", "600", "700", "800", "900", "1000", "1200", "1400", "1600", "1800" };

	vector<int> masses_SL = { 125, 130, 140, 160, 180, 200, 250, 300, 350, 400, 450, 500, 600, 700 };
	vector<string> srmasses_SL = { "125", "130", "140", "160", "180", "200", "250", "300", "350", "400", "450", "500", "600", "700" };

	TString dir("/nfs/dust/cms/user/consuegs/Analyses/Hbb_MSSM/analysis-mssmhbb/test/Hbb_MSSM/Run2017/forSandra/Feb2022_v6/");

	std::ofstream outtext("LumiSF_2017.txt");
	outtext << "Lumi Scale Factors FH channel:" << endl;
	outtext << endl;

	for (unsigned int i = 0; i < masses_FH.size(); ++i)
	{

		int mass_FH = masses_FH[i];

		TString srmass_FH = srmasses_FH[i];

		TFile *file_FH = new TFile(dir + "FH/FH_SUSYGluGluToBBHToBB_M-" + srmass_FH + "_2017-v6.root", "READ");

		TH1D *hist_FH = (TH1D*) file_FH->Get("nentries");

		float lumiSF_FH = (hist_FH->GetBinContent(2) - hist_FH->GetBinContent(1)) / lumi_2017_FH;

		outtext << endl;
		outtext << mass_FH << " GeV: " << setprecision(4) << lumiSF_FH << endl;
		outtext << endl;
	}

	outtext << endl;
	outtext << endl;
	outtext << "Lumi Scale Factors SL channel:" << endl;
	outtext << endl;

	for (unsigned int i = 0; i < masses_SL.size(); ++i)
	{

		int mass_SL = masses_SL[i];

		TString srmass_SL = srmasses_SL[i];

		TFile *file_SL = new TFile(dir + "/SL/SL_SUSYGluGluToBBHToBB_M-" + srmass_SL + "_2017-v6.root", "READ");

		TH1D *hist_SL = (TH1D*) file_SL->Get("nentries");

		float lumiSF_SL = (hist_SL->GetBinContent(2) - hist_SL->GetBinContent(1)) / lumi_2017_SL;

		outtext << endl;
		outtext << mass_SL << " GeV: " << setprecision(4) << lumiSF_SL << endl;
		outtext << endl;
	}
}
