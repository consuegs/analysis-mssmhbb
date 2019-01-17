#ifndef Analysis_MssmHbb_MssmHbbAnalyser_h
#define Analysis_MssmHbb_MssmHbbAnalyser_h 1

// -*- C++ -*-
//
// Package:    Analysis/MssmHbb
// Class:      Analysis
// 
/**\class Analysis MssmHbbAnalyser.cc Analysis/MssmHbb/src/MssmHbbAnalyser.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Roberval Walsh Bastos Rangel
//         Created:  Mon, 20 Oct 2014 14:24:08 GMT
//
//

// system include files
#include <memory>
#include <vector>
#include <string>
// 
// user include files

#include "Analysis/Tools/interface/Analyser.h"

//
// class declaration
//

namespace analysis {
   namespace mssmhbb {

      class MssmHbbAnalyser : public analysis::tools::Analyser {
         
         public:
            MssmHbbAnalyser();
            MssmHbbAnalyser(int argc, char ** argv);
           ~MssmHbbAnalyser();
           
//             virtual bool event(const int &);
//             virtual void histograms(const std::string &, const int & n = 1);
//             virtual void fillJetHistograms();
//             virtual void end();        
            // ----------member data ---------------------------
         protected:
               
         private:
               
         public:

      };
   }
}

#endif  // Analysis_MssmHbb_MssmHbbAnalyser_h
