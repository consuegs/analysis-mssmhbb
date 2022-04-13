void GetNEvents()
{

	std::ofstream outtext("NEvents.txt");
	outtext << "Number of events:" << endl;
	outtext << endl;

	TString dir("/nfs/dust/cms/user/consuegs/Analyses/Hbb_MSSM/analysis-mssmhbb/test/Hbb_MSSM/");

	// Signal mass point of 300 GeV for ReReco 17, UL 17, and UL 18
	TFile *file_Sig17ReReco = new TFile(dir + "Run2017_ReReco/mc-sig-300-NLO-deep-SR-3j.root", "READ");
	TFile *file_Sig17UL = new TFile(dir + "Run2017/forSandra/April2022_v6/FH/FH_SUSYGluGluToBBHToBB_M-300_2017-v6.root", "READ");
	TFile *file_Sig18UL = new TFile(dir + "Run2018/mssmHbb_FH_2018_MC_signal_MP_300.root", "READ");

	TH1D *histSig17ReReco_SR1 = (TH1D*) file_Sig17ReReco->Get("m12_SR1_1GeV");
	TH1D *histSig17ReReco_SR2 = (TH1D*) file_Sig17ReReco->Get("m12_SR2_1GeV");
	TH1D *histSig17ReReco_SR3 = (TH1D*) file_Sig17ReReco->Get("m12_SR3_5GeV");
	TH1D *histSig17ReReco_SR4 = (TH1D*) file_Sig17ReReco->Get("m12_SR4_10GeV");
	TH1D *histSig17ReReco = (TH1D*) file_Sig17ReReco->Get("m12_aac");

	TH1D *histSig17UL = (TH1D*) file_Sig17UL->Get("mbb");
	TH1D *histSig18UL = (TH1D*) file_Sig18UL->Get("mbb");

	// CR
	TFile *file_CR17ReReco = new TFile(dir + "Run2017_ReReco/DataRootFiles/rereco-CDEF-deep-CR-3j.root", "READ");
	TFile *file_CR17UL = new TFile(dir + "Run2017/forSandra/April2022_v6/FH/FullhadCR_BTagCSV_UL2017-v6.root", "READ");
	TFile *file_CR18UL = new TFile(dir + "Run2018/mssmhbb_FH_2018_DataABCD_CR.root", "READ");

	TH1D *histCR17ReReco_SR1 = (TH1D*) file_CR17ReReco->Get("m12_SR1_1GeV");
	TH1D *histCR17ReReco_SR2 = (TH1D*) file_CR17ReReco->Get("m12_SR2_1GeV");
	TH1D *histCR17ReReco_SR3 = (TH1D*) file_CR17ReReco->Get("m12_SR3_5GeV");
	TH1D *histCR17ReReco_SR4 = (TH1D*) file_CR17ReReco->Get("m12_SR4_10GeV");
	TH1D *histCR17ReReco = (TH1D*) file_CR17ReReco->Get("m12_aac");

	TH1D *histCR17UL = (TH1D*) file_CR17UL->Get("mbb");
	TH1D *histCR18UL = (TH1D*) file_CR18UL->Get("mbb");

	//SR
	TFile *file_SR17ReReco = new TFile(dir + "Run2017_ReReco/DataRootFiles/rereco-CDEF-deep-SR-3j.root", "READ");
	TFile *file_SR17UL = new TFile(dir + "Run2017/forSandra/April2022_v6/FH/FullhadSR_BTagCSV_UL2017-v6.root", "READ");
	TFile *file_SR18UL = new TFile(dir + "Run2018/mssmhbb_FH_2018_DataABCD_SR.root", "READ");

	TH1D *histSR17ReReco_SR1 = (TH1D*) file_SR17ReReco->Get("m12_SR1_1GeV");
	TH1D *histSR17ReReco_SR2 = (TH1D*) file_SR17ReReco->Get("m12_SR2_1GeV");
	TH1D *histSR17ReReco_SR3 = (TH1D*) file_SR17ReReco->Get("m12_SR3_5GeV");
	TH1D *histSR17ReReco_SR4 = (TH1D*) file_SR17ReReco->Get("m12_SR4_10GeV");
	TH1D *histSR17ReReco = (TH1D*) file_SR17ReReco->Get("m12_aac");

	TH1D *histSR17UL = (TH1D*) file_SR17UL->Get("mbb");
	TH1D *histSR18UL = (TH1D*) file_SR18UL->Get("mbb");

	outtext << "Signal mass point 300 GeV: " << endl;
	outtext << "2017 ReReco Fit range 1: " << histSig17ReReco_SR1->GetSumOfWeights() << endl;
	outtext << "2017 ReReco Fit range 2: " << histSig17ReReco_SR2->GetSumOfWeights() << endl;
	outtext << "2017 ReReco Fit range 3: " << histSig17ReReco_SR3->GetSumOfWeights() << endl;
	outtext << "2017 ReReco Fit range 4: " << histSig17ReReco_SR4->GetSumOfWeights() << endl;
	outtext << endl;
	outtext << "Total: " << endl;
	outtext << "2017 ReReco: " << histSig17ReReco->GetSumOfWeights() << endl;
	outtext << "2017 UL: " << histSig17UL->GetSumOfWeights() << endl;
	outtext << "2018 UL: " << histSig18UL->GetSumOfWeights() << endl;
	outtext << endl;
	outtext << "Data events in CR: " << endl;
	outtext << "2017 ReReco Fit range 1: " << histCR17ReReco_SR1->GetEntries() << endl;
	outtext << "2017 ReReco Fit range 2: " << histCR17ReReco_SR2->GetEntries() << endl;
	outtext << "2017 ReReco Fit range 3: " << histCR17ReReco_SR3->GetEntries() << endl;
	outtext << "2017 ReReco Fit range 4: " << histCR17ReReco_SR4->GetEntries() << endl;
	outtext << endl;
	outtext << "Total: " << endl;
	outtext << "2017 ReReco: " << histCR17ReReco->GetEntries() << endl;
	outtext << "2017 UL: " << histCR17UL->GetEntries() << endl;	
	outtext << "2018 UL: " << histCR18UL->GetEntries() << endl;
	outtext << endl;
	outtext << "Data events in SR: " << endl;
	outtext << "2017 ReReco Fit range 1: " << histSR17ReReco_SR1->GetEntries() << endl;
	outtext << "2017 ReReco Fit range 2: " << histSR17ReReco_SR2->GetEntries() << endl;
	outtext << "2017 ReReco Fit range 3: " << histSR17ReReco_SR3->GetEntries() << endl;
	outtext << "2017 ReReco Fit range 4: " << histSR17ReReco_SR4->GetEntries() << endl;
	outtext << endl;
	outtext << "Total: " << endl;
	outtext << "2017 ReReco: " << histSR17ReReco->GetEntries() << endl;
	outtext << "2017 UL: " << histSR17UL->GetEntries() << endl;
	outtext << "2018 UL: " << histSR18UL->GetEntries() << endl;
	outtext << endl;
	outtext << "Ratios and %:" << endl;
	outtext << "2017 ReReco CR / 2017 ReReco SR: " << setprecision(6) << histCR17ReReco->GetEntries() / histSR17ReReco->GetEntries() << endl;
	outtext << "2017 UL CR / 2017 UL SR: " << setprecision(6) << histCR17UL->GetEntries() / histSR17UL->GetEntries() << endl;
	outtext << "2018 UL CR / 2018 UL SR: " << setprecision(6) << histCR18UL->GetEntries() / histSR18UL->GetEntries() << endl;
	outtext << endl;
	outtext << "2017 UL / 2017 ReReco CR: " << setprecision(6) << (histCR17UL->GetEntries() / histCR17ReReco->GetEntries()) * 100 << "%" << endl;
	outtext << "2017 UL / 2017 ReReco SR: " << setprecision(6) << (histSR17UL->GetEntries() / histSR17ReReco->GetEntries()) * 100 << "%" << endl;

}
