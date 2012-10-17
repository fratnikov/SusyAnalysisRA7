//
// F. Ratnikov, KIT, Sep. 2012 (fedor.ratnikov@cern.ch)
// 
// EWKino CLs model. The stand-alone code implementing complete
// description of RA7 without simplifications to reduce total number
// of nuisances.
// - ra7StatConverter.h/C
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
    int id;
    std::string name;
    int observed;
    double background;
    double yield;
    double sigmaBackgroundUncorrelated;
    double sigmaBackgroundDD;
    double sigmaBackgroundJes;
    double sigmaBackgroundWZ;
    double sigmaBackgroundZZ;
    double sigmaBackgroundZGamma;
    double sigmaBackgroundRare;
    double sigmaLumi;
    double sigmaYieldUncorrelated;
    double sigmaYieldElectron;
    double sigmaYieldMuon;
    double sigmaYieldTau;
    double sigmaYieldJes;
    double sigmaYieldTrigger;
    double sigmaYieldTheory;
    double quickLimit;
    double getQuickLimit () const;
    double getExpectedLimit () const;
    double sigmaBackground () const;
    double sigmaYield () const;
  }; 
  typedef std::vector<Signature> Signatures;

  struct StatModelChannel {
    int id;
    std::string name;
    int observed;
    double background;
    double yield;
    double sigmaBackgroundUncorrelated;
    double sigmaBackgroundWZ;
    double sigmaBackgroundDD;
    double sigmaBackgroundZGamma;
    double sigmaBackgroundZZ;
    double sigmaBackgroundRare;
    double sigmaBackgroundJes;
    double sigmaLumi;
    double sigmaYieldUncorrelated;
    double sigmaYieldMuon;
    double sigmaYieldElectron;
    double sigmaYieldTau;
    double sigmaYieldTrigger;
    double sigmaYieldJes;
    double sigmaYieldTheory;
  }; 

  typedef std::vector<StatModelChannel> StatModelChannels;

  double sumYield (const Signatures& fSignatures, int fLimit = 0);
  int sumObserved (const Signatures& fSignatures);
  double sumBackgrounds (const Signatures& fSignatures);

  void dump (const Signature& fSignature);
  void dump (const Signatures& fSignatures, int fLimit = 10);
  bool dumpCombined (const Signatures& fSignatures, const std::string& fFile, const std::string& fTitle = "", bool normalizeYield = false, int fChannels = 0);

  bool lessQuickLimit (const Signature& a, const Signature& b);
  bool lessExpectedLimit (const Signature& a, const Signature& b);

  void addDataFiles (const std::string& fMegaName, Signatures* fSignatures);
  bool readScanFiles (const std::string& fMegaName, int fM1, int fM2, Signatures* fSignatures, double fScale = 1);
  double totalXSection (const std::string& fMegaName, int fM1, int fM2);

} // namespace ra7StatConverter
