#include "ra7StatModel.h"

#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>

#include <set>

#include "Math/ProbFuncMathCore.h"
#include "Math/PdfFuncMathCore.h"
#include "Math/QuantFuncMathCore.h"
#include "Math/SpecFuncMathCore.h"

#include "TRandom2.h"
#include "TH1F.h"

using namespace std;

namespace {
  vector<string> tokenize (const string& fInput) {
    vector<string> result;
    string buf; 
    stringstream ss (fInput);
    while (ss >> buf) result.push_back(buf);
    return result;
  }

  TRandom2* globalRndm = new TRandom2 ();
  //  TRandom2* globalRndm = new TRandom2 (time(0));
}

namespace ra7StatModel {

  double sumYield (const Signatures& fSignatures) {
    double result = 0;
    for (size_t i = 0; i < fSignatures.size(); ++i) result += fSignatures[i].yield;
    return result;
  }

  Prior::Prior(double fMean, double fSigma, double fMin, double fMax, Type fType) 
    : mMean(fMean),
      mSigma (fSigma),
      mMin (fMin),
      mMax (fMax),
      mFixed (false),				
      mType (fType)
  {}

  vector<double> Prior::equidistant_sample (int nNodes) const {
    vector<double> result; 
    if (fixed()) {
      result.push_back (1.);
      return result;
    }
    if (mType == Flat) {
      for (int i = 0; i < nNodes; ++i) {
	result.push_back (mMin + (i+0.5)*(mMax-mMin)/nNodes);
      }
    }
    else if (mType == Gauss) {
      double minC = ROOT::Math::normal_cdf (mMin, mSigma, mMean);
      double maxC = ROOT::Math::normal_cdf (mMax, mSigma, mMean);
      for (int i = 0; i < nNodes; ++i) {
	double q = minC + (i+0.5)*(maxC-minC)/nNodes;
	result.push_back (mMean + ROOT::Math::normal_quantile (q, mSigma));
      }
    }
    else if (mType == Lognormal) {
      double minC = ROOT::Math::lognormal_cdf (mMin, 0, mSigma);
      double maxC = ROOT::Math::lognormal_cdf (mMax, 0, mSigma);
      for (int i = 0; i < nNodes; ++i) {
	double q = minC + (i+0.5)*(maxC-minC)/nNodes;
	result.push_back (mMean + ROOT::Math::lognormal_quantile (q, 0, mSigma));
      }
    }
    return result;
  }

  double Prior::generate (TRandom* fRandom) const {
    TRandom* rndm = fRandom ? fRandom : globalRndm;
    if (mType == Flat) {
      return rndm->Uniform (mMin, mMax);
    }
    else if (mType == Gauss) {
      while (1) {
	double r = rndm->Gaus (mMean, mSigma);
	if (r >= mMin && r <= mMax) return r;
      }
    }
    cout << "Prior::generate is not implemented for method " << int (mType) << endl;
    return 0;
  }


  Likelihood::Likelihood (const Signatures& fSignatures) 
    : mSignatures (fSignatures),
      mSumYields (sumYield (fSignatures))
  {}

  double Likelihood::getLikelihood (const PriorValues& fPriorValuesCommon, 
				    const PriorValuesIndividual& fPriorValuesIndividual, 
				    double fTotalYield) const {
    return exp (-getNegLogLikelihood (fPriorValuesCommon, fPriorValuesIndividual, fTotalYield));
  }

  double Likelihood::getNegLogLikelihood (const PriorValues& fPriorValuesCommon, 
				       const PriorValuesIndividual& fPriorValuesIndividual, 
				       double fTotalYield) const {
    double result = 0;
    size_t nSig = mSignatures.size();
    vector<double> estimatedYields (nSig);
    vector<double> estimatedBackgrounds (nSig);
    double yieldSum = 0;
    for (size_t i = 0; i < nSig; ++i) {
      const Signature& sig = mSignatures[i];
      const PriorValues& priorsIndividual = fPriorValuesIndividual[i];
      double& estimatedYield = estimatedYields[i];
      estimatedYield = sig.yield;
      if (estimatedYield > 0) {
	estimatedYield *= (1 + sig.sigmaYieldLumi * fPriorValuesCommon[SystematicSourceShared::lumi]);
	estimatedYield *= (1 + sig.sigmaYieldJES * fPriorValuesCommon[SystematicSourceShared::jes]);
	estimatedYield *= priorsIndividual[SystematicSourceIndividual::yieldMC];
	estimatedYield *= (1 + sig.sigmaYieldElectron  * fPriorValuesCommon[SystematicSourceShared::eEff]);
	estimatedYield *= (1 + sig.sigmaYieldMuon  * fPriorValuesCommon[SystematicSourceShared::muEff]);
	estimatedYield *= (1 + sig.sigmaYieldTrack  * fPriorValuesCommon[SystematicSourceShared::tEff]);
	estimatedYield *= (1 + sig.sigmaYieldTau  * fPriorValuesCommon[SystematicSourceShared::tauEff]);
      }
      
      double backgroundDD = sig.backgroundDD * priorsIndividual[SystematicSourceIndividual::backgroundDD];
      double backgroundMC = sig.backgroundMC * priorsIndividual[SystematicSourceIndividual::backgroundMC];
      //double backgroundMC = sig.backgroundMC * (1.+sig.sigmaBackgroundMC/6.9*fPriorValuesCommon[SystematicSourceShared::extra1]);
      double& estimatedBackground = estimatedBackgrounds[i];
      estimatedBackground = backgroundDD + backgroundMC;

      if (estimatedYield < 0) estimatedYield = 0;
      if (estimatedBackground < 0) estimatedBackground = 1e-10;
      yieldSum += estimatedYield;
    }
    for (size_t i = 0; i < nSig; ++i) {
      estimatedYields[i] *= fTotalYield / yieldSum;
      double likelh = ROOT::Math::poisson_pdf (mSignatures[i].observed, 
					       estimatedYields[i] + estimatedBackgrounds[i]);
      if (likelh <= 0) {
	cout << "Likelihood::getNegLogLikelihood-> " << i<<' '
	     <<mSignatures[i].name<<'/'<<mSignatures[i].observed << '/'
	     <<estimatedYields[i]<<'/'<<estimatedBackgrounds[i]<<'/'
	     <<likelh<<'/'<<result<<endl;
	 exit(0);
      }
      result -= (likelh > 0 ? log(likelh) : -1e9);
    }
    return result;
  }

  double runCLs (const Signatures& fSignatures,
		 const Priors& fPriors, const PriorsIndividual& fIndividualPriors, 
		 double fTotalYield, int fToys) {
    Likelihood baseModel (fSignatures);
    PriorValues basePriorValues;
    defaultValues (fPriors, &basePriorValues);
    PriorValuesIndividual basePriorValuesIndividual;
    defaultValues (fIndividualPriors, &basePriorValuesIndividual);
   
    double dNLLdata = 2 * (baseModel.getNegLogLikelihood (basePriorValues, basePriorValuesIndividual, fTotalYield) -
			   baseModel.getNegLogLikelihood (basePriorValues, basePriorValuesIndividual, 0));

    int nDataNLLsbBetter = 0;
    int nDataNLLbBetter = 0;
    int nToys = 0;
    PriorValues priorValues;
    PriorValuesIndividual priorValuesIndividual;
    Signatures toySignaturesB;
    Signatures toySignaturesSB;
    for (; nToys < fToys; ++nToys) {
      samplePriors (fPriors, &priorValues);
      sampleIndividualPriors (fIndividualPriors, &priorValuesIndividual);
      sampleSignatures (fSignatures, fPriors, fIndividualPriors, &toySignaturesB, 0);
      sampleSignatures (fSignatures, fPriors, fIndividualPriors, &toySignaturesSB, fTotalYield);
      Likelihood dataB (toySignaturesB);
      Likelihood dataSB (toySignaturesSB);
      double dNLLb = 2 * (dataB.getNegLogLikelihood (basePriorValues, basePriorValuesIndividual, fTotalYield) - 
			 dataB.getNegLogLikelihood (basePriorValues, basePriorValuesIndividual, 0));
      double dNLLsb = 2 * (dataSB.getNegLogLikelihood (basePriorValues, basePriorValuesIndividual, fTotalYield) - 
			 dataSB.getNegLogLikelihood (basePriorValues, basePriorValuesIndividual, 0));

      if (dNLLsb >= dNLLdata) ++nDataNLLsbBetter;
      if (dNLLb >= dNLLdata) ++nDataNLLbBetter;
      // cout << "runCLs-> " << fTotalYield<<' '<<iToy<<' '<<dNLLdata<<'/'<<dNLLsb<<'/'<<dNLLb<<"->"<<nDataNLLsbBetter<<'/'<<nDataNLLbBetter<<endl;
      // good enough?
      if (nDataNLLsbBetter > 5 && nDataNLLbBetter < nDataNLLsbBetter * 10) break;
      if (nDataNLLsbBetter > 100) break;
    }
    double cl_sb = double (nDataNLLsbBetter) / nToys;
    double cl_b = double (nDataNLLbBetter) / nToys;
    if (cl_b <= 0) cl_b = 1e-6;
    // cout << "runCLs-> " << fTotalYield<<" toys: " << nToys<<" cl_sb/cl_b " << cl_sb<<'/'<<cl_b<<endl;
    return cl_sb/cl_b;
  }

  double cls95 (const Signatures& fSignatures, const Priors& fPriors, 
		const PriorsIndividual& fIndividualPriors,
		int fToys) {
    const bool track = false;
    double target = 0.05;
    double x0 = sumYield (fSignatures);
    double cl0 = runCLs (fSignatures, fPriors, fIndividualPriors, x0, fToys);
    double x1 = x0;
    double cl1 = cl0;
    if (cl0 > target) {
      while (cl1 > target) {
	x0 = x1;
	cl0 = cl1;
	x1 *= 2;
	cl1 = runCLs (fSignatures, fPriors, fIndividualPriors, x1, fToys);
	if (track) cout << "cls95 1 -> " << x0 <<'/'<<cl0<<'/'<<x1<<'/'<<cl1<<endl;
      }
    }
    else {
      while (cl0 < target) {
	x1 = x0;
	cl1 = cl0;
	x0 *= 0.5;
	cl0 = runCLs (fSignatures, fPriors, fIndividualPriors, x0, fToys);
	if (track) cout << "cls95 2 -> " << x0 <<'/'<<cl0<<'/'<<x1<<'/'<<cl1<<endl;
	if (x0 < 1e-3) {
	  // cout << "cls95-> break infinite loop at " << x0 << endl; 
	  cout << '!' << flush;
	  return x0;
	}
      }
    }
    double precision = sqrt (target/fToys);
    while (abs((x0-x1)*2/(x0+x1)) > 0.01) {
      double x = 0.5 * (x0 + x1);
      //      double x = x0 + (cl0-target)/(cl0-cl1)*(x1-x0);
      double cl = runCLs (fSignatures, fPriors, fIndividualPriors, x, fToys);
      if (track) cout << "cls95 3 -> " << x<<'/'<<cl<<' '<<x0 <<'/'<<cl0<<'/'<<x1<<'/'<<cl1<<'/'<<precision<<endl;
      if (cl < target) {
	x1 = x;
	cl1 = cl;
      }
      else {
	x0 = x;
	cl0 = cl;
      }
    }
    return 0.5 * (x0 + x1);
  }


  BayesianIntegral::BayesianIntegral (const Likelihood& fModel, 
				      const Priors& fPriors, const PriorsIndividual& fIndividualPriors,
				      int fGridSize) 
    : mModel (fModel),
      mPriors (fPriors),
      mIndividualPriors (fIndividualPriors),
      mNBins (fGridSize)
  {
    for (size_t i = 0; i < mPriors.size(); ++i) {
      mGrid.push_back (mPriors[i].equidistant_sample (mNBins));
    }
  }

  vector<double> BayesianIntegral::postorial (const std::vector<double>& fGrid) {
    vector<double> result;
    for (size_t i = 0; i < fGrid.size(); ++i) {
      result.push_back (postorial (fGrid[i]));
    }
    return result;
  }
  
vector<double> BayesianIntegral::postorialDelta (const vector<double>& fGrid, size_t fIndex, SystematicSourceIndividual::Type fType, 
						 std::vector<double>* fInternalIntegral) {
  vector<double> result;
    for (size_t i = 0; i < fGrid.size(); ++i) {
      result.push_back (postorialDelta (fGrid[i], fIndex, fType, fInternalIntegral ? &((*fInternalIntegral)[i]) : 0));
    }
    return result;
}
  

  double BayesianIntegral::postorial (double mTotalYield) {
    mTotalYieldCache = mTotalYield;
    defaultValues (mIndividualPriors, &mIndividualValuesCache);
    mValuesCache.clear();
    return internalIntegral ();
  }

  double BayesianIntegral::postorialDelta (double mTotalYield, size_t fIndex, SystematicSourceIndividual::Type fType, double* fInternalIntegral) {
    double result = 0;
    double referenceIntegral = fInternalIntegral ? *fInternalIntegral : postorial (mTotalYield);
    vector<double> grid = mIndividualPriors[fIndex][fType].equidistant_sample (mNBins);
    defaultValues (mIndividualPriors, &mIndividualValuesCache);
    for (size_t i = 0; i < grid.size(); ++i) {
      mIndividualValuesCache[fIndex][fType] = grid[i];
      result += postorial (mTotalYield);
    }
    return result / grid.size() - referenceIntegral;
  }
 
 double BayesianIntegral::internalIntegral () {
    size_t rank = mValuesCache.size ();
    if (rank >= mPriors.size ()) {
      return mModel.getLikelihood (mValuesCache, mIndividualValuesCache, mTotalYieldCache);
    }
    double result = 0;
    mValuesCache.push_back(0);
    for (size_t i = 0; i < mGrid[rank].size(); ++i) {
      mValuesCache.back() = mGrid[rank][i];
      result += internalIntegral (); // reccursion
    }
    mValuesCache.resize (rank); // cleanup
    return result;
  }

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
	  sig.sigmaYieldLumi = sigmaLumi;
	  sig.backgroundMC = atof (tokens[3].c_str());
	  if (sig.backgroundMC <= 0) sig.backgroundMC = 1e-6;
	  sig.sigmaBackgroundMC = atof(tokens[4].c_str()) / sig.backgroundMC;
	  sig.backgroundDD = atof (tokens[5].c_str());
	  if (sig.backgroundDD <= 0) sig.backgroundDD = 1e-6;
	  sig.sigmaBackgroundDD = atof(tokens[6].c_str()) / sig.backgroundDD;
	  
	  fSignatures->push_back (sig);
	}
    }
  }

  bool readMCFiles (const string& fJimFile, const string& fRichardFile, int fM0, int fM12, Signatures* fSignatures) {
    for (size_t i = 0; i < fSignatures->size(); ++i) {
      Signature* sig = &((*fSignatures)[i]);
      if (!readJimMCFile (fJimFile, fM0, fM12, sig)) {
	if (!readRichardMCFile (fRichardFile, fM0, fM12, sig)) {
	  cerr << "readMCFiles-> Worning can not find data for signature " <<  sig->name << " in " << fM0 << ':' << fM12 << endl;
	  return false;
	  sig->sigmaYieldElectron = 0;
	  sig->sigmaYieldMuon = 0;
	  sig->sigmaYieldTau = 0;
	  sig->sigmaYieldTrack = 0;
	  sig->sigmaYieldJES = 0;
	
	  sig->yield = 0;
	  sig->sigmaYieldStat = 0;
	  
	}
      }
    }
    return true;
  }

  bool readJimMCFile (const string& fName, int fM0, int fM12, Signature* fSignature) {
    // constants
    double muEffSigma = 0.03;
    double eEffSigma = 0.03;
    double tauEffSigma = 0.3;
    double jesSigma = 0.05;

    char buffer[1024];
    Signature* sig = fSignature;
    const string flavor = sig->name;
    ifstream in (fName.c_str());
    while (in.getline (buffer, 1024)) {
      vector<string> tokens = tokenize (string(buffer));
      if (tokens.size() < 4) continue;
      if (tokens[0] != "scan") continue;
      if (tokens[1] != "m0m12" || int(atof (tokens[2].c_str())) != fM0 || int(atof (tokens[3].c_str())) != fM12) continue;
      if (tokens.size() == 7 && tokens[4] == sig->name) {
	double yield = atof (tokens[5].c_str());
	if (yield <= 0) yield = 1e-9; 
	// parse lepton flavors
	int ne = 0;
	int nmu = 0;
	int ntau = 0;
	size_t index;
	if ((index = flavor.find ("mu")) != string::npos) nmu = int(flavor[index-1])-int('0'); if (nmu > 9) nmu = 1;
	if ((index = flavor.find ("e")) != string::npos) ne = int(flavor[index-1])-int('0'); if (ne > 9) ne = 1;
	if ((index = flavor.find ("tau")) != string::npos) ntau = int(flavor[index-1])-int('0'); if (ntau > 9) ntau = 1;
	

	sig->yield *= yield;

	sig->sigmaYieldElectron = ne * eEffSigma;
	sig->sigmaYieldMuon = nmu * muEffSigma;
	sig->sigmaYieldTau = ntau * tauEffSigma;
	sig->sigmaYieldTrack = 0;
	sig->sigmaYieldJES = jesSigma;
	
	double allSigma2 = atof (tokens[6].c_str()) / yield; allSigma2 *= allSigma2;
	allSigma2 -= sig->sigmaYieldElectron*sig->sigmaYieldElectron;
	allSigma2 -= sig->sigmaYieldMuon*sig->sigmaYieldMuon;
	allSigma2 -= sig->sigmaYieldTau*sig->sigmaYieldTau;
	//sig->sigmaYieldStat = allSigma2 > 0 ? sqrt (allSigma2) : 0.;
	sig->sigmaYieldStat = allSigma2 > 0 ? sqrt (allSigma2) : 0.002 / yield;
	
	return true;
      }
    }
    return false;
  }

  bool readRichardMCFile (const string& fName, int fM0, int fM12, Signature* fSignature) {
    // constants
    double jesSigma = 0.05;

    char buffer[1024];
    Signature* sig = fSignature;
    const string flavor = sig->name;
    ifstream in (fName.c_str());
    while (in.getline (buffer, 1024)) {
      vector<string> tokens = tokenize (string(buffer));
      if (tokens.size() < 4) continue;
      if (tokens[0] != "scan") continue;
      if (tokens[1] != "m0m12" || int(atof (tokens[2].c_str())) != fM0 || int(atof (tokens[3].c_str())) != fM12) continue;
      if (tokens.size() == 13 && tokens[4] == sig->name) {
	double yield = atof (tokens[5].c_str());
	if (yield <= 0) yield = 1e-9;
	sig->yield *= yield;
	double sigmaStat = atof (tokens[7].c_str());
	//if (sigmaStat <= 0) sigmaStat = 0.;
	if (sigmaStat <= 0) sigmaStat = 0.002;
	sig->sigmaYieldStat = sigmaStat / yield;
	sig->sigmaYieldElectron = atof (tokens[9].c_str()) / yield;
	sig->sigmaYieldMuon = atof (tokens[8].c_str()) / yield;
	sig->sigmaYieldTau = atof (tokens[11].c_str()) / yield;
	sig->sigmaYieldTrack = atof (tokens[10].c_str()) / yield;
	sig->sigmaYieldJES = jesSigma;
	return true;
      }
    }
    return false;
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


  void samplePriors (const Priors& fPriors, PriorValues* fValues) {
    PriorValues& result = *fValues;
    result.resize (fPriors.size());
    for (size_t i = 0; i < fPriors.size(); ++i) {
      // cout << "   samplePriors-> " << i << endl;
      result[i] = fPriors[i].generate();
    }
  }

  void defaultValues (const Priors& fPriors, PriorValues* fValues) {
    PriorValues& result = *fValues; 
    result.resize (fPriors.size());
    for (size_t i = 0; i < fPriors.size(); ++i) {
      result[i] = 0;
    }
 }

  void sampleIndividualPriors (const PriorsIndividual& fPriors, PriorValuesIndividual* fValues) {
    PriorValuesIndividual& result = *fValues;
    result.resize (fPriors.size());
    for (size_t i = 0; i < fPriors.size(); ++i) {
      // cout << "sampleIndividualPriors-> " << i << endl;
      samplePriors (fPriors[i], &(result[i]));
    }
  }

  void defaultValues (const PriorsIndividual& fPriors, PriorValuesIndividual* fValues) {
    PriorValuesIndividual& result = *fValues; 
    result.resize (fPriors.size());
    for (size_t i = 0; i < fPriors.size(); ++i) {
      PriorValues& values = result[i]; 
      values.resize (fPriors[i].size());
      for (size_t j = 0; j < fPriors[i].size(); ++j) {
	values[j] = 1.;
      }
    }
  }

  void sampleSignatures (const Signatures& fBasicSignatures, const Priors& fPriors, const PriorsIndividual& fPriorsIndividual, Signatures* fSignatures, double fTotalYield) {
    Signatures& result = *fSignatures;
    result = fBasicSignatures;
    size_t nSig = result.size();
    PriorValues pv; 
    samplePriors (fPriors, &pv);
    PriorValuesIndividual pvi;
    sampleIndividualPriors (fPriorsIndividual, &pvi);
    double totalYield = 0;
    vector<double> backgrounds(nSig);
    for (size_t i = 0; i < nSig; ++i) {
      Signature& sig = result[i];
      double backgroundDD = sig.backgroundDD * pvi[i][SystematicSourceIndividual::backgroundDD]; 
      double backgroundMC = sig.backgroundMC * pvi[i][SystematicSourceIndividual::backgroundMC];
      sig.yield *= (1 + sig.sigmaYieldLumi * pv[SystematicSourceShared::lumi]);
      sig.yield *= (1 + sig.sigmaYieldJES * pv[SystematicSourceShared::jes]);
      sig.yield *= pvi[i][SystematicSourceIndividual::yieldMC];
      sig.yield *= (1 + sig.sigmaYieldElectron  * pv[SystematicSourceShared::eEff]);
      sig.yield *= (1 + sig.sigmaYieldMuon  * pv[SystematicSourceShared::muEff]);
      sig.yield *= (1 + sig.sigmaYieldTrack  * pv[SystematicSourceShared::tEff]);
      sig.yield *= (1 + sig.sigmaYieldTau  * pv[SystematicSourceShared::tauEff]);
      if (sig.yield <= 0) sig.yield = 1e-6;
      totalYield += sig.yield;
      backgrounds[i] = backgroundMC+backgroundDD;
    }
    for (size_t i = 0; i < nSig; ++i) {
      Signature& sig = result[i];
      double yield = fTotalYield / totalYield * sig.yield; 
      sig.observed = globalRndm->Poisson (yield + backgrounds[i]);
//       cout << "samplePriors-> " << sig.name << ' ' 
// 	   <<fTotalYield<<'/'<<totalYield<<'*'<<sig.yield<<'='<<yield<<' '
// 	   << backgrounds[i]<<' '<<sig.observed<<endl;
    }
  }

  void sampleSignatures (const Signatures& fBasicSignatures, Signatures* fSignatures) {
    Signatures& result = *fSignatures;
    result = fBasicSignatures;
    for (size_t i = 0; i < result.size(); ++i) {
      Signature& sig = result[i];
      sig.observed = globalRndm->Poisson (sig.backgroundMC+sig.backgroundDD);
    }
  }


  void initSignatures (Signatures* fSignatures, int m0, int m12) {
    fSignatures->clear();
    // addDataFile("t2_data.txt",fSignatures);
    //      readMCFiles ("CUDAVISscanfilemSUGRAkfactor.txt", "testscan.txt", 60, 230, fSignatures);
    addDataFile ("data_outfile_V02.txt", fSignatures);
    addDataFile ("CUDAVISdatafile.txt", fSignatures);
    readMCFiles ("CUDAVISscanfilemSUGRAkfactor.txt", "mSugra_RUTCOMBO_kFactor_V02.txt", m0, m12, fSignatures);
  }
  
  void initPriors (Priors* fPriors) {
    fPriors->clear();
    fPriors->resize (SystematicSourceShared::size);
    (*fPriors)[SystematicSourceShared::lumi] = Prior (0., 1., -5, 5, Prior::Gauss);
    (*fPriors)[SystematicSourceShared::jes] = Prior (0, 1., -5, 5, Prior::Gauss);
    (*fPriors)[SystematicSourceShared::eEff] = Prior (0, 1., -5, 5, Prior::Gauss);
    (*fPriors)[SystematicSourceShared::muEff] = Prior (0, 1., -5, 5, Prior::Gauss);
    (*fPriors)[SystematicSourceShared::tEff] = Prior (0, 1., -5, 5, Prior::Gauss);
    (*fPriors)[SystematicSourceShared::tauEff] = Prior (0, 1., -3, 5, Prior::Gauss);
    (*fPriors)[SystematicSourceShared::extra1] = Prior (0, 6.9, -1, 34, Prior::Gauss);
    (*fPriors)[SystematicSourceShared::extra2] = Prior (0, 1., -5, 5, Prior::Gauss);
  }

  void initPriorsIndividual (const Signatures& fSignatures, PriorsIndividual* fPriors) {
    fPriors->clear();
    for (size_t i = 0; i < fSignatures.size(); ++i) {
      Priors individualPriors (SystematicSourceIndividual::size);
      const Signature& sig = fSignatures[i];
      individualPriors[SystematicSourceIndividual::backgroundDD] = 
	Prior (1, sig.sigmaBackgroundDD, 0, 1+5*sig.sigmaBackgroundDD, Prior::Gauss);
      individualPriors[SystematicSourceIndividual::backgroundMC] = 
	Prior (1, sig.sigmaBackgroundMC, 0, 1+5*sig.sigmaBackgroundMC, Prior::Gauss);
      individualPriors[SystematicSourceIndividual::yieldMC] = 
	Prior (1, sig.sigmaYieldStat, 0, 1+5*sig.sigmaYieldStat, Prior::Gauss);

      fPriors->push_back(individualPriors);
    }
  }

  double runCLs (int m0, int m12) {
    Signatures sigs;
    initSignatures (&sigs, m0, m12);
    Priors priors;
    initPriors (&priors);
    PriorsIndividual individualPriors;
    initPriorsIndividual (sigs, &individualPriors);
    double cls95Yield = cls95 (sigs, priors, individualPriors, 20000);
    return cls95Yield;
  }
  
  void expectedLimitCLs (int m0, int m12, bool fSimplifyed) {
    Signatures sigs;
    initSignatures (&sigs, m0, m12);
    Priors priors;
    initPriors (&priors);
    PriorsIndividual individualPriors;
    initPriorsIndividual (sigs, &individualPriors);

    double oneSigmaQuantile = ROOT::Math::normal_cdf (-1);
    double twoSigmaQuantile = ROOT::Math::normal_cdf (-2);
    int nToys (int(floor(5./twoSigmaQuantile+0.5)));
    cout << "expectedLimitCLs -> toys: " << nToys << endl;
    vector<double> sample;
    sample.reserve (nToys);
    Signatures toySigs;
    for (int i = 0; i < nToys; ++i) {
      if (fSimplifyed) sampleSignatures (sigs, &toySigs);
      else sampleSignatures (sigs, priors, individualPriors, &toySigs, 0);
      double cls95Yield = cls95 (toySigs, priors, individualPriors, 2000);
      sample.push_back (cls95Yield);
      if (!(i % 10))  cout << i/10 << flush;
      else cout << '.' << flush;
    }
    cout << endl;
    sort (sample.begin(), sample.end());
    // extract statystics
    double Minus2Sigma = sample[int(floor(nToys * twoSigmaQuantile + 0.5))];
    double Minus1Sigma = sample[int(floor(nToys * oneSigmaQuantile + 0.5))];
    double Median = sample[int(floor(nToys * 0.5+0.5))];
    double Plus1Sigma = sample[int(floor(nToys * (1.-oneSigmaQuantile) + 0.5))];
    double Plus2Sigma = sample[int(floor(nToys * (1.-twoSigmaQuantile) + 0.5))];

    cout << "expectedLimitCLs-> median: " << Median 
	 << ", +-1sigma: [" <<  Minus1Sigma << ", " << Plus1Sigma
	 << ", +-2sigma: [" <<  Minus2Sigma << ", " << Plus2Sigma
	 << endl;

    TH1F* h = new TH1F ("cl95", "cl95", 100, 0, sample.back());
    for (size_t i = 0; i < sample.size(); ++i) h->Fill (sample[i]);
    h->Draw();
  }

  double runBayesian () {
    return 0;
  }

  double coverageCLs (double fTotalYield, int m0, int m12) {
    Signatures sigs;
    initSignatures (&sigs, m0, m12);
    Priors priors;
    initPriors (&priors);
    PriorsIndividual individualPriors;
    initPriorsIndividual (sigs, &individualPriors);
    int nAbove = 0;
    int nToys = 0;
    Signatures toySigs;
    while (++nToys <= 2000) {
      sampleSignatures (sigs, priors, individualPriors, &toySigs, fTotalYield);
      double cls95Yield = cls95 (toySigs, priors, individualPriors, 2000);
      if (cls95Yield < fTotalYield) nAbove++;
      cout << "coverageCLs-> " << nToys << " " << fTotalYield << '/' << cls95Yield << " -> " << nAbove << '/' << 1.-double (nAbove)/double(nToys) << endl;
    }
    return 1.-double (nAbove)/double(nToys);
  }

  void plotLimitDistribution (const std::string& fName) {
    ofstream dump (fName.c_str());
    vector<pair<int,int> > scan = allMCPoints ("CUDAVISscanfilemSUGRAkfactor.txt");
    TH1F* h = new TH1F ("UL", "UL", 150, 0, 15);
    for (size_t i = 0; i < scan.size(); ++i) {
      Signatures sigs;
      addDataFile ("data_outfile_V02.txt", &sigs);
      addDataFile ("CUDAVISdatafile.txt", &sigs);
      Priors priors;
      PriorsIndividual individualPriors;
      if (!readMCFiles ("CUDAVISscanfilemSUGRAkfactor.txt", "mSugra_RUTCOMBO_kFactor_V02.txt", scan[i].first, scan[i].second, &sigs)) continue;
      double signalYield = sumYield (sigs);
      if (signalYield < 3 || signalYield > 12) {
	cout << "CLs95-> " << scan[i].first << ':' << scan[i].second << " ignore signal " << signalYield << endl;
	continue;
      }
      initPriors (&priors);
      initPriorsIndividual (sigs, &individualPriors);
      double cls95Yield = cls95 (sigs, priors, individualPriors, 20000);
      cout << "CLs95-> " << scan[i].first << ':' << scan[i].second << " UL: " << cls95Yield << endl;
      h->Fill (cls95Yield);
      dump << scan[i].first << ' ' << scan[i].second << ' ' << cls95Yield << endl;
    }
    h->Draw();
  }

} // namespace

