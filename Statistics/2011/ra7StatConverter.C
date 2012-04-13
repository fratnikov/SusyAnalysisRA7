//
// F. Ratnikov, KIT, Feb. 2011 (fedor.ratnikov@cern.ch)
// 
#include "ra7StatConverter.h"

#include <dirent.h>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include <stdio.h>

#include <set>
#include <algorithm>

#include "Math/ProbFuncMathCore.h"


using namespace std;

namespace {

  vector<string> tokenize (const string& fInput) {
    vector<string> result;
    string buf; 
    stringstream ss (fInput);
    while (ss >> buf) result.push_back(buf);
    return result;
  }


  vector<string> getdir (const string& dir) {
    vector<string> result;
    string prefix = dir + '/';
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
      cout << "Error opening " << dir << endl;
      return result;
    }
    
    while ((dirp = readdir(dp)) != NULL) {
      string name = dirp->d_name;
      if (name[0] != '.' && name.find (".txt") == name.length()-4) {
	result.push_back(prefix+name);
      }
    }
    closedir(dp);
    return result;
  }

  string getFile (const string& dir, int m0, int m12) {
    string result;
    string prefix = dir + '/';
    char pattern1 [1024];
    char pattern2 [1024];
    //    sprintf (pattern1, "m0_%d_m12_%d.txt", m0, m12);
    sprintf (pattern1, "_%d_%d.txt", m0, m12);
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
      cout << "Error opening " << dir << endl;
      return result;
    }
    
    while ((dirp = readdir(dp)) != NULL) {
      string name = dirp->d_name;
      // cout << "found file " << name << " " << pattern2 << endl;
      if (name.find (pattern1) != string::npos) {
	result = prefix+name;
	break;
      }
    }
    closedir(dp);
    return result;
  }

  bool lessSigSignificance (const ra7StatConverter::Signature& a, const ra7StatConverter::Signature& b) {
    return a.sigSig() < b.sigSig();
  }

  bool lessDDBkgSignificance (const ra7StatConverter::Signature& a, const ra7StatConverter::Signature& b) {
    return a.sigBkgDD() < b.sigBkgDD();
  }

  bool lessObservedSignificance (const ra7StatConverter::Signature& a, const ra7StatConverter::Signature& b) {
    return fabs(a.sigObserved()) > fabs(b.sigObserved());
  }


  double quickCLsCalculator (double signal, double bkg, int observed) {
    double clsb = ROOT::Math::poisson_cdf (observed, signal+bkg);
    double clb = ROOT::Math::poisson_cdf (observed, bkg);
    double result = 1.;
    if (clb > 0) result = clsb / clb;
    return result;
  }
  
  double quickLimitCalculator (int observed, double bkg, double dbkg = 0, double dscale = 0) {
    double CL = 0.05;
    // limit without uncertainties
    double limit = 2.5;
    double limitprev = limit;
    double cls = quickCLsCalculator (limit, bkg, observed);
    double clsprev = cls;
    while (cls > CL) {
      limitprev = limit;
      clsprev = cls;
      limit *= 2.;
      cls = quickCLsCalculator (limit, bkg, observed);
    }
    while (fabs (cls - CL) > CL*0.01) {
      double newlimit = cls > CL ? limit + 0.5*fabs(limitprev-limit) :
	limit - 0.5*fabs(limitprev-limit);
      limitprev = limit;
      limit = newlimit;
      clsprev = cls;
      cls = quickCLsCalculator (limit, bkg, observed);
    }
    // bkg & scale uncertainty
    limit = sqrt (limit*limit + bkg*bkg) * sqrt (1.+dscale*dscale);
    return limit;
  }
}

namespace ra7StatConverter {

  string ruChannel (const string& kitCh) {
    const char* ruChannels [] = {
      /*1*/ "L4T0METVHTVZV", "L4T0METVHTV", "L4T0METVZV", "L4T0METV", "L4T0HTVZV",
      /*6*/ "L4T0HTV", "L4T0ZV", "L4T0", "L3DY0T0METVHTV", "L3DY0T0METV",
      /*11*/ "L3DY0T0HTV", "L3DY0T0", "L3DY1T0METVHTVZV", "L3DY1T0METVHTV", "L3DY1T0METVZV",
      /*16*/ "L3DY1T0METV", "L3DY1T0HTVZV", "L3DY1T0HTV", "L3DY1T0ZV", "L3DY1T0",
      /*21*/ "L4T1METVHTVZV", "L4T1METVHTV", "L4T1METVZV", "L4T1METV", "L4T1HTVZV",
      /*26*/ "L4T1HTV", "L4T1ZV", "L4T1", "L3DY0T1METVHTV", "L3DY0T1METV",
      /*31*/ "L3DY0T1HTV", "L3DY0T1", "L3DY1T1METVHTVZV", "L3DY1T1METVHTV", "L3DY1T1METVZV",
      /*36*/ "L3DY1T1METV", "L3DY1T1HTVZV", "L3DY1T1HTV", "L3DY1T1ZV", "L3DY1T1",
      /*41*/ "L4T2METVHTVZV", "L4T2METVHTV", "L4T2METVZV", "L4T2METV", "L4T2HTVZV",
      /*46*/ "L4T2HTV", "L4T2ZV", "L4T2", "L3DY0T2METVHTV", "L3DY0T2METV",
      /*51*/ "L3DY0T2HTV", "L3DY0T2"
    };
    if (kitCh.find ("ch") == 0) {
      int ichannel = atoi (kitCh.c_str()+2);
      if (ichannel >= 1 && ichannel <= 52) return string(ruChannels[ichannel-1]);
    }
    return "undefined";
  }

  string kitChannel (const string& ruCh) {
    char kit[] = "chxx";
    for (int i = 1; i <= 52; ++i) {
      sprintf (kit, "%2d", i);
      if (ruChannel (string(kit)) == ruCh) return string(kit);
    }
    return "undefined";
  }

  int kitChannelI (const string& ruCh) {
    char kit[] = "chxx";
    for (int i = 1; i <= 52; ++i) {
      sprintf (kit, "ch%d", i);
      if (ruChannel (string(kit)) == ruCh) return i;
    }
    return 0;
  }
  
  bool lessPull (const ra7StatConverter::Signature& a, const ra7StatConverter::Signature& b) {
    double pullA = fabs(a.observed - a.backgroundDD - a.backgroundMC) /
      sqrt (a.observed*a.observed + 
	    a.sigmaBackgroundDD*a.sigmaBackgroundDD + 
	    a.sigmaBackgroundMC*a.sigmaBackgroundMC);
    double pullB = fabs(b.observed - b.backgroundDD - b.backgroundMC) /
      sqrt (b.observed*b.observed + 
	    b.sigmaBackgroundDD*b.sigmaBackgroundDD + 
	    b.sigmaBackgroundMC*b.sigmaBackgroundMC);
    return pullA > pullB;
  }

  bool lessQuickLimit (const ra7StatConverter::Signature& a, const ra7StatConverter::Signature& b) {
    return a.quickLimit < b.quickLimit;
  }
  bool lessExpectedLimit (const ra7StatConverter::Signature& a, const ra7StatConverter::Signature& b) {
    return a.getExpectedLimit() < b.getExpectedLimit();
  }

  double Signature::sigObserved () const {
    double sig = observed - backgroundDD - backgroundMC;
    int sign = sig>0?1:-1;
    double dbkg = pow (backgroundDD*sigmaBackgroundDD,2) + pow (backgroundMC*sigmaBackgroundMC,2);
    sig = sig*sig / (double(observed>0?observed:1) + dbkg);
    return sqrt(sig)*sign;
  }

  double Signature::sigSig () const {
    double sig = sigmaYieldStat*sigmaYieldStat;
    //sig += pow(backgroundDD*sigmaBackgroundDD/yield,2);
    sig += pow(backgroundMC*sigmaBackgroundMC/yield,2);
    return sqrt(sig);
  }

  double Signature::sigBkgDD () const {
    double sig = backgroundDD < 1 ? 1 : 1./backgroundDD;
    sig += sigmaBackgroundDD*sigmaBackgroundDD;
    sig += backgroundMC*backgroundMC/backgroundDD/backgroundDD;
    return sqrt(sig);
  }

  double Signature::getQuickLimit () const {
    
    double bkg = backgroundDD + backgroundMC;
    double dbkg = sqrt (sigmaBackgroundDD*sigmaBackgroundDD + 
			sigmaBackgroundMC*sigmaBackgroundMC);
    double dscale = sqrt(sigmaLumi*sigmaLumi +
			 sigmaYieldStat*sigmaYieldStat +
			 sigmaYieldJes*sigmaYieldJes +
			 sigmaYieldPdf*sigmaYieldPdf +
			 sigmaTrigger*sigmaTrigger +
			 sigmaYieldMuon*sigmaYieldMuon +
			 sigmaYieldElectron*sigmaYieldElectron +
			 sigmaYieldTau*sigmaYieldTau);
    return quickLimitCalculator (observed, bkg, dbkg, dscale)/yield; 
  }

  double Signature::getExpectedLimit () const {
    double bkg = backgroundDD + backgroundMC;
    double dbkg = sqrt (sigmaBackgroundDD*sigmaBackgroundDD + 
			sigmaBackgroundMC*sigmaBackgroundMC);
    double dscale = sqrt(sigmaLumi*sigmaLumi +
			 sigmaYieldStat*sigmaYieldStat +
			 sigmaYieldJes*sigmaYieldJes +
			 sigmaYieldPdf*sigmaYieldPdf +
			 sigmaTrigger*sigmaTrigger +
			 sigmaYieldMuon*sigmaYieldMuon +
			 sigmaYieldElectron*sigmaYieldElectron +
			 sigmaYieldTau*sigmaYieldTau);
    return quickLimitCalculator (int(floor(bkg+0.5)), bkg, dbkg, dscale)/yield; 
  }


  double sumYield (const Signatures& fSignatures) {
    double result = 0;
    for (size_t i = 0; i < fSignatures.size(); ++i) result += fSignatures[i].yield;
    return result;
  }

  int sumObserved (const Signatures& fSignatures) {
    int result = 0;
    for (size_t i = 0; i < fSignatures.size(); ++i) result += fSignatures[i].observed;
    return result;
  }

  double sumBackgrounds (const Signatures& fSignatures) {
    double result = 0;
    for (size_t i = 0; i < fSignatures.size(); ++i) result += (fSignatures[i].backgroundDD+fSignatures[i].backgroundMC);
    return result;
  }

  void dump (const Signature& fSignature) {
    cout << "------ " << fSignature.name << " ------" << endl
	 << " observed: " << fSignature.observed << endl
	 << " background DD: " << fSignature.backgroundDD << "+-" << fSignature.sigmaBackgroundDD
	 << " background MC: " << fSignature.backgroundMC << "+-" << fSignature.sigmaBackgroundMC
	 << " sigma bkg MC Jes/Pdf: " << fSignature.sigmaBackgroundJes << '/' << fSignature.sigmaBackgroundPdf
	 << endl
	 << " yield: " << fSignature.yield
	 << " sigma yield lumi/stat/jes/pdf/trig: " << fSignature.sigmaLumi << '/' << fSignature.sigmaYieldStat << '/' << fSignature.sigmaYieldJes << '/' << fSignature.sigmaYieldPdf << '/' << fSignature.sigmaTrigger
	 << " sigma yield eff mu/e/tau: " << fSignature.sigmaYieldMuon << '/' << fSignature.sigmaYieldElectron << '/' << fSignature.sigmaYieldTau << endl
	 << " sisSig: " << 1./fSignature.sigSig() << ", sigBkgDD: " << 1./fSignature.sigBkgDD() 
	 << " sigObserved: " << fSignature.sigObserved() << endl
	 << " total limit: " << fSignature.quickLimit << endl
	 << " --- " << endl;
  }

  void dump (const Signatures& fSignatures) {
    Signatures sigs (fSignatures);
    // sort (sigs.begin(), sigs.end(), lessByYield);
        sort (sigs.begin(), sigs.end(), lessQuickLimit);
    //sort (sigs.begin(), sigs.end(), lessPull);
    double totYield = sumYield (fSignatures);
    cout << "dump Signatures-> Total yield: " << totYield << endl;
    for (size_t i = 0; i < sigs.size() && i < 10; ++i) {
      dump (sigs[i]);
      cout << "Total yield Limit: " << sigs[i].quickLimit*totYield << endl;
      cout << "Total expec Limit: " << sigs[i].getExpectedLimit()*totYield << endl;
    }
    cout << "dump Signatures-> End" << endl;
  }

  //============ process data files =================
 
  void addDataFile (const string& fName, Signatures* fSignatures) {
    ifstream in (fName.c_str());
    char buffer[1024];
    double lumi = 0;
    double sigmaLumi = 0;
    while (in.getline (buffer, 1024)) {
	vector<string> tokens = tokenize (string(buffer));
	if (tokens.empty()) continue;
	if (tokens[0] == "lumi" && tokens.size() >= 3) {
	  lumi = atof (tokens[1].c_str());
	  sigmaLumi = atof (tokens[2].c_str());
	}
	else if (tokens[0] == "data") {
	  if (tokens.size() != 7) {
	    cerr << "readDataFile-> ERROR expect 7 fields, got " <<  tokens.size() << ": " << buffer << endl;
	    continue;
	  }
	  Signature sig;
	  sig.name = tokens[1];
	  sig.observed = int (atof (tokens[2].c_str()));
	  sig.yield = lumi;
	  sig.sigmaLumi = sigmaLumi;
	  sig.backgroundMC = atof (tokens[3].c_str());
	  sig.sigmaBackgroundMC = atof(tokens[4].c_str());
	  if (sig.sigmaBackgroundMC > 0 && sig.backgroundMC < 0.5*sig.sigmaBackgroundMC) {
	    cout << "addDataFile-> " << sig.name << ':' << " brute force bkgMC " << sig.backgroundMC << "+-" << sig.sigmaBackgroundMC;
	    sig.backgroundMC = 0.5*sig.sigmaBackgroundMC;
	    sig.sigmaBackgroundMC = 2.;
	    cout << " to " << sig.backgroundMC << "+-" << sig.sigmaBackgroundMC << endl;
	  }
	  else if (sig.backgroundMC > 0) sig.sigmaBackgroundMC /= sig.backgroundMC;
	  else sig.sigmaBackgroundMC = 0;

	  sig.backgroundDD = atof (tokens[5].c_str()); 
	  sig.sigmaBackgroundDD = atof (tokens[6].c_str());
	  if (sig.sigmaBackgroundDD > 0 && sig.backgroundDD <= 0.5*sig.sigmaBackgroundDD) {
	    cout << "addDataFile-> " << sig.name << ':' << " brute force bkgDD " << sig.backgroundDD << "+-" << sig.sigmaBackgroundDD;
	    sig.backgroundDD = 0.5*sig.sigmaBackgroundDD;
	    sig.sigmaBackgroundDD = 2.;
	    cout << " to " << sig.backgroundDD << "+-" << sig.sigmaBackgroundDD << endl;
	  }
	  else if (sig.backgroundDD > 0) sig.sigmaBackgroundDD /= sig.backgroundDD;
	  else sig.sigmaBackgroundDD = 0;

	  fSignatures->push_back (sig);
	}
    }
  }

  bool readMCFiles (const string& fFile, int fM0, int fM12, Signatures* fSignatures, double fScale) {
    vector<size_t> cleanup;
    for (size_t i = 0; i < fSignatures->size(); ++i) {
      Signature* sig = &((*fSignatures)[i]);
      if (!readRichardMCFile (fFile, fM0, fM12, sig, fScale)) {
	cerr << "readRUMCFiles-> Worning can not find data for signature " <<  sig->name << " in " << fM0 << ':' << fM12 << endl;
	cleanup.push_back(i);
      }
    }
    // cleanup undefined channels
    int i = cleanup.size();
    while (--i >= 0) {
      cerr << "readRUMCFiles-> removing channel " << (*fSignatures)[cleanup[i]].name << endl;
      fSignatures->erase (fSignatures->begin() +  cleanup[i]);
    }
    return true;
  }

  bool readRichardMCFile (const string& fName, int fM0, int fM12, Signature* fSignature, double fScale) {
    // constants
    double jesSigma = 0.10;
    double pdfSigma = 0.14;
    double trigSigma = 0.05;

    char buffer[1024];
    Signature* sig = fSignature;
    const string flavor = sig->name;
    ifstream in (fName.c_str());
    while (in.getline (buffer, 1024)) {
      vector<string> tokens = tokenize (string(buffer));
      if (tokens.size() < 4) continue;
      if (tokens[0] != "scan") { // work around bug
	if (tokens[0][0]>='0' && tokens[0][0]<= '9' && tokens[1][0]>='0' && tokens[1][0]<= '9') {
	  tokens.resize(tokens.size()+ 2);
	  int i = tokens.size() - 2;
	  while (--i >= 0) {
	    tokens[i+2] = tokens[i];
	  }
	  tokens[1] = "charginoneutralino";
	  tokens[0] = "scan";
	}
	else continue;
      }
      if ((tokens[1] != "m0m12" && 
	   tokens[1] != "charginogluino" && 
	   tokens[1] != "charginoneutralino" && 
	   tokens[1] != "mCHmLSP") 
	  || int(atof (tokens[2].c_str())) != fM0 
	  || int(atof (tokens[3].c_str())) != fM12) 
	continue;

      if (tokens.size() == 13 && (tokens[4] == sig->name || ruChannel (tokens[4]) == sig->name)) {
	//  0    1    2  3   4           5          6                      7        8         9         10       11         12     
      	// scan m0m12 m0 m12 ChannelName Efficiency Efficiency_total_error stat_err MuEff_err ElEff_err TEff_err TauEff_err Trigger_err

	double yield = atof (tokens[5].c_str());
	double sigmaYield = atof (tokens[6].c_str());
	if (yield <= 0 && sigmaYield > 0) {
	  yield = sigmaYield / 2;
	  cout << "readRichardMCFile-> " << sig->name << ": brute force MC yield to " <<  yield << endl;
	}
	sig->yield *= yield;
	if (yield <= 0) yield = 1; // to avoid nan
	double sigmaStat = atof (tokens[7].c_str());
	sig->sigmaYieldStat = sigmaStat / yield;
	sig->sigmaYieldElectron = atof (tokens[9].c_str()) / yield;
	sig->sigmaYieldMuon = atof (tokens[8].c_str()) / yield;
	sig->sigmaYieldTau = atof (tokens[11].c_str()) / yield;
	//	sig->sigmaYieldTrack = atof (tokens[10].c_str()) / yield;
	sig->sigmaYieldJes = jesSigma;
	sig->sigmaYieldPdf = pdfSigma;
	sig->sigmaBackgroundJes = jesSigma;
	sig->sigmaBackgroundPdf = pdfSigma;
	sig->sigmaTrigger = trigSigma;
	sig->yield *= fScale;

	double bkg = sig->backgroundDD + sig->backgroundMC;
	double dbkg = sqrt (sig->sigmaBackgroundDD*sig->sigmaBackgroundDD + 
			    sig->sigmaBackgroundMC*sig->sigmaBackgroundMC);
	double dscale = sqrt(sig->sigmaLumi*sig->sigmaLumi +
			     sig->sigmaYieldStat*sig->sigmaYieldStat +
			     sig->sigmaYieldJes*sig->sigmaYieldJes +
			     sig->sigmaYieldPdf*sig->sigmaYieldPdf +
			     sig->sigmaTrigger*sig->sigmaTrigger +
			     sig->sigmaYieldMuon*sig->sigmaYieldMuon +
			     sig->sigmaYieldElectron*sig->sigmaYieldElectron +
			     sig->sigmaYieldTau*sig->sigmaYieldTau);
	sig->quickLimit = sig->getQuickLimit ();
	
	return true;
      }
    }
    return false;
  }

  double totalXSection (const std::string& fName, int fM0, int fM12) {
    char buffer[1024];
    ifstream in (fName.c_str());
    if (!in) {
      cerr << "totalXSection-> Failed to find file " << fName << endl;
    return 0;
   }
    while (in.getline (buffer, 1024)) {
      vector<string> tokens = tokenize (string(buffer));
      if (tokens.size() < 6) continue;
      if (tokens[0] == "scan" && 
	  int(atof (tokens[2].c_str())) == fM0 && 
	  int(atof (tokens[3].c_str())) == fM12 &&
	  (tokens[4] == "NLOXSEC" || tokens[4] == "LOXSEC")) {
	double result = atof (tokens[5].c_str());
	return result;
      }
    }
    cerr << "totalXSection-> Failed to find xSection in file " << fName 
	 << " for the point " << fM0 << ':' << fM12 << endl;
    return 0;
  }

  std::vector<std::pair<int, int> > allMCPoints (const std::string& fName) {
    set <pair<int, int> > result;
    char buffer[1024];
    ifstream in (fName.c_str());
    while (in.getline (buffer, 1024)) {
      vector<string> tokens = tokenize (string(buffer));
      if (tokens.size() < 4) continue;
      if (tokens[0] != "scan") continue;
      pair<int,int> point (int(atof (tokens[2].c_str())),  int(atof (tokens[3].c_str())));
      result.insert (point);
    }
    return vector<pair<int, int> > (result.begin(), result.end());
}

  void convertChannels (const Signatures& fSignatures, StatModelChannels& fStatChannels, bool normilizeYields) {
    Signatures tmpSigs (fSignatures);
//     cout << "--------------------------------------" << endl;
//     cout << "first 5 signal significant channels" << endl;
//     sort (tmpSigs.begin(), tmpSigs.end(), lessSigSignificance);
//     for (size_t i = 0; i <  tmpSigs.size() && i < 5; ++i) dump(tmpSigs[i]);
//     cout << "--------------------------------------" << endl;
//     cout << "first 5 DD background significant channels" << endl;
//     sort (tmpSigs.begin(), tmpSigs.end(), lessDDBkgSignificance);
//     for (size_t i = 0; i <  tmpSigs.size() && i < 5; ++i) dump(tmpSigs[i]);
//     cout << "--------------------------------------" << endl;
    Signatures cleanSigs;
    for (size_t i = 0; i < fSignatures.size(); ++i) {
      const Signature& sig = fSignatures[i];
//       if (sig.sigmaYieldStat > 1) { 
// 	cout << "convertChannels-> ignore channel with unsignificant signal yield: " << sig.name << endl;
// 	continue;
//       }
//       if (sig.yield < sig.backgroundDD * sig.sigmaBackgroundDD) {
// // 	cout << "convertChannels-> ignore channel with signal yield insignificant comparing to DD background: " << sig.name << endl;
// // 	continue;
//       }
//       if (sig.yield < sig.backgroundMC * sig.sigmaBackgroundMC) {
// 	cout << "convertChannels-> ignore channel with signal yield insignificant comparing to MC background: " << sig.name << endl;
// 	continue;
//       }

      cleanSigs.push_back (sig);
    }
    
    int nChannels = cleanSigs.size();
    fStatChannels = StatModelChannels (nChannels);
    double sumYields = 0;
    for (int iChannel = 0; iChannel < nChannels; ++iChannel) {
      sumYields += cleanSigs[iChannel].yield;
    }
    
    for (int iChannel = 0; iChannel < nChannels; ++iChannel) {
      const Signature& sig = cleanSigs[iChannel];
      //dump(sig);
      StatModelChannel& sch = fStatChannels[iChannel];
      sch.name = sig.name;
      sch.observed = sig.observed;
      sch.backgroundDD = sig.backgroundDD;
      sch.backgroundMC = sig.backgroundMC;
      sch.sigmaBackgroundDD = sig.sigmaBackgroundDD;
      sch.sigmaBackgroundMC = sig.sigmaBackgroundMC;
      sch.sigmaBackgroundMCLumiJesTrigPdf = sqrt (sig.sigmaLumi*sig.sigmaLumi+
						sig.sigmaBackgroundJes*sig.sigmaBackgroundJes+
						sig.sigmaBackgroundPdf*sig.sigmaBackgroundPdf+
						sig.sigmaTrigger*sig.sigmaTrigger); 
      sch.yield = normilizeYields ? sig.yield / sumYields : sig.yield;
      sch.sigmaYieldStat = sig.sigmaYieldStat;
      sch.sigmaYieldLumiJesTrigPdf = sqrt (sig.sigmaLumi*sig.sigmaLumi+
					   sig.sigmaYieldJes*sig.sigmaYieldJes+
					   sig.sigmaYieldPdf*sig.sigmaYieldPdf+
					   sig.sigmaTrigger*sig.sigmaTrigger);
      sch.sigmaYieldElectron = sig.sigmaYieldElectron;
      sch.sigmaYieldMuon = sig.sigmaYieldMuon;
      sch.sigmaYieldTau= sig.sigmaYieldTau;
    }
  }

  void dumpCombined (const Signatures& fSignatures, const std::string& fFile, const std::string& fTitle, bool normilizeYields, int fChannels) {
    Signatures sig_copy (fSignatures); // local copy
    sort (sig_copy.begin(), sig_copy.end(), lessExpectedLimit);
    StatModelChannels statChannels;
    convertChannels (sig_copy, statChannels, normilizeYields);
    int nChannels = statChannels.size();
    if (fChannels > 0 && fChannels < nChannels) nChannels = fChannels;
    // produce configuration in HIGGS combination format
    FILE* cfgFile = fopen (fFile.c_str(), "w");
    fprintf (cfgFile,"# %s\n", fTitle.c_str());
    fprintf (cfgFile,"%-20s", "# channels"); 
    for (int i=0;i<nChannels;++i) fprintf(cfgFile, "%30s",statChannels[i].name.c_str()); fprintf(cfgFile, "\n");
    
    fprintf (cfgFile,"imax %d number of channels\n", nChannels);
    fprintf (cfgFile,"jmax %d number of background\n", 2);
    fprintf (cfgFile,"kmax %d number of nuisance parameters\n", 7);

    fprintf (cfgFile,"%-20s", "observation"); 
    for (int i=0;i<nChannels;++i) fprintf(cfgFile, "%10d", statChannels[i].observed); fprintf(cfgFile, "\n");

    fprintf (cfgFile,"%-20s", "bin"); 
    for (int i=0;i<nChannels;++i) fprintf(cfgFile, "%10d%10d%10d", i+1, i+1, i+1); fprintf(cfgFile, "\n");
    
    fprintf (cfgFile,"%-20s", "process"); 
    for (int i=0;i<nChannels;++i) fprintf(cfgFile, "%10s%10s%10s", "susy", "bkgDD", "bkgMC"); fprintf(cfgFile, "\n");
    
    fprintf (cfgFile,"%-20s", "process"); 
    for (int i=0;i<nChannels;++i) fprintf(cfgFile, "%10d%10d%10d", 0, 1, 2); fprintf(cfgFile, "\n");
    
    fprintf (cfgFile,"%-20s", "rate"); 
    for (int i=0;i<nChannels;++i) fprintf(cfgFile, "%10.3e%10.3e%10.3e", 
					  statChannels[i].yield, 
					  statChannels[i].backgroundDD, 
					  statChannels[i].backgroundMC); fprintf(cfgFile, "\n");
    // for (int i=0;i<nChannels;++i) cout << statChannels[i].name << " \t" << statChannels[i].yield << endl;

    fprintf (cfgFile,"%-10s%10s", "LuJeTriPd", "lnN"); 
    for (int i=0;i<nChannels;++i) fprintf(cfgFile, "%10.3f%10.3f%10.3f", 
					  1.+(statChannels[i].sigmaYieldLumiJesTrigPdf),
					  1., 
					  1.+(statChannels[i].sigmaBackgroundMCLumiJesTrigPdf)); fprintf(cfgFile, "\n");
    
    fprintf (cfgFile,"%-10s%10s", "SigMCStat", "lnN"); 
    for (int i=0;i<nChannels;++i) fprintf(cfgFile, "%10.3f%10.3f%10.3f", 
					  1.+(statChannels[i].sigmaYieldStat),
					  1.,1.); fprintf(cfgFile, "\n");

    
    fprintf (cfgFile,"%-10s%10s", "BkgMCStat", "lnN"); 
    for (int i=0;i<nChannels;++i) fprintf(cfgFile, "%10.3f%10.3f%10.3f", 
					  1.,1.,
					  1.+(statChannels[i].sigmaBackgroundMC)); fprintf(cfgFile, "\n");
    
    fprintf (cfgFile,"%-10s%10s", "BkgDD", "lnN"); 
    for (int i=0;i<nChannels;++i) fprintf(cfgFile, "%10.3f%10.3f%10.3f",
					  1., 
					  1.+(statChannels[i].sigmaBackgroundDD),
					  1.); fprintf(cfgFile, "\n");
    
    fprintf (cfgFile,"%-10s%10s", "muEff", "lnN"); 
    for (int i=0;i<nChannels;++i) fprintf(cfgFile, "%10.3f%10.3f%10.3f",
					  1.+(statChannels[i].sigmaYieldMuon),
					  1., 1.); fprintf(cfgFile, "\n");
    
    fprintf (cfgFile,"%-10s%10s", "eEff", "lnN"); 
    for (int i=0;i<nChannels;++i) fprintf(cfgFile, "%10.3f%10.3f%10.3f",
					  1.+(statChannels[i].sigmaYieldElectron),
					  1., 1.); fprintf(cfgFile, "\n");
    
    fprintf (cfgFile,"%-10s%10s", "tauEff", "lnN"); 
    for (int i=0;i<nChannels;++i) fprintf(cfgFile, "%10.3f%10.3f%10.3f",
					  1.+(statChannels[i].sigmaYieldTau),
					  1., 1.); fprintf(cfgFile,"\n");
    
    fclose (cfgFile);
  }



} // namespace

using namespace ra7StatConverter;

void runAll () {
  using namespace ra7StatConverter;
  Signatures sigs;
  addDataFile ("ra7_2011_data.txt", &sigs);
  readMCFiles ("ra7_2011_msugra3.txt", 180, 240, &sigs);
  sort (sigs.begin(), sigs.end(), lessByYield);
  //dump (sigs);
  dumpCombined (sigs, "ra7_combined_model.txt", "ra7_combined_model CMSSM 180:240:3", false);
}

string runStatConverter (const string& datadir, int m0, int m12, int maxChannels = 0) {
  Signatures sigs;
  //  addDataFile (datadir + "/data_outfile.txt", &sigs);
  //  addDataFile (datadir + "/data_outfile_RA7_2.1ifb.txt", &sigs);
  addDataFile (datadir + "/data.txt", &sigs);
  string mcDataDir = datadir + "/output";
  string mcDataFile = getFile (mcDataDir, m0, m12);
  if (mcDataFile.empty()) {
    cout << "Can not find MC data for point " << m0 << ':' << m12 << " in dir " << mcDataDir << endl;
    return "";
  }
  readMCFiles (mcDataFile, m0, m12, &sigs);
  char buffer [1024];
  sprintf (buffer, "ra7_%d_%d_combinedModel.txt", m0, m12);
  string cardFileName (buffer);
  sprintf (buffer, "ra7_combined_model %s CMSSM %d:%d", datadir.c_str(), m0, m12);
  dump (sigs);
  dumpCombined (sigs, cardFileName, buffer, true, maxChannels);
  return cardFileName;
}

string simpleStatConverter (const string& name, int observed, double background, 
			    double dBackground, double dScale) {
  bool bkgError = dBackground > 0;
  bool scaleError = dScale > 0;
  int nuisances = 0;
  if (bkgError) ++nuisances;
  if (scaleError) ++nuisances;
  FILE* cfgFile = fopen (name.c_str(), "w");
  fprintf (cfgFile,"# %s\n", "simpleStatConverter");
  fprintf (cfgFile,"imax %d number of channels\n", 1);
  fprintf (cfgFile,"jmax %d number of background\n", 1);
  fprintf (cfgFile,"kmax %d number of nuisance parameters\n", nuisances);
  fprintf (cfgFile,"%-20s%10d\n", "observation", observed); 
  fprintf (cfgFile,"%-20s%10d%10d\n", "bin", 1, 1); 
  fprintf (cfgFile,"%-20s%10s%10s\n", "process", "sig", "bkg");
  fprintf (cfgFile,"%-20s%10.3e%10.3e\n", "rate", 1., background); 
  if (bkgError) {
    fprintf (cfgFile,"%-10s%10s%10.3f%10.3f\n", "dBkg", "lnN", 1., 1.+(dBackground/background));
  }
  if (scaleError) {
    fprintf (cfgFile,"%-10s%10s%10.3f%10.3f\n", "dScale", "lnN", 1.+(dScale), 1.);
  }
  fclose (cfgFile);
  return name;
}

void dumpYields (const string& datadir, int m0, int m12) {
  Signatures sigs;
  addDataFile (datadir + "/data.txt", &sigs);
  string mcDataDir = datadir + "/output";
  string mcDataFile = getFile (mcDataDir, m0, m12);
  if (mcDataFile.empty()) {
    cout << "Can not find MC data for point " << m0 << ':' << m12 << " in dir " << mcDataDir << endl;
    return;
  }
  readMCFiles (mcDataFile, m0, m12, &sigs);
  sort (sigs.begin(), sigs.end(), lessByYield);
  reverse (sigs.begin(), sigs.end());
  cout << datadir <<", masses " <<  m0 << ':' << m12 << endl;
  for (size_t i = 0; i < sigs.size(); ++i) {
    cout << sigs[i].name << ": " << sigs[i].yield/4670. << endl;
  }
}
