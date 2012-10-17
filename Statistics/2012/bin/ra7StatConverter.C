//
// F. Ratnikov, KIT, Sep. 2012 (fedor.ratnikov@cern.ch)
// 
#include "ra7StatConverter.h"

#include <dirent.h>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <time.h>
#include <stdio.h>

#include <set>
#include <algorithm>

#include "Math/ProbFuncMathCore.h"


using namespace std;

namespace {

  vector<string> tokenize (const string& fInput) {
    vector<string> result;
    if (!fInput.empty() && fInput[0] != '#') {
      string buf; 
      stringstream ss (fInput);
      while (ss >> buf) result.push_back(buf);
    }
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

bool validChannel (int ich) 
{
  return 
    (ich >= 0 && ich < 60) ||
    (ich >= 75 && ich < 105) ||
    (ich >= 120 && ich < 150) ||
    (ich >= 165 && ich < 180) ||
    (ich >=181 && ich <= 182) ||
    (ich >=500 && ich <= 504)
    ;
}

string channelName (int i)
{
  char buffer [1024] = "UNUSED";
  if (i<180) 
    {
      int index = i;
      int met = index % 5;
      index = (index - met) / 5;
      int mt = index % 3;
      index = (index - mt) / 3;
      int mll = index % 3;
      index = (index - mll) / 3;
      int category = index % 4;
      
      const char* cmet [] = {"0-50", "50-100", "100-150", "150-200", "200-inf"};
      const char* cmt [] = {"0-120", "120-160", "160-inf"};
      const char* cmll [] = {"belowZ", "inZ", "aboveZ"};
      const char* ccat [] = {"OSSF", "OSOF", "SS1tau", "OSOF1tau"};
      if (validChannel(i))
	{
	  sprintf (buffer, "ch%d:3L_%s_%s_MT:%s_MET:%s", i, ccat[category], cmll[mll], cmt[mt], cmet[met]);
	}
    }
  else if (i == 181)
    {
      sprintf(buffer,"ch%d:SS_HT0MET200lV", i);
    }
  else if (i == 182)
    {
      sprintf (buffer, "ch%d:SS_HT0MET120NJ2bVlV", i);
    }
  else if (i >= 500 && i <= 504)
    {
      const char* cben [] = {"2L2J_MET:80-100","2L2J_MET:100-120","2L2J_MET:120-150","2L2J_MET:150-200","2L2J_MET:200-inf"};
      sprintf (buffer, "ch%d:%s", i, cben[i-500]);
    }
  return string(buffer);
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
    limit = sqrt (limit*limit + dbkg*dbkg) * sqrt (1.+dscale*dscale);
    return limit;
  }
}

namespace ra7StatConverter {


  bool lessQuickLimit (const ra7StatConverter::Signature& a, const ra7StatConverter::Signature& b) {
    return a.quickLimit < b.quickLimit;
  }
  bool lessExpectedLimit (const ra7StatConverter::Signature& a, const ra7StatConverter::Signature& b) {
    return a.getExpectedLimit() < b.getExpectedLimit();
  }

  double Signature::getQuickLimit () const {
    if (yield <= 0) return 9999;
    double bkg = background;
    double dbkg = sigmaBackground ();
    double dscale = sigmaYield ();
    return quickLimitCalculator (observed, bkg, dbkg, dscale)/yield; 
  }

  double Signature::getExpectedLimit () const {
    if (yield <= 0) return 9999;
    double bkg = background;
    double dbkg = sigmaBackground ();
    double dscale = sigmaYield ();
    int nobserved = int (floor (bkg));
    double limit1 = quickLimitCalculator (nobserved, bkg, dbkg, dscale)/yield; 
    double limit2 = quickLimitCalculator (nobserved+1, bkg, dbkg, dscale)/yield;
    return limit1 + (bkg - nobserved)*(limit2 - limit1);
  }

  double Signature::sigmaBackground () const {
    return sqrt (sigmaBackgroundUncorrelated*sigmaBackgroundUncorrelated +
		 sigmaBackgroundWZ * sigmaBackgroundWZ +
		 sigmaBackgroundDD * sigmaBackgroundDD +
		 sigmaBackgroundZGamma * sigmaBackgroundZGamma +
		 sigmaBackgroundZZ * sigmaBackgroundZZ +
		 sigmaBackgroundRare * sigmaBackgroundRare +
		 sigmaBackgroundJes * sigmaBackgroundJes
		 );
  }

  double Signature::sigmaYield () const {
    return sqrt(sigmaLumi*sigmaLumi +
		sigmaYieldUncorrelated * sigmaYieldUncorrelated +
		sigmaYieldMuon * sigmaYieldMuon +
		sigmaYieldElectron * sigmaYieldElectron +
		sigmaYieldTau * sigmaYieldTau +
		sigmaYieldTrigger * sigmaYieldTrigger +
		sigmaYieldJes * sigmaYieldJes
		);
  }

  double sumYield (const Signatures& fSignatures, int fLimit) {
    double result = 0;
    int nChannels = fSignatures.size();
    if (fLimit > 0 && nChannels > fLimit) nChannels = fLimit;
    for (size_t i = 0; i < nChannels; ++i) {
      result += fSignatures[i].yield;
      //      cout << "sumYield->"<<i<<':'<<fSignatures[i].id<<" yield: "<<fSignatures[i].yield<<':'<<result<<endl;
    }
    return result;
  }

  int sumObserved (const Signatures& fSignatures) {
    int result = 0;
    for (size_t i = 0; i < fSignatures.size(); ++i) result += fSignatures[i].observed;
    return result;
  }

  double sumBackgrounds (const Signatures& fSignatures) {
    double result = 0;
    for (size_t i = 0; i < fSignatures.size(); ++i) result += (fSignatures[i].background);
    return result;
  }

  void dump (const Signature& fSignature) {
    cout << "------ " << fSignature.id << " " << fSignature.name << " ------" 
	 << endl
	 << " observed: " << fSignature.observed 
	 << endl
	 << " background: " << fSignature.background << "+-" << fSignature.sigmaBackground()
	 << " uncor/WZ/DD/ZG/ZZ/Rare/JES: " 
	 << fSignature.sigmaBackgroundUncorrelated << '/' << fSignature.sigmaBackgroundWZ << '/'
	 << fSignature.sigmaBackgroundDD << '/' << fSignature.sigmaBackgroundZGamma << '/'
	 << fSignature.sigmaBackgroundZZ << '/' << fSignature.sigmaBackgroundRare << '/'
	 << fSignature.sigmaBackgroundJes
	 << endl
	 << " yield: " << fSignature.yield << "+-" << fSignature.sigmaYield ()
	 << " uncor/lumi/mu/el/tau/trig/jes/theory: "
	 << fSignature.sigmaYieldUncorrelated << '/' << fSignature.sigmaLumi << '/'
	 << fSignature.sigmaYieldMuon << '/' << fSignature.sigmaYieldElectron << '/'
	 << fSignature.sigmaYieldTau << '/' << fSignature.sigmaYieldTrigger << '/'
	 << fSignature.sigmaYieldJes << '/' << fSignature.sigmaYieldTheory
	 << endl
	 << " quick limit: " << fSignature.quickLimit << endl
	 << " --- " << endl;
  }
  
  void dump (const Signatures& fSignatures, int fLimit) {
    Signatures sigs (fSignatures);
    double totYield = sumYield (fSignatures);
    double thisYield = sumYield (fSignatures, fLimit);
    cout << "dump Signatures-> Total yield: " << totYield << endl;
    cout << "dump Signatures-> Top " <<  fLimit << " channels yield: " << thisYield << endl;
    for (size_t i = 0; i < sigs.size() && i < fLimit; ++i) {
      dump (sigs[i]);
      cout << i << " -> total yield Limit: " << sigs[i].quickLimit*thisYield << endl;
    }
    cout << "dump Signatures-> End" << endl;
  }

  //============ process data files =================
 
  void addDataFiles (const string& fMegaName, Signatures* fSignatures) {
    char buffer[1024];
    double lumi = 0;
    double sigmaLumi = 0;
    vector <vector <string> > dataCards;
    vector <vector <string> > lumiCards;
    vector <string> inputFiles;
    ifstream in (fMegaName.c_str());
    while (in.getline (buffer, 1024)) {
      if (buffer[0] == 'f' && buffer[1] == 'i' && buffer[2] == 'l' && buffer[3] == 'e') {
	vector<string> tokens = tokenize (string(buffer));
	if (tokens.size() >= 2) inputFiles.push_back (tokens[1]);
	cout << "Add data file: " << tokens[1] << endl;
      }
    }

    for (size_t ifile = 0; ifile < inputFiles.size(); ++ifile) {
      ifstream in (inputFiles[ifile].c_str());
      if (!in) {
	cerr << "addDataFiles-> Cannot find file: " << inputFiles[ifile] << " FATAL" << endl;
	return;
      }
      while (in.getline (buffer, 1024)) {
	if (buffer[0] == 'd' && buffer[1] == 'a' && buffer[2] == 't' && buffer[3] == 'a') {
	  dataCards.push_back (tokenize (string(buffer)));
	}
	else if (buffer[0] == 'l' && buffer[1] == 'u' && buffer[2] == 'm' && buffer[3] == 'i') {
	  lumiCards.push_back (tokenize (string(buffer)));
	}
      }
    }
    cout << "found channels: "<<dataCards.size()<<" lumi: "<<lumiCards.size()<<endl;

    // process "lumi"
    for (size_t ilumi = 0; ilumi < lumiCards.size(); ++ilumi) {
      const vector<string>& tokens = lumiCards[ilumi];
      if (tokens.size() < 3) {
	cout << "lumi card: expected 3 fiels, got " << tokens.size() << endl;
	for (size_t j = 0; j < tokens.size(); ++j) cout << tokens[j] << ' ';
	cout << endl;
      }
      else {
	double thisLumi = atof (tokens[1].c_str());
	double thisDLumi = atof (tokens[2].c_str());
	if (lumi > 0) {
	  double tolerance = 1e-2;
	  if (2*fabs(thisLumi-lumi)/(thisLumi+lumi) > tolerance ||
	      2*fabs(thisDLumi-sigmaLumi)/(thisDLumi+sigmaLumi) > tolerance) {
	    cerr << "addDataFiles-> ERROR inconsistent LUMI definition" 
		 << " old: " << lumi << "+-" << sigmaLumi
		 << " new: " << thisLumi << "+-" << thisDLumi
		 << " Ignore new" << endl;
	  }
	}
	else {
	  lumi = thisLumi;
	  sigmaLumi = thisDLumi;
	}
      }
    }

    // process "data"
    for (size_t idata = 0; idata < dataCards.size(); ++idata) {
      const vector<string>& tokens = dataCards[idata];
      if (tokens.size() != 16 && tokens.size() != 21) {
	cerr << "readDataFile-> ERROR expect 16 or 21 fields, got " <<  tokens.size() << ": ";
	for (size_t i = 0; i < tokens.size(); ++i) cerr << tokens[i] << ' ';
	cerr << endl;
	continue;
      }
      bool newFormat = tokens.size() == 21;
      // check no duplication
      int id = atoi (tokens[1].c_str());
      bool matched = false;
      for (int i = 0; i < fSignatures->size(); ++i) {
	if (id == (*fSignatures)[i].id) {
	  cerr << "readDataFile-> ERROR id " << id << " is defined already. Inore new" << endl;
	  matched = true;
	  break;
	}
      }
      if (matched) continue;
      
      Signature sig;
      
      sig.id = int (atof (tokens[1].c_str()));
      sig.name = channelName (sig.id);
      sig.observed = int (atof (tokens[2].c_str()));
      double totalBackground = atof (tokens[3].c_str());
      double sigmatotalBackground = atof (tokens[4].c_str());
      sig.sigmaBackgroundUncorrelated = atof (tokens[5].c_str());
      if (newFormat) {
	// card format:
	// data <channel ID> <observed> <total background> 
	// <total bkg stat> <total bkg syst> 
	// <wz> <wz stat> <wz syst> <ttbar+fakes> <ttbar+fakes stat> <ttbar+fakes syst> 
	// <zgamma> <zgamma stat> <zgamma syst> <zz> <z stat> <z syst> <rare> <rare stat> <rare syst>
	double bkgAll = 0;
	double bkgStat2 = 0;
	
	bkgAll += atof (tokens[6].c_str());
	sig.sigmaBackgroundWZ = atof (tokens[7].c_str());
	bkgStat2 += pow (atof (tokens[8].c_str()), 2);

	bkgAll += atof (tokens[9].c_str());
	sig.sigmaBackgroundDD = atof (tokens[10].c_str());
	bkgStat2 += pow (atof (tokens[11].c_str()), 2);


	bkgAll += atof (tokens[12].c_str());
	sig.sigmaBackgroundZGamma = atof (tokens[13].c_str());
	bkgStat2 += pow (atof (tokens[14].c_str()), 2);


	bkgAll += atof (tokens[15].c_str());
	sig.sigmaBackgroundZZ = atof (tokens[16].c_str());
	bkgStat2 += pow (atof (tokens[17].c_str()), 2);


	bkgAll += atof (tokens[18].c_str());
	sig.sigmaBackgroundRare = atof (tokens[19].c_str());
	bkgStat2 += pow (atof (tokens[20].c_str()), 2);

	sig.sigmaBackgroundJes = 0;

	sig.background = bkgAll;
	sig.sigmaBackgroundUncorrelated = sqrt (bkgStat2);
      }
      else { // old format
	// card format:
	// data <channel ID> <observed> <total background> 
	// <total bkg uncertainty> <uncorrelated bkg uncertainty> 
	// <wz> <wz uncertainty> <ttbar+fakes> 
	// <ttbar+fakes uncertainty> <zgamma> <zgamma uncertainty> <zz> <zz uncertainty><rare> 
	// <rare uncertainty>
	sig.background = atof (tokens[6].c_str());
	sig.sigmaBackgroundWZ = atof (tokens[7].c_str());
	sig.background += atof (tokens[8].c_str());
	sig.sigmaBackgroundDD = atof (tokens[9].c_str());
	sig.background += atof (tokens[10].c_str());
	sig.sigmaBackgroundZGamma = atof (tokens[11].c_str());
	sig.background += atof (tokens[12].c_str());
	sig.sigmaBackgroundZZ = atof (tokens[13].c_str());
	sig.background += atof (tokens[14].c_str());
	sig.sigmaBackgroundRare = atof (tokens[15].c_str());
	sig.sigmaBackgroundJes = 0;
       }
      
      if (sig.background <= 0) { 
	sig.background = totalBackground;
	sig.sigmaBackgroundUncorrelated = sigmatotalBackground;
      }
      
      sig.yield = lumi;
      sig.sigmaLumi = lumi > 0 ? sigmaLumi / lumi : 0.;
      
      fSignatures->push_back (sig);
    }
  }
  
  bool readScanFiles (const string& fMegaName, int fM1, int fM2, Signatures* fSignatures, double fScale) {
    vector<vector<string> > yieldSpec;
    vector<vector<string> > xsecSpec;
    char buffer[1024];
    vector <string> inputFiles;
    ifstream in (fMegaName.c_str());
    while (in.getline (buffer, 1024)) {
      if (buffer[0] == 'd' && buffer[1] == 'i' && buffer[2] == 'r') {
	vector<string> tokens = tokenize (string(buffer));
	if (tokens.size() >= 2) {
	  string fileName = getFile (tokens[1], fM1, fM2);
	  if (!fileName.empty()) {
	    inputFiles.push_back (fileName);
	    cout << "Add signal file: " << fileName << endl;
	  }
	  else {
	    cerr << "Can not find MC data for point " << fM1 << ':' << fM2 << " in dir " << tokens[1] << " FATAL" << endl;
	    return false;
	  }
	}
      }
    }
    for (int ifile = 0; ifile < inputFiles.size(); ++ifile) {
      ifstream in (inputFiles[ifile].c_str());
      while (in.getline (buffer, 1024)) {
	if (buffer[0] == 's' && buffer[1] == 'c' && buffer[2] == 'a' && buffer[3] == 'n') {
	  yieldSpec.push_back (tokenize (string(buffer)));
	}
	else if (buffer[0] == 'x' && buffer[1] == 's' && buffer[2] == 'e' && buffer[3] == 'c') {
	  xsecSpec.push_back (tokenize (string(buffer)));
	}
      }
    }

    // process xsec
    double xsec = 0;
    for (size_t ixsec = 0; ixsec < xsecSpec.size(); ++ixsec) {
      const vector<string>& tokens = xsecSpec[ixsec];
      if (tokens.size() < 4) {
	cout << "xsec card: expected 4 fiels, got " << tokens.size() << endl;
	for (size_t j = 0; j < tokens.size(); ++j) cout << tokens[j] << ' ';
	cout << endl;
      }
      else {
	int m1 = atoi (tokens[1].c_str());
	int m2 = atoi (tokens[2].c_str());
	if (m1 == fM1 && m2 == fM2) {
	  double thisXsec = atof (tokens[3].c_str());
	  if (xsec > 0) {
	    double tolerance = 1e-2;
	    if (2*fabs(thisXsec-xsec)/(thisXsec+xsec) > tolerance) {
	      cerr << "readScanFiles-> ERROR inconsistent XSEC definition" 
		   << " old: " << xsec
		   << " new: " << thisXsec
		   << " Ignore new" << endl;
	    }
	  }
	  else {
	    xsec = thisXsec;
	  }
	}
      }
    }

    vector<int> cleanup;
    for (size_t iSig = 0; iSig < fSignatures->size(); ++iSig) {
      Signature* sig = &((*fSignatures)[iSig]);
      bool foundChannel = false;
      for (size_t iSpec = 0; iSpec < yieldSpec.size(); ++iSpec) {
	// scan <m1> <m2> <channel ID> <channel yield in pb> 
	// <total yield uncertainty> <uncorrelated uncertainty> <muon eff uncertainty> <electron eff uncertainty> <tau eff uncertainty> 
	// <trigger eff uncertainty> <JES uncertainty> <theory uncertainties>
	const vector<string>& scanLine = yieldSpec[iSpec];
	if (scanLine.size () < 12) {
	  cerr << "readScanFile:scan-> ERROR expect 13 fields, got " <<  scanLine.size();
	  for (int i = 0; i < scanLine.size (); ++i) cerr << ' ' << scanLine[i];
	  cerr << endl;
	}
	else {
	  int m1 = int (atof (scanLine[1].c_str()));
	  int m2 = int (atof (scanLine[2].c_str()));
	  int id = int (atof (scanLine[3].c_str()));
	  if (m1 != fM1 || m2 != fM2 || id != sig->id) continue;
	  double yield = atof (scanLine[4].c_str());
	  if (yield > 0) {
	    int pietOffset = scanLine.size () == 12 ? 1 : 0;
	    sig->sigmaYieldUncorrelated = atof (scanLine[6-pietOffset].c_str()) / yield;
	    sig->sigmaYieldMuon = atof (scanLine[7-pietOffset].c_str()) / yield;
	    sig->sigmaYieldElectron = atof (scanLine[8-pietOffset].c_str()) / yield;
	    sig->sigmaYieldTau = atof (scanLine[9-pietOffset].c_str()) / yield;
	    sig->sigmaYieldTrigger = atof (scanLine[10-pietOffset].c_str()) / yield;
	    sig->sigmaYieldJes = atof (scanLine[11-pietOffset].c_str()) / yield;
	    sig->sigmaYieldTheory = atof (scanLine[12-pietOffset].c_str()) / yield;
	  }
	  else {
	    sig->sigmaYieldUncorrelated = 0;
	    sig->sigmaYieldMuon = 0;
	    sig->sigmaYieldElectron = 0;
	    sig->sigmaYieldTau = 0;
	    sig->sigmaYieldTrigger = 0;
	    sig->sigmaYieldJes = 0;
	    sig->sigmaYieldTheory = 0;
	  }
	  sig->yield *= yield; // yield in events#
	  sig->quickLimit = sig->getExpectedLimit ();
	  foundChannel = true;
	  break;
	}
      }
      if (!foundChannel) {
	cerr << "readScanFile-> Worning can not find data for signature " <<  sig->id << " in " << fM1 << ':' << fM2 << endl;
	cleanup.push_back(iSig);
      }
    }
    // cleanup undefined channels
    int i = cleanup.size();
    while (--i >= 0) {
      cerr << "readScanFile-> removing channel " << (*fSignatures)[cleanup[i]].name << endl;
      fSignatures->erase (fSignatures->begin() +  cleanup[i]);
    }
    sort (fSignatures->begin(), fSignatures->end(), lessQuickLimit);
    // dump (*fSignatures);
    return true;
  }

  double totalXSection (const std::string& fMegaName, int fM1, int fM2) {
    vector<vector<string> > xsecSpec;
    char buffer[1024];
    vector <string> inputFiles;
    ifstream in (fMegaName.c_str());
    while (in.getline (buffer, 1024)) {
      if (buffer[0] == 'd' && buffer[1] == 'i' && buffer[2] == 'r') {
	vector<string> tokens = tokenize (string(buffer));
	if (tokens.size() >= 2) {
	  string fileName = getFile (tokens[1], fM1, fM2);
	  if (!fileName.empty()) inputFiles.push_back (fileName);
	  else cerr << "Can not find MC data for point " << fM1 << ':' << fM2 << " in dir " << tokens[1] << endl;
	}
      }
    }
    for (int ifile = 0; ifile < inputFiles.size(); ++ifile) {
      ifstream in (inputFiles[ifile].c_str());
      while (in.getline (buffer, 1024)) {
	if (buffer[0] == 'x' && buffer[1] == 's' && buffer[2] == 'e' && buffer[3] == 'c') {
	  xsecSpec.push_back (tokenize (string(buffer)));
	}
      }
    }
    
    // process xsec
    double xsec = 0;
    for (size_t ixsec = 0; ixsec < xsecSpec.size(); ++ixsec) {
      const vector<string>& tokens = xsecSpec[ixsec];
      if (tokens.size() < 4) {
	cout << "xsec card: expected 4 fiels, got " << tokens.size() << endl;
	for (size_t j = 0; j < tokens.size(); ++j) cout << tokens[j] << ' ';
	cout << endl;
      }
      else {
	int m1 = atoi (tokens[1].c_str());
	int m2 = atoi (tokens[2].c_str());
	if (m1 == fM1 && m2 == fM2) {
	  double thisXsec = atof (tokens[3].c_str());
	  if (xsec > 0) {
	    double tolerance = 1e-2;
	    if (2*fabs(thisXsec-xsec)/(thisXsec+xsec) > tolerance) {
	      cerr << "readScanFiles-> ERROR inconsistent XSEC definition" 
		   << " old: " << xsec
		   << " new: " << thisXsec
		   << " Ignore new" << endl;
	    }
	  }
	  else {
	    xsec = thisXsec;
	  }
	}
      }
    }
    return xsec;
  }

  void convertChannels (const Signatures& fSignatures, StatModelChannels& fStatChannels, int fUseNFirstChannels, bool fNormilizeYields) {
    bool CORRELATED_ALL_BKG = getenv ("CORRELATED_ALL_BKG");
    bool UNCORRELATED_ALL_BKG = getenv ("UNCORRELATED_ALL_BKG");

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
    Signatures selectedSigs;
    int useFirstChannels = fUseNFirstChannels > 0 ? fUseNFirstChannels : tmpSigs.size(); 
    for (size_t i = 0; i < useFirstChannels; ++i) {
      const Signature& sig = tmpSigs[i];
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

      selectedSigs.push_back (sig);
    }
    
    int nChannels = selectedSigs.size();
    fStatChannels = StatModelChannels (nChannels);
    double sumYields = 0;
    for (int iChannel = 0; iChannel < nChannels; ++iChannel) {
      sumYields += selectedSigs[iChannel].yield;
    }

    cout << "convertChannels-> sumYields: " << fUseNFirstChannels << ' ' << nChannels << ' ' << sumYields << endl;

    for (int iChannel = 0; iChannel < nChannels; ++iChannel) {
      const Signature& sig = selectedSigs[iChannel];
      //dump(sig);
      StatModelChannel& sch = fStatChannels[iChannel];
      sch.id = sig.id;
      sch.name = sig.name;
      sch.observed = sig.observed;
      sch.background = sig.background > 0 ? sig.background : 0.01;
      sch.yield = fNormilizeYields ? sig.yield / sumYields : sig.yield;
      sch.sigmaBackgroundUncorrelated = sig.sigmaBackgroundUncorrelated / sch.background;
      // check if uncorrelated bkg uncertainty is significant
      const double significanceThreshold = 0.05;
      
      if (sig.sigmaBackgroundUncorrelated < sig.quickLimit * significanceThreshold) {
	//	cout << "convertChannels-> Disregard uncorrelated background uncertainty for channel " << sig.name << endl;
	sch.sigmaBackgroundUncorrelated = 0;
      }

      sch.sigmaBackgroundUncorrelated = sig.sigmaBackgroundUncorrelated / sch.background;
      sch.sigmaBackgroundWZ = sig.sigmaBackgroundWZ / sch.background;
      sch.sigmaBackgroundDD = sig.sigmaBackgroundDD / sch.background;
      sch.sigmaBackgroundZGamma = sig.sigmaBackgroundZGamma / sch.background;
      sch.sigmaBackgroundZZ = sig.sigmaBackgroundZZ / sch.background;
      sch.sigmaBackgroundRare = sig.sigmaBackgroundRare / sch.background;
      sch.sigmaBackgroundJes = sig.sigmaBackgroundJes / sch.background;

      if (CORRELATED_ALL_BKG || UNCORRELATED_ALL_BKG) {
	double sigmaAllBackgrounds = 
	  sch.sigmaBackgroundUncorrelated*sch.sigmaBackgroundUncorrelated +
	  sch.sigmaBackgroundWZ*sch.sigmaBackgroundWZ +
	  sch.sigmaBackgroundDD*sch.sigmaBackgroundDD +
	  sch.sigmaBackgroundZGamma*sch.sigmaBackgroundZGamma +
	  sch.sigmaBackgroundZZ*sch.sigmaBackgroundZZ +
	  sch.sigmaBackgroundRare*sch.sigmaBackgroundRare +
	  sch.sigmaBackgroundJes*sch.sigmaBackgroundJes;
	sigmaAllBackgrounds = sqrt (sigmaAllBackgrounds);
	sch.sigmaBackgroundUncorrelated = 0;
	sch.sigmaBackgroundWZ = 0;
	sch.sigmaBackgroundDD = 0;
	sch.sigmaBackgroundZGamma = 0;
	sch.sigmaBackgroundZZ = 0;
	sch.sigmaBackgroundRare = 0;
	sch.sigmaBackgroundJes = 0;
	if (CORRELATED_ALL_BKG) sch.sigmaBackgroundWZ = sigmaAllBackgrounds;
	else if (UNCORRELATED_ALL_BKG) sch.sigmaBackgroundUncorrelated = sigmaAllBackgrounds;
      }


      sch.sigmaLumi = sig.sigmaLumi;
      // check if uncorrelated yield uncertainty is significant
      double allYieldUncertainties = sqrt (sig.sigmaYieldUncorrelated*sig.sigmaYieldUncorrelated +
					   sig.sigmaYieldElectron*sig.sigmaYieldElectron +
					   sig.sigmaYieldMuon*sig.sigmaYieldMuon +
					   sig.sigmaYieldTau*sig.sigmaYieldTau +
					   sig.sigmaYieldJes*sig.sigmaYieldJes +
					   sig.sigmaYieldTrigger*sig.sigmaYieldTrigger +
					   sig.sigmaYieldTheory*sig.sigmaYieldTheory
					   );
      sch.sigmaYieldUncorrelated = fabs (sig.sigmaYieldUncorrelated) > significanceThreshold * allYieldUncertainties ? sig.sigmaYieldUncorrelated : 0;
      sch.sigmaYieldElectron = sig.sigmaYieldElectron;
      sch.sigmaYieldMuon = sig.sigmaYieldMuon;
      sch.sigmaYieldTau = sig.sigmaYieldTau;
      sch.sigmaYieldJes = sig.sigmaYieldJes;
      sch.sigmaYieldTrigger = sig.sigmaYieldTrigger;
      sch.sigmaYieldTheory = sig.sigmaYieldTheory;
    }
  }

  bool dumpCombined (const Signatures& fSignatures, const std::string& fFile, const std::string& fTitle, bool normilizeYields, int fChannels) {
    Signatures sig_copy (fSignatures); // local copy
    if (sumYield(sig_copy) <= 0) {
      cout << "dumpCombined-> Total yield is 0, no CARDS is produced " << sumYield(sig_copy) << endl;
      return false;
    }
    sort (sig_copy.begin(), sig_copy.end(), lessExpectedLimit);
    
    StatModelChannels statChannels;
    int nChannels = sig_copy.size();
    if (fChannels > 0 && fChannels < nChannels) nChannels = fChannels;
    convertChannels (sig_copy, statChannels, nChannels, normilizeYields);
    
    vector<int> bkgUncorrelated;
    vector<int> sigUncorrelated;
    bool noBkgWZ = true;
    bool noBkgDD = true;
    bool noBkgZGamma = true;
    bool noBkgZZ = true;
    bool noBkgRare = true;
    bool noBkgJes = true;
    bool noYieldTau = true;
    
    for (int i = 0; i < nChannels; ++i) {
      if (statChannels[i].sigmaBackgroundUncorrelated > 0) bkgUncorrelated.push_back (i);
      if (statChannels[i].sigmaYieldUncorrelated > 0) sigUncorrelated.push_back (i);
      if (statChannels[i].sigmaBackgroundWZ > 0) noBkgWZ = false; 
      if (statChannels[i].sigmaBackgroundDD > 0) noBkgDD = false; 
      if (statChannels[i].sigmaBackgroundZGamma > 0) noBkgZGamma = false; 
      if (statChannels[i].sigmaBackgroundZZ > 0) noBkgZZ = false; 
      if (statChannels[i].sigmaBackgroundRare > 0) noBkgRare = false; 
      if (statChannels[i].sigmaBackgroundJes > 0) noBkgJes = false; 
      if (statChannels[i].sigmaYieldTau > 0) noYieldTau = false; 
    }
    // count nuisances
    int nNuisances = 11; // wz, dd, zg, zz, rare, lumi, mueff, eleeff, taueff, trigger, jes
    if (noBkgWZ) --nNuisances;
    if (noBkgDD) --nNuisances;
    if (noBkgZGamma) --nNuisances;
    if (noBkgZZ) --nNuisances;
    if (noBkgRare) --nNuisances;
    if (noYieldTau) --nNuisances;
  
    nNuisances += (bkgUncorrelated.size() + sigUncorrelated.size());
    
    // produce configuration in HIGGS combination format
    FILE* cfgFile = fopen (fFile.c_str(), "w");
    fprintf (cfgFile,"# %s\n", fTitle.c_str());
    fprintf (cfgFile,"%-20s", "# channels"); 
    for (int i=0;i<nChannels;++i) fprintf(cfgFile, " %s",statChannels[i].name.c_str()); fprintf(cfgFile, "\n");
    
    fprintf (cfgFile,"imax %d number of channels\n", nChannels);
    fprintf (cfgFile,"jmax %d number of background\n", 1);
    fprintf (cfgFile,"kmax %d number of nuisance parameters\n", nNuisances);
    
    fprintf (cfgFile,"%-20s", "observation"); 
    for (int i=0;i<nChannels;++i) fprintf(cfgFile, "%10d", statChannels[i].observed); fprintf(cfgFile, "\n");
    
    fprintf (cfgFile,"%-20s", "bin"); 
    for (int i=0;i<nChannels;++i) fprintf(cfgFile, "%10d%10d", i+1, i+1); fprintf(cfgFile, "\n");
    
    fprintf (cfgFile,"%-20s", "process"); 
    for (int i=0;i<nChannels;++i) fprintf(cfgFile, "%10s%10s", "susy", "bkg"); fprintf(cfgFile, "\n");
    
    fprintf (cfgFile,"%-20s", "process"); 
    for (int i=0;i<nChannels;++i) fprintf(cfgFile, "%10d%10d", 0, 1); fprintf(cfgFile, "\n");
    
    fprintf (cfgFile,"%-20s", "rate"); 
    for (int i=0;i<nChannels;++i) fprintf(cfgFile, "%10.3e%10.3e", 
					  statChannels[i].yield, 
					  statChannels[i].background); fprintf(cfgFile, "\n");
    // for (int i=0;i<nChannels;++i) cout << statChannels[i].name << " \t" << statChannels[i].yield << endl;
    
    if (!noBkgWZ) {
      fprintf (cfgFile,"%-10s%10s", "bkgWZ", "lnN"); 
      for (int i=0;i<nChannels;++i) fprintf(cfgFile, "%10.3f%10.3f", 
					    1.,
					    1.+statChannels[i].sigmaBackgroundWZ); fprintf(cfgFile, "\n");
    }
    
    if (!noBkgDD) {
      fprintf (cfgFile,"%-10s%10s", "bkgDD", "lnN"); 
      for (int i=0;i<nChannels;++i) fprintf(cfgFile, "%10.3f%10.3f", 
					    1.,
					    1.+statChannels[i].sigmaBackgroundDD); fprintf(cfgFile, "\n");
    }
    
    if (!noBkgZGamma) {
      fprintf (cfgFile,"%-10s%10s", "bkgZG", "lnN"); 
      for (int i=0;i<nChannels;++i) fprintf(cfgFile, "%10.3f%10.3f", 
					    1.,
					    1.+statChannels[i].sigmaBackgroundZGamma); fprintf(cfgFile, "\n");
    }

    if (!noBkgZZ) {
      fprintf (cfgFile,"%-10s%10s", "bkgZZ", "lnN"); 
      for (int i=0;i<nChannels;++i) fprintf(cfgFile, "%10.3f%10.3f", 
					    1.,
					    1.+statChannels[i].sigmaBackgroundZZ); fprintf(cfgFile, "\n");
    }
    
    if (!noBkgRare) {
      fprintf (cfgFile,"%-10s%10s", "bkgRare", "lnN"); 
      for (int i=0;i<nChannels;++i) fprintf(cfgFile, "%10.3f%10.3f", 
					    1.,
					    1.+statChannels[i].sigmaBackgroundRare); fprintf(cfgFile, "\n");
    }
    
    fprintf (cfgFile,"%-10s%10s", "JES", "lnN"); 
    for (int i=0;i<nChannels;++i) fprintf(cfgFile, "%10.3f%10.3f", 
					  1.+statChannels[i].sigmaYieldJes,
					  1.+statChannels[i].sigmaBackgroundJes); fprintf(cfgFile, "\n");
    
    fprintf (cfgFile,"%-10s%10s", "Lumi", "lnN"); 
    for (int i=0;i<nChannels;++i) fprintf(cfgFile, "%10.3f%10.3f", 
					  1.+statChannels[i].sigmaLumi,
					  1.); fprintf(cfgFile, "\n");
    
    fprintf (cfgFile,"%-10s%10s", "EffMu", "lnN"); 
    for (int i=0;i<nChannels;++i) fprintf(cfgFile, "%10.3f%10.3f", 
					  1.+statChannels[i].sigmaYieldMuon,
					  1.); fprintf(cfgFile, "\n");

    fprintf (cfgFile,"%-10s%10s", "EffE", "lnN"); 
    for (int i=0;i<nChannels;++i) fprintf(cfgFile, "%10.3f%10.3f", 
					  1.+statChannels[i].sigmaYieldElectron,
					  1.); fprintf(cfgFile, "\n");

    if (!noYieldTau) {
      fprintf (cfgFile,"%-10s%10s", "EffTau", "lnN"); 
      for (int i=0;i<nChannels;++i) fprintf(cfgFile, "%10.3f%10.3f", 
					    1.+statChannels[i].sigmaYieldTau,
					    1.); fprintf(cfgFile, "\n");
    }

    fprintf (cfgFile,"%-10s%10s", "Trigger", "lnN"); 
    for (int i=0;i<nChannels;++i) fprintf(cfgFile, "%10.3f%10.3f", 
					  1.+statChannels[i].sigmaYieldTrigger,
					  1.); fprintf(cfgFile, "\n");
    
    // uncorrelated contributions
    for (int i = 0; i < bkgUncorrelated.size(); ++i) {
      fprintf (cfgFile,"bkgCh%-5d%10s", bkgUncorrelated[i], "lnN");
      for (int ii = 0; ii < nChannels; ++ii) {
	if (ii != bkgUncorrelated[i]) fprintf(cfgFile, "%10.3f%10.3f", 1., 1.);
	else fprintf(cfgFile, "%10.3f%10.3f", 1., 1.+statChannels[ii].sigmaBackgroundUncorrelated);
      }
      fprintf(cfgFile, "\n");
    }
    for (int i = 0; i < sigUncorrelated.size(); ++i) {
      fprintf (cfgFile,"sigCh%-5d%10s", sigUncorrelated[i], "lnN");
      for (int ii = 0; ii < nChannels; ++ii) {
	if (ii != sigUncorrelated[i]) fprintf(cfgFile, "%10.3f%10.3f", 1., 1.);
	else fprintf(cfgFile, "%10.3f%10.3f", 1.+statChannels[ii].sigmaYieldUncorrelated, 1.);
      }
      fprintf(cfgFile, "\n");
    }
    
    fclose (cfgFile);
    return true;
  }



} // namespace

using namespace ra7StatConverter;

string runStatConverter (const string& datadir, int m1, int m2, int maxChannels = 0) {
  Signatures sigs;
  addDataFiles (datadir + "/dataAll.txt", &sigs);
  if (readScanFiles (datadir + "/scanAll.txt", m1, m2, &sigs)) {
    char buffer [1024];
    sprintf (buffer, "ewkino_%d_%d_combinedModel.txt", m1, m2);
    string cardFileName (buffer);
    sprintf (buffer, "ewkino_combined_model %s SMS %d:%d", datadir.c_str(), m1, m2);
    if (dumpCombined (sigs, cardFileName, buffer, true, maxChannels)) {
      dump (sigs, maxChannels);
      return cardFileName;
    }
  }
  return "";
}

void dumpYields (const string& datadir, int m1, int m2) {
  Signatures sigs;
  addDataFiles (datadir + "/dataAll.txt", &sigs);
  if (readScanFiles (datadir + "/scanAll.txt", m1, m2, &sigs)) {
    sort (sigs.begin(), sigs.end(), lessQuickLimit);
    reverse (sigs.begin(), sigs.end());
    cout << datadir <<", masses " <<  m1 << ':' << m2 << endl;
    for (size_t i = 0; i < sigs.size(); ++i) {
      cout << sigs[i].name << ": " << sigs[i].yield << endl;
    }
  }
}
