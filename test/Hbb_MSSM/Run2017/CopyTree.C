#include <fstream>
#include "TFile.h"
#include "TTree.h"
#include "TROOT.h"

void CopyTree(TString mass = "300", int reduceFactor = 5)
{
	// Read signal tree and fill a new tree with a subset of the total number of events

	TFile *oldfile = new TFile("SignalRootFiles/mc-sig-" + mass + "-NLO-deep-SR-3j.root");
	TTree *tree_oldfile = (TTree*) oldfile->Get("MssmHbb_13TeV");
	Double_t mbb, weight;
	tree_oldfile->SetBranchAddress("mbb", &mbb);
	tree_oldfile->SetBranchAddress("weight", &weight);

	int nentries = tree_oldfile->GetEntries() / reduceFactor;

	// Create a new file 
	TFile *newfile = new TFile("SignalRootFiles_reducedstats/mc-sig-" + mass + "-NLO-deep-SR-3j.root", "RECREATE");
	TTree *tree_newfile = new TTree("MssmHbb_13TeV", "MssmHbb_13TeV");
	tree_newfile->Branch("mbb", &mbb);
	tree_newfile->Branch("weight", &weight);

	// Read all entries and fill the new tree
	for (int i = 0; i < nentries; i++)	////// loop over tree entries
	{
		tree_oldfile->GetEntry(i);
		tree_newfile->Fill();
	}
	////// end loop over tree entries

	tree_newfile->Write();

	newfile->Close();
}

void CopyAll()
{

	gROOT->SetBatch();

	int nSamples = 13;

	//// Mass points	////
	TString mpoints[13] = { "300", "350", "400", "450", "500", "600", "700", "800", "900", "1000", "1200", "1400", "1600" };

	for (int isample = 0; isample < nSamples; isample++)	// Loop over masses
	{
		CopyTree(mpoints[isample]);
	}	// End loop over masses

}
