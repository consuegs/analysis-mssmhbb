#include "TPad.h"
#include "TLatex.h"
#include "TLine.h"
#include "TBox.h"
#include "TASImage.h"

//
// Global variables
//

TString cmsText     = "CMS";
float cmsTextFont   = 61;  // default is helvetic-bold

bool writeExtraText = false;
TString extraText   = "Work in progress";
float extraTextFont = 52;  // default is helvetica-italics

// text sizes and text offsets with respect to the top frame
// in unit of the top margin size
float lumiTextSize     = 0.35;
float lumiTextOffset   = 0.1;
float cmsTextSize      = 0.55;
float cmsTextOffset    = 0.1;  // only used in outOfFrame version

float relPosX    = 0.045;
float relPosY    = 0.035;
float relExtraDY = 1.2;

// ratio of "CMS" and extra text size
float extraOverCmsTextSize  = 0.76;

TString lumi_13TeV_Run2 = "137.2 fb^{-1}";
TString lumi_13TeV_2016and2017 = "77.4 fb^{-1}";
TString lumi_13TeV_2018 = "2018, 59.7 fb^{-1}";
TString lumi_13TeV_2017 = "2017, 36.3 fb^{-1}";
TString lumi_13TeV_2016 = "2016, 35.9 fb^{-1}";
TString lumi_8TeV  = "19.7 fb^{-1}";
TString lumi_7TeV  = "5.1 fb^{-1}";
TString lumi_null = "2017, 36.0 fb^{-1}";

bool drawLogo      = false;

void CMS_lumi( TPad* pad, int iPeriod=3, int iPosX=10 );

