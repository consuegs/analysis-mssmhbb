void wspace_read()
{

	vector<string> srmasses = { "300", "350", "400", "450", "500", "600", "700", "800", "900", "1000", "1200", "1400", "1600", "1800" };

	for (unsigned int i = 0; i < srmasses.size(); ++i)
	{

		TString srmass = srmasses[i];

		// R e a d   w o r k s p a c e   f r o m   f i l e
		// -----------------------------------------------

		// Open input file with workspace 
		TFile *f = new TFile("input_parametrized_2018_2017TF_FH/signal_workspace_" + srmass + ".root");

		// Retrieve workspace from file
		RooWorkspace *w = (RooWorkspace*) f->Get("wspace");

		// R e t r i e v e   p d f  f r o m   w o r k s p a c e
		// -----------------------------------------------------------------

		// Retrieve models from workspace
		RooAbsPdf *signal = w->pdf("signal");
		RooAbsPdf *background = w->pdf("background");
		RooAbsPdf *signalregion = w->pdf("signalregion");
		RooAbsPdf *TF = w->pdf("TF");

		cout << "Mass point " << srmass << " GeV:" << endl;
		cout << endl;
		cout << "Parameters signal model:" << endl;
		signal->Print("t");
		cout << endl;
		cout << "Parameters background model in CR:" << endl;
		cout << endl;
		background->Print("t");
		cout << endl;
		cout << "Parameters background model in SR:" << endl;
		cout << endl;
		signalregion->Print("t");
		cout << endl;
		cout << "Parameters Transfer factor:" << endl;
		cout << endl;
		TF->Print("t");
		cout << endl;
	}
}
