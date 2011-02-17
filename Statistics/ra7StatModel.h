#include <vector>
#include <string>

#include "TRandom.h"

namespace ra7StatModel {

  struct Signature {
    std::string name;
    int observed;
    double backgroundDD;
    double backgroundMC;
    double yield;
    double sigmaBackgroundMC;
    double sigmaBackgroundDD;
    double sigmaYieldLumi;
    double sigmaYieldStat;
    double sigmaYieldElectron;
    double sigmaYieldMuon;
    double sigmaYieldTrack;
    double sigmaYieldTau;
    double sigmaYieldJES;
  }; 
  typedef std::vector<Signature> Signatures;

  double sumYield (const Signatures& fSignatures);

  void dump (const Signature& fSignature);
  void dump (const Signatures& fSignatures);

  int lessByYield (const Signature& a,const Signature& b) {return a.yield < b.yield;}
  int lessByObserved (const Signature& a,const Signature& b) {return a.observed < b.observed;}
  int lessByBackground (const Signature& a,const Signature& b) {return a.backgroundDD+a.backgroundMC < b.backgroundDD+b.backgroundMC;}

  class Prior {
  public:
    enum Type {Flat, Gauss, Lognormal};
    Prior () {}
    Prior (double fMean, double fSigma, double fMin, double fMax, Type fType); 
    std::vector<double> equidistant_sample (int nNodes) const;
    double generate (TRandom* fRandom = 0) const;
    bool fixed () const {return mFixed;}
    void fix () {mFixed = false;}
    void release () {mFixed = true;}
  private:
    double mMean;
    double mSigma;
    double mMin;
    double mMax;
    bool mFixed;
    Type mType;
  };

  namespace SystematicSourceShared {  
    enum Type {
      lumi, jes, eEff, muEff, tEff, tauEff, extra1, extra2,
      size
    };
  }

  typedef  std::vector<Prior> Priors;
  typedef std::vector<double> PriorValues;

  namespace SystematicSourceIndividual {
    enum Type {
      backgroundDD, backgroundMC, yieldMC,
      size
    };
  }

  typedef  std::vector<Priors> PriorsIndividual;
  typedef std::vector<PriorValues> PriorValuesIndividual;


  class Likelihood {
  public:
    Likelihood (const Signatures& fSignatures);
    double sumYields() const {return mSumYields;}
    double getLikelihood (const PriorValues& fPriorValuesCommon, const PriorValuesIndividual& fPriorValuesIndividual, double fTotalYield) const;
    double getNegLogLikelihood (const PriorValues& fPriorValuesCommon, const PriorValuesIndividual& fPriorValuesIndividual, double fTotalYield) const;
  private:
    Signatures mSignatures;
    double mSumYields;
  };

  
  double runCLs (const Signatures& fSignatures,
		 const Priors& fPriors, const PriorsIndividual& fIndividualPriors, 
		 double fTotalYield, int fToys = 5000);
  double cls95 (const Signatures& fSignatures,
		const Priors& fPriors,  const PriorsIndividual& fIndividualPriors,
		int fToys = 5000);

  class BayesianIntegral {
  public:
    BayesianIntegral (const Likelihood& fModel, 
		      const Priors& fPriors, const PriorsIndividual& fIndividualPriors,
		      int fGridSize = 51);
    std::vector<double> postorial (const std::vector<double>& fGrid);
    std::vector<double> postorialDelta (const std::vector<double>& fGrid, size_t fIndex, SystematicSourceIndividual::Type fType, 
					std::vector<double>* fInternalIntegral = 0);
  private:
    double postorial (double mTotalYield); 
    double postorialDelta (double mTotalYield, size_t fIndex, SystematicSourceIndividual::Type fType, double* fInternalIntegral = 0); 
    double internalIntegral ();

    const Likelihood& mModel; 
    const Priors& mPriors;
    const PriorsIndividual& mIndividualPriors;
    int mNBins;
    std::vector<std::vector<double> > mGrid;
    mutable PriorValues mValuesCache;
    mutable PriorValuesIndividual mIndividualValuesCache;
    mutable double mTotalYieldCache;
  };

 
  void addDataFile (const std::string& fName, Signatures* fSignatures);
  bool readMCFiles (const std::string& fJimFile, const std::string& fRichardFile, int fM0, int fM12, Signatures* fSignatures);
  bool readJimMCFile (const std::string& fName, int fM0, int fM12, Signature* fSignature);
  bool readRichardMCFile (const std::string& fName, int fM0, int fM12, Signature* fSignature);
  std::vector<std::pair<int, int> > allMCPoints (const std::string& fName);

  void samplePriors (const Priors& fPriors, PriorValues* fValues);
  void defaultValues (const Priors& fPriors, PriorValues* fValues);
  void sampleIndividualPriors (const PriorsIndividual& fPriors, PriorValuesIndividual* fValues);
  void defaultValues (const PriorsIndividual& fPriors, PriorValuesIndividual* fValues);
  void initPriors (Priors* fPriors);
  void initPriorsIndividual (const Signatures& fSignatures, PriorsIndividual* fPriors);
  void sampleObserved (const Signatures& fBasicSignatures, const Priors& fPriors, const PriorsIndividual& fPriorsIndividual, Signatures* fSignatures, double fTotalYield = 0);
  void sampleSignatures (const Signatures& fBasicSignatures, const Priors& fPriors, const PriorsIndividual& fPriorsIndividual, Signatures* fSignatures, double fTotalYield = 0);
  void sampleSignatures (const Signatures& fBasicSignatures, Signatures* fSignatures);

  void initSignatures (Signatures* fSignatures, int m1, int m2, bool sugra);

  double runCLs (int m0 = 60, int m12 = 230, bool sugra = true);
  double runBayesian ();
  void expectedLimitCLs (double* limits, int m0 = 60, int m12 = 230, bool sugra = true, bool fSimplifyed = false);
  double coverageCLs (double fTotalYield, int m0 = 60, int m12 = 230, bool sugra = true);

  void plotLimitDistribution (const std::string& fName);

} // namespace ra7StatModel
