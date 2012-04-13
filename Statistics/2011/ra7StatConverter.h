//
// F. Ratnikov, KIT, Feb. 2011 (fedor.ratnikov@cern.ch)
// 
// KIT CLs model. The stand-alone code implementing complete
// description of RA7 without simplifications to reduce total number
// of nuisances.
// - ra7StatConverter.h/C
// - data_outfile_V02.txt, CUDAVISdatafile.txt - measured data files
// - mSugra_RUTCOMBO_kFactor_V02.txt, CUDAVISscanfilemSUGRAkfactor.txt - mSUGRA scans
// - CONLSP_RUTCOMB_KFactor_V02.txt, CUDAVISscanfileGGMkfactor.txt - GGM scans
//
// To run from the ROOT prompt:
// root [1] .L ra7StatConverter.C+
// root [2] cout << "CLs 95%C.L. UL: " << ra7StatConverter::runCLs() << endl;
//
#include <vector>
#include <string>

using namespace std;

namespace ra7StatConverter {

  struct Signature {
    std::string name;
    int observed;
    double backgroundDD;
    double backgroundMC;
    double yield;
    double sigmaBackgroundMC;
    double sigmaBackgroundJes;
    double sigmaBackgroundPdf;
    double sigmaBackgroundDD;
    double sigmaLumi;
    double sigmaYieldStat;
    double sigmaYieldElectron;
    double sigmaYieldMuon;
    double sigmaYieldTau;
    double sigmaYieldJes;
    double sigmaYieldPdf;
    double sigmaTrigger;
    double quickLimit;
    double sigObserved () const;
    double sigSig () const;
    double sigBkgDD () const;
    double getQuickLimit () const;
    double getExpectedLimit () const;
  }; 
  typedef std::vector<Signature> Signatures;

  struct StatModelChannel {
    std::string name;
    int observed;
    double backgroundDD;
    double sigmaBackgroundDD;
    double backgroundMC;
    double sigmaBackgroundMCLumiJesTrigPdf;
    double sigmaBackgroundMC;
    double yield;
    double sigmaYieldStat;
    double sigmaYieldLumiJesTrigPdf;
    double sigmaYieldElectron;
    double sigmaYieldMuon;
    double sigmaYieldTau;
  }; 

  typedef std::vector<StatModelChannel> StatModelChannels;

  string ruChannel (const string& kitCh);
  string kitChannel (const string& ruCh);
  int kitChannelI (const string& ruCh);


  double sumYield (const Signatures& fSignatures);
  int sumObserved (const Signatures& fSignatures);
  double sumBackgrounds (const Signatures& fSignatures);

  void dump (const Signature& fSignature);
  void dump (const Signatures& fSignatures);
  void dumpCombined (const Signatures& fSignatures, const std::string& fFile, const std::string& fTitle = "", bool normalizeYield = false, int fChannels = 0);

  int lessByYield (const Signature& a,const Signature& b) {return a.yield < b.yield;}
  int lessByObserved (const Signature& a,const Signature& b) {return a.observed < b.observed;}
  int lessByBackground (const Signature& a,const Signature& b) {return a.backgroundDD+a.backgroundMC < b.backgroundDD+b.backgroundMC;}
  bool lessPull (const Signature& a, const Signature& b);
  bool lessQuickLimit (const Signature& a, const Signature& b);
  bool lessExpectedLimit (const Signature& a, const Signature& b);

  void addDataFile (const std::string& fName, Signatures* fSignatures);
  bool readMCFiles (const std::string& fRichardFile, int fM0, int fM12, Signatures* fSignatures, double fScale = 1);
  bool readRichardMCFile (const std::string& fName, int fM0, int fM12, Signature* fSignature, double fScale = 1);
  double totalXSection (const std::string& fName, int fM0, int fM12);
  std::vector<std::pair<int, int> > allMCPoints (const std::string& fName);

} // namespace ra7StatConverter
