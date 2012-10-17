#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <iostream>
#include <sstream>

#include "TFile.h"
#include "TH1F.h"

using namespace std;

double getXsection (double x, const char* inputFile) {
  ifstream input (inputFile);
  double xPrev = -1;
  double yPrev = -1;
  while (input) {
    double xThis, yThis, dy;
    input >> xThis >> yThis >> dy;
    if (!input) {
      cerr << "getXsection-> error reading stream" << endl;
      return 0;
    }
    if (xThis >= x) {
      if (xPrev < 0) return yThis;
      double y = exp (log(yPrev) + (log(yThis)-log(yPrev)) * (x-xPrev)/(xThis-xPrev));
      //cout << "prev:"<<xPrev<<':'<<yPrev<<" this:"<<xThis<<':'<<yThis<<" -> " << x<<':'<<y<<endl;
      return y;
    }
    xPrev = xThis;
    yPrev = yThis;
  }
  return 0;
}



vector<string> tokenize (const string& fInput) {
  vector<string> result;
  if (!fInput.empty() && fInput[0] != '#') {
    string buf; 
    stringstream ss (fInput);
    while (ss >> buf) result.push_back(buf);
  }
  return result;
}

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
 };

void makeCards (int i1, int i2, double scaleYield = 1., bool makeData = false) 
{
  double intLumi = 9200;
  int m1 = 100 + (i1-11)*10;
  int m2 = (i2-1)*10;
  double xSection = getXsection (m1, "8TeVc1n2.dat");
  //  cout << "xsection: " << m1 << "->" << xSection<<endl;
  Signature sigs[5];
  // first read LandS file
  char buffer[1024];
  sprintf (buffer, "cards/V00-00-04/SMS_%d_%d.txt", i1, i2);
  ifstream cardin (buffer);
  double lumi = 0;
  double leff = 0;
  double btag = 0;
  
  while (cardin.getline (buffer, 1024)) 
    {
      vector<string> tokens = tokenize (string(buffer));
      if (tokens[0] == string("lumi")) lumi = atof (tokens[2].c_str()) - 1.;
      else if (tokens[0] == string("eff_leptons")) leff = atof (tokens[2].c_str()) - 1.;
      else if (tokens[0] == string("btagerr")) btag = atof (tokens[2].c_str()) - 1.;
   }
  // now process shapes
  sprintf (buffer, "rootfiles/V00-00-04/SMS_%d_%d.root", i1, i2);
  TFile rootin (buffer);
  TH1F* histo_Data = dynamic_cast<TH1F*> (rootin.FindObjectAny ("histo_Data"));
  TH1F* histo_Zbkg = dynamic_cast<TH1F*> (rootin.FindObjectAny ("histo_Zbkg"));
  TH1F* histo_Zbkg_errZUp = dynamic_cast<TH1F*> (rootin.FindObjectAny ("histo_Zbkg_errZUp"));
  TH1F* histo_Zbkg_errZDown = dynamic_cast<TH1F*> (rootin.FindObjectAny ("histo_Zbkg_errZDown"));
  TH1F* histo_OFbkg = dynamic_cast<TH1F*> (rootin.FindObjectAny ("histo_OFbkg"));
  TH1F* histo_OFbkg_errOFUp = dynamic_cast<TH1F*> (rootin.FindObjectAny ("histo_OFbkg_errOFUp"));
  TH1F* histo_OFbkg_errOFDown = dynamic_cast<TH1F*> (rootin.FindObjectAny ("histo_OFbkg_errOFDown"));
  TH1F* histo_WZbkg = dynamic_cast<TH1F*> (rootin.FindObjectAny ("histo_WZbkg"));
  TH1F* histo_WZbkg_errWZUp = dynamic_cast<TH1F*> (rootin.FindObjectAny ("histo_WZbkg_errWZUp"));
  TH1F* histo_WZbkg_errWZDown = dynamic_cast<TH1F*> (rootin.FindObjectAny ("histo_WZbkg_errWZDown"));
  TH1F* histo_ZZbkg = dynamic_cast<TH1F*> (rootin.FindObjectAny ("histo_ZZbkg"));
  TH1F* histo_ZZbkg_errZZUp = dynamic_cast<TH1F*> (rootin.FindObjectAny ("histo_ZZbkg_errZZUp"));
  TH1F* histo_ZZbkg_errZZDown = dynamic_cast<TH1F*> (rootin.FindObjectAny ("histo_ZZbkg_errZZDown"));
  TH1F* histo_rarebkg = dynamic_cast<TH1F*> (rootin.FindObjectAny ("histo_rarebkg"));
  TH1F* histo_rarebkg_errRAREUp = dynamic_cast<TH1F*> (rootin.FindObjectAny ("histo_rarebkg_errRAREUp"));
  TH1F* histo_rarebkg_errRAREDown = dynamic_cast<TH1F*> (rootin.FindObjectAny ("histo_rarebkg_errRAREDown"));
  sprintf (buffer,"histo_SMS_%d_%d", i1, i2);
  TH1F* histo_SMS = dynamic_cast<TH1F*> (rootin.FindObjectAny (buffer));
  sprintf (buffer,"histo_SMS_%d_%d_JES_shapeUp", i1, i2);
  TH1F* histo_SMS_JES_shapeUp = dynamic_cast<TH1F*> (rootin.FindObjectAny (buffer));
  sprintf (buffer,"histo_SMS_%d_%d_JES_shapeDown", i1, i2);
  TH1F* histo_SMS_JES_shapeDown = dynamic_cast<TH1F*> (rootin.FindObjectAny (buffer));
  for (int i = 0; i < 5; ++i) 
    {
      Signature& sig = sigs[i];
      sig.id = 500+i;
      sprintf(buffer, "2l2j_%d", i);
      sig.name = buffer;
      sig.observed = int (floor(histo_Data->GetBinContent(i+1)+0.5));
      sig.background = histo_Zbkg->GetBinContent(i+1) +
	histo_OFbkg->GetBinContent(i+1) +
	histo_WZbkg->GetBinContent(i+1) +
	histo_ZZbkg->GetBinContent(i+1) +
	histo_rarebkg->GetBinContent(i+1);

      sig.yield = histo_SMS->GetBinContent(i+1)*xSection/9200.*scaleYield;
      //sig.yield = 0.5*(histo_SMS_JES_shapeUp->GetBinContent(i+1)+histo_SMS_JES_shapeDown->GetBinContent(i+1))*xSection/9200.*scaleYield;
      sig.sigmaBackgroundUncorrelated = 0;
      sig.sigmaBackgroundDD = 0.5*(histo_OFbkg_errOFUp->GetBinContent(i+1) - histo_OFbkg_errOFDown->GetBinContent(i+1));
      sig.sigmaBackgroundJes = 0;
      sig.sigmaBackgroundWZ =  0.5*(histo_WZbkg_errWZUp->GetBinContent(i+1) - histo_WZbkg_errWZDown->GetBinContent(i+1));
      sig.sigmaBackgroundZZ =   0.5*(histo_ZZbkg_errZZUp->GetBinContent(i+1) - histo_ZZbkg_errZZDown->GetBinContent(i+1));
      sig.sigmaBackgroundZGamma = 0.5*(histo_Zbkg_errZUp->GetBinContent(i+1) - histo_Zbkg_errZDown->GetBinContent(i+1));
      sig.sigmaBackgroundRare =   0.5*(histo_rarebkg_errRAREUp->GetBinContent(i+1) - histo_rarebkg_errRAREDown->GetBinContent(i+1));
      sig.sigmaLumi = lumi;
      sig.sigmaYieldUncorrelated = 0;
      sig.sigmaYieldElectron = 0.5*leff;
      sig.sigmaYieldMuon = 0.5*leff;
      sig.sigmaYieldTau = 0;
      sig.sigmaYieldJes = sig.yield > 0 ? 0.5*(histo_SMS_JES_shapeUp->GetBinContent(i+1)-histo_SMS_JES_shapeDown->GetBinContent(i+1))/histo_SMS->GetBinContent(i+1) : 0;
      sig.sigmaYieldTrigger = 0;
      sig.sigmaYieldTheory = 0;
    }

  // dump cards
  sprintf (buffer, "l2j2_wz_%d_%d.txt", m1, m2);
  ofstream outcard(buffer);
  cout << "producing file " << buffer << endl; 
  outcard << "xsec " << m1 << ' ' << m2 << " " << xSection << endl;
  for (int i = 0; i < 5; ++i)
    {
      outcard << "scan " << m1 << ' ' << m2 
	      << ' ' << sigs[i].id
	      << ' ' << sigs[i].yield
	      << ' ' << 0
	      << ' ' << sigs[i].sigmaYieldUncorrelated*sigs[i].yield
	      << ' ' << sigs[i].sigmaYieldMuon*sigs[i].yield
	      << ' ' << sigs[i].sigmaYieldElectron*sigs[i].yield
	      << ' ' << sigs[i].sigmaYieldTau*sigs[i].yield
	      << ' ' << sigs[i].sigmaYieldTrigger*sigs[i].yield
	      << ' ' << sigs[i].sigmaYieldJes*sigs[i].yield
	      << ' ' << sigs[i].sigmaYieldTheory*sigs[i].yield
	      << endl;
    } 
  if (makeData)
    {
      ofstream outdata ("data.txt");
      outdata << "lumi " << intLumi << ' ' << intLumi*sigs[0].sigmaLumi << endl;
      for (int i = 0; i < 5; ++i) 
	{
	  outdata << "data " << sigs[i].id << ' ' << sigs[i].observed
		  << ' ' << sigs[i].background << " 0 0 "
		  << ' ' << histo_WZbkg->GetBinContent(i+1) << ' ' << sigs[i].sigmaBackgroundWZ
		  << ' ' << histo_OFbkg->GetBinContent(i+1) << ' ' << sigs[i].sigmaBackgroundDD
		  << ' ' << histo_Zbkg->GetBinContent(i+1) << ' ' << sigs[i].sigmaBackgroundZGamma
		  << ' ' << histo_ZZbkg->GetBinContent(i+1) << ' ' << sigs[i].sigmaBackgroundZZ
		  << ' ' << histo_rarebkg->GetBinContent(i+1) << ' ' << sigs[i].sigmaBackgroundRare
		  << endl;
	}
    }
}

void convertAll (double scaleYield = 1.)
{
  bool data = false;
  for (int i = 11; i <= 41; ++i)
    {
      for (int j = 1; j <= i-10; ++j)
	{
	  if (data)   makeCards (i, j, scaleYield);
	  else {
	    makeCards (i, j, scaleYield, true);
	    data = true;
	  }
	}
    }
}

void dumpXsection () {
  for (double m = 100; m <= 400; m+=10.) {
    double xsec = getXsection (m, "8TeVc1n2.dat");
    cout << m << " \t " << xsec << endl;
  }
}
