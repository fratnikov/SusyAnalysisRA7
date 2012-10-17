#include <string>
#include <fstream>
#include <stdio.h>
#include "TH2D.h"
#include "TH1D.h"
#include "TMarker.h"
#include "TFile.h"

#include "ra7StatConverter.C"
//#include "fixHist.C"

const char smoothMode[] = "k3a";

double channelNumber (const string& ch) {
  if (ch.length() < 3 || ch[0] != 'c' || ch[1]!='h') return 0;
  return atof (ch.c_str()+2);
}

void repareHoles (TH2D* hist) {
  for (int iy = 1; iy <= hist->GetNbinsY(); ++iy) {
    for (int ix = 1; ix <= hist->GetNbinsX(); ++ix) {
      if (hist->GetBinContent (ix,iy) <=0) {
	if (ix > 1 && ix < hist->GetNbinsX() &&
	    hist->GetBinContent (ix-1,iy) >1e-40 &&
	    hist->GetBinContent (ix+1,iy) >1e-40) {
	  hist->SetBinContent (ix,iy, 0.5*(hist->GetBinContent (ix-1,iy)+hist->GetBinContent (ix+1,iy)));
	}
      }
    }
  }

  for (int iy = 1; iy <= hist->GetNbinsY(); ++iy) {
    for (int ix = 1; ix <= hist->GetNbinsX(); ++ix) {
      if (hist->GetBinContent (ix,iy) <=0) {
	if (iy > 1 && iy < hist->GetNbinsY() &&
	    hist->GetBinContent (ix,iy-1) >1e-40 &&
	    hist->GetBinContent (ix,iy+1) >1e-40) {
	  hist->SetBinContent (ix,iy, 0.5*(hist->GetBinContent (ix,iy-1)+hist->GetBinContent (ix,iy+1)));
	}
      }
    }
  }
  bool thisDone = true;
  while (thisDone) {
    thisDone = false;
    for (int iy = 1; !thisDone && iy <= hist->GetNbinsY(); ++iy) {
      for (int ix = 1; !thisDone && ix <= hist->GetNbinsX(); ++ix) {
	if (hist->GetBinContent (ix,iy) <=0) {
	  if (ix > 1 && iy > 1) {
	    if (hist->GetBinContent (ix-1,iy-1) > 1e-40 &&
		hist->GetBinContent (ix,iy-1) > 1e-40 &&
		hist->GetBinContent (ix-1,iy) > 1e-40) {
	      hist->SetBinContent (ix,iy, 
				   hist->GetBinContent (ix,iy-1)*
				   hist->GetBinContent (ix-1,iy)/
				   hist->GetBinContent (ix-1,iy-1));
	      thisDone = true;
	      break;
	    }
	  }
	}
      }
    }
  }
}

double getXsection (double x, ifstream& input) {
  input.seekg(0);
  double xPrev = -1;
  double yPrev = -1;
  while (input) {
    double xThis, yThis;
    input >> xThis >> yThis;
    if (!input) {
      cerr << "getXsection-> error reading stream" << endl;
      return 0;
    }
    if (xThis >= x) {
      if (xPrev < 0) return yThis;
      double y = exp (log(yPrev) + (log(yThis)-log(yPrev)) * (x-xPrev)/(xThis-xPrev));
      return y/1000.;
    }
    xPrev = xThis;
    yPrev = yThis;
  }
}

int main (int argc, char* argv[]) {
  if (argc < 2) {
    cout << argv[0] << " <type> [xSections file] [used best channels #]" << endl;
    return 0;
  }

  string dataDir = "";
  string limitFile = "";
  string outFile = "";
  double m0step = 0;
  double m0min = 0;
  double m0max = 0;
  double m12step = 0;
  double m12min = 0;
  double m12max = 0;
  ifstream* xSections = 0;
  int nChannels = 0;
  if (argc >= 3 && !string (argv[2]).empty()) { // scale yields
    xSections = new ifstream (argv[2]);
  }
  if (argc >= 4) { // # channels
    nChannels = atoi (argv[3]);
  }

  if (string(argv[1]) == "chaneu") {
    dataDir = "EWKino";
    limitFile = "EWKino/combinedModel.out";
    outFile = "EWKino_9.2fb.root";
    m0step = 25;
    m0min = 100;
    m0max = 1000;
    m12step = 25;
    m12min = 0;
    m12max = 1000;
  }
  else if (string(argv[1]) == "TChiSlepSnu") {
    m0step = 50;
    m0min = 100;
    m0max = 1000;
    m12step = 50;
    m12min = 0;
    m12max = 1000;
  }
  else if (string(argv[1]) == "TChiWZ.2l2j") {
    m0step = 10;
    m0min = 100;
    m0max = 350;
    m12step = 10;
    m12min = 0;
    m12max = 250;
  }
  else if (string(argv[1]) == "TChiWZ.ru") {
    m0step = 50;
    m0min = 150;
    m0max = 450;
    m12step = 50;
    m12min = 0;
    m12max = 350;
  }
  else if (string(argv[1]) == "TChiWZ.2l2jru") {
    m0step = 50;
    m0min = 150;
    m0max = 350;
    m12step = 50;
    m12min = 0;
    m12max = 250;
  }
  else if (string(argv[1]) == "TSlepSlep") {
    dataDir = "TSlepSlep";
    limitFile = "TSlepSlep/combinedModel.out";
    outFile = "TSlepSlep_9.2fb.root";
    m0step = 25;
    m0min = 100;
    m0max = 300;
    m12step = 25;
    m12min = 0;
    m12max = 300;
  }
  else if (string(argv[1]) == "TChipmSlepSnu") {
    dataDir = "TChipmSlepSnu";
    limitFile = "TChipmSlepSnu/combinedModel.out";
    outFile = "TChipmSlepSnu_9.2fb.root";
    m0step = 50;
    m0min = 100;
    m0max = 450;
    m12step = 50;
    m12min = 0;
    m12max = 450;
  }
  else {
    cout << "Unknown keyword " << argv[1] << endl
	 << "Accepted: chaneu TChiSlepSnu TChipmSlepSnu TSlepSlep TChiWZ.2l2j TChiWZ.2l2jru TChiWZ.ru" << endl; 
    return -1;
  }
  dataDir = '.';
  limitFile = dataDir + "/combinedModel.out";
  outFile = "Exclusion.root";

  int m0Bins = int (floor ((m0max-m0min)/m0step+1.5));
  int m12Bins = int (floor ((m12max-m12min)/m12step+1.5));
  TH2D* yieldHists = new TH2D ("yield", "yield",
			       m0Bins, m0min-0.5*m0step, m0max+0.5*m0step,			  
			       m12Bins, m12min-0.5*m12step, m12max+0.5*m12step);
  cout << "book hist: " << m0Bins<<':'<<m0min-0.5*m0step<<':'<<m0max+0.5*m0step
       << " : " <<m12Bins <<':'<<m12min-0.5*m12step <<':'<<m12max+0.5*m12step << endl;

  TH2D* processXSection = new TH2D(*yieldHists);
  processXSection->SetName ("processXSection");
  processXSection->SetTitle ("process total XSection [pb]");
  
  TH2D* mainChannel = new TH2D(*yieldHists);
  mainChannel->SetName ("mainChannel");
  mainChannel->SetTitle ("mainChannel");
  mainChannel->Reset();
  
  TH2D* main2Channel = new TH2D(*yieldHists);
  main2Channel->SetName ("main2Channel");
  main2Channel->SetTitle ("main2Channel");
  main2Channel->Reset();
  
  TH2D* main3Channel = new TH2D(*yieldHists);
  main3Channel->SetName ("main3Channel");
  main3Channel->SetTitle ("main3Channel");
  main3Channel->Reset();
  
  TH2D* main4Channel = new TH2D(*yieldHists);
  main4Channel->SetName ("main4Channel");
  main4Channel->SetTitle ("main4Channel");
  main4Channel->Reset();
  
  TH2D* main5Channel = new TH2D(*yieldHists);
  main5Channel->SetName ("main5Channel");
  main5Channel->SetTitle ("main5Channel");
  main5Channel->Reset();
  
  TH2D* secondChannel = new TH2D(*yieldHists);
  secondChannel->SetName ("secondChannel");
  secondChannel->SetTitle ("secondChannel");
  secondChannel->Reset();
  
  TH2D* ratioChannel = new TH2D(*yieldHists);
  ratioChannel->SetName ("ratioChannel");
  ratioChannel->SetTitle ("ratioChannel");
  ratioChannel->Reset();
  
  TH2D* ratio2Channel = new TH2D(*yieldHists);
  ratio2Channel->SetName ("ratio2Channel");
  ratio2Channel->SetTitle ("ratio2Channel");
  ratio2Channel->Reset();
  
  TH2D* ratio3Channel = new TH2D(*yieldHists);
  ratio3Channel->SetName ("ratio3Channel");
  ratio3Channel->SetTitle ("ratio3Channel");
  ratio3Channel->Reset();
  
  TH2D* ratio4Channel = new TH2D(*yieldHists);
  ratio4Channel->SetName ("ratio4Channel");
  ratio4Channel->SetTitle ("ratio4Channel");
  ratio4Channel->Reset();
  
  TH2D* ratio5Channel = new TH2D(*yieldHists);
  ratio5Channel->SetName ("ratio5Channel");
  ratio5Channel->SetTitle ("ratio5Channel");
  ratio5Channel->Reset();
  

  for (int im0 = 1; im0 <= m0Bins; ++im0) {
    int m0 = int(floor(m0min+(im0-1)*m0step+0.5));
    double xsecScale = 1;
    double trueXsec = 1;
    if (xSections) {
      trueXsec = getXsection (m0, *xSections);
      cout << "point " << m0 << " xSection=" << trueXsec << endl;
    }
    for (int im12 = 1; im12 <= m12Bins; ++im12) {
      int m12 = int(floor(m12min+(im12-1)*m12step+0.5));
      if (m12 >= m0) continue;
      Signatures sigs;
      addDataFiles (dataDir + "/dataAll.txt", &sigs);
      if (!readScanFiles (dataDir + "/scanAll.txt", m0, m12, &sigs, xsecScale)) {
	cerr << "Can not find file "<<m0<<':'<<m12<<" in dir: " << endl;
	continue;
      }
      double xSec = totalXSection (dataDir + "/scanAll.txt", m0, m12);
      if (fabs(xSec-1.)<0.001) xsecScale = trueXsec/ xSec; 
      processXSection->Fill (m0, m12, xSec*xsecScale);
      cout << "Fill xSection " << m0 << ':' << m12 << " " << xSec*xsecScale << endl;
 

      sort (sigs.begin(), sigs.end(), lessQuickLimit); 

      mainChannel->Fill (m0, m12, sigs[0].id);
      if (sigs.size() > 1) {
	main2Channel->Fill (m0, m12, sigs[1].id);
	ratio2Channel->Fill (m0, m12, sigs[0].getExpectedLimit ()/sigs[1].getExpectedLimit ());
	if (sigs.size() > 2) {
	  main3Channel->Fill (m0, m12, sigs[2].id);
	  ratio3Channel->Fill (m0, m12, sigs[0].getExpectedLimit ()/sigs[2].getExpectedLimit ());
	  if (sigs.size() > 3) {
	    main4Channel->Fill (m0, m12, sigs[3].id);
	    ratio4Channel->Fill (m0, m12, sigs[0].getExpectedLimit ()/sigs[3].getExpectedLimit ());
	    if (sigs.size() > 4) {
	      main5Channel->Fill (m0, m12, sigs[4].id);
	      ratio5Channel->Fill (m0, m12, sigs[0].getExpectedLimit ()/sigs[4].getExpectedLimit ());
	    }
	  }
	}
      }
//        for (int ii = 0; ii < sigs.size(); ++ii) {
//  	if (sigs[ii].id > 180) {
//  	  cout << "mass " << m0<<':'<<m12<<' '<<sigs[ii].id<<' '<<sigs[ii].name<<" -> "<<ii<<endl;
//  	}
//        }

      StatModelChannels statChannels;
      convertChannels (sigs, statChannels, 0, false);

      if (nChannels > 0 && nChannels < sigs.size()) {
	statChannels.erase (statChannels.begin()+nChannels,statChannels.end()); 
      }
      
      double sumYield = 0;
      for (size_t iChannel = 0; iChannel < statChannels.size(); ++iChannel) {
	yieldHists->Fill (m0, m12, statChannels[iChannel].yield);
	if (m0 == 300 && m12 == 0) {
	  sumYield += statChannels[iChannel].yield;
	  cout << iChannel << ':'<< statChannels[iChannel].id << " yield: " << statChannels[iChannel].yield << ':' << sumYield << endl;
	}
      }
    }
  }

  TH2D* yieldOrig = new TH2D(*yieldHists);
  yieldOrig->SetName ("yieldOrig");
  repareHoles(yieldHists);
  TH2D* processXSectionOrig = new TH2D(*processXSection);
  processXSectionOrig->SetName ("processXSectionOrig");
  repareHoles(processXSection);
  TH2D* yieldSmooth = new TH2D(*yieldHists);
  yieldSmooth->SetName ("yieldSmooth");
  //yieldSmooth->Smooth(1,smoothMode);

  TH2D* hObsLimit = new TH2D("hObsLimit", dataDir.c_str(), 
			     m0Bins, m0min-0.5*m0step, m0max+0.5*m0step,			  
			     m12Bins, m12min-0.5*m12step, m12max+0.5*m12step);
  hObsLimit->GetXaxis()->SetTitle("m_{0}");
  hObsLimit->GetYaxis()->SetTitle("m_{1/2}");

  TH2D* hExpLimit = new TH2D("hExpLimit", dataDir.c_str(), 
			     m0Bins, m0min-0.5*m0step, m0max+0.5*m0step,			  
			     m12Bins, m12min-0.5*m12step, m12max+0.5*m12step);
  hExpLimit->GetXaxis()->SetTitle("m_{0}");
  hExpLimit->GetYaxis()->SetTitle("m_{1/2}");

  TH2D* hExpP1Limit = new TH2D("hExpP1Limit", dataDir.c_str(), 
			     m0Bins, m0min-0.5*m0step, m0max+0.5*m0step,			  
			     m12Bins, m12min-0.5*m12step, m12max+0.5*m12step);
  hExpP1Limit->GetXaxis()->SetTitle("m_{0}");
  hExpP1Limit->GetYaxis()->SetTitle("m_{1/2}");

  TH2D* hExpM1Limit = new TH2D("hExpM1Limit", dataDir.c_str(), 
			     m0Bins, m0min-0.5*m0step, m0max+0.5*m0step,			  
			     m12Bins, m12min-0.5*m12step, m12max+0.5*m12step);
  hExpM1Limit->GetXaxis()->SetTitle("m_{0}");
  hExpM1Limit->GetYaxis()->SetTitle("m_{1/2}");

  TH2D* hExpP2Limit = new TH2D("hExpP2Limit", dataDir.c_str(), 
			       m0Bins, m0min-0.5*m0step, m0max+0.5*m0step,
			       m12Bins, m12min-0.5*m12step, m12max+0.5*m12step);
  hExpP2Limit->GetXaxis()->SetTitle("m_{0}");
  hExpP2Limit->GetYaxis()->SetTitle("m_{1/2}");

  TH2D* hExpM2Limit = new TH2D("hExpM2Limit", dataDir.c_str(), 
			       m0Bins, m0min-0.5*m0step, m0max+0.5*m0step,
			       m12Bins, m12min-0.5*m12step, m12max+0.5*m12step);
  hExpM2Limit->GetXaxis()->SetTitle("m_{0}");
  hExpM2Limit->GetYaxis()->SetTitle("m_{1/2}");

  ifstream in (limitFile.c_str());
  while (in) {
    string line;
    getline (in, line);
    if (!in) break;
    int m0;
    int m12;
    int tanb;
    float limit[6];
    if (line[0] == '#') continue;
    sscanf (line.c_str(),"%d:%d cls: %f %f ( %f : %f ) ( %f : %f )",
	    &m0, &m12, limit, limit+1, limit+2, limit+3, limit+4, limit+5); 

    hObsLimit->Fill (m0, m12, limit[0]);
    hExpLimit->Fill (m0, m12, limit[1]);
    hExpP1Limit->Fill (m0, m12, limit[2]);
    hExpM1Limit->Fill (m0, m12, limit[3]);
    hExpP2Limit->Fill (m0, m12, limit[4]);
    hExpM2Limit->Fill (m0, m12, limit[5]);

    //cout << "fill limits : " << m0<<':'<<m12<<' '<<limit[0]<<' '<<limit[1]<<' '<<limit[2]<<' '<<limit[3]<<' '<<limit[4]<<' '<<limit[5]<<endl;
  }

  
  repareHoles(hObsLimit);  
  TH2D* hObsLimitSmooth = new TH2D (*hObsLimit);
  hObsLimitSmooth->SetName ("hObsLimitSmooth");
  hObsLimitSmooth->Smooth(1,smoothMode);
  hObsLimitSmooth->Divide (yieldSmooth);

  TH2D* hObsLimitPlain = new TH2D (*hObsLimit);
  hObsLimitPlain->SetName ("hObsLimitPlain");
  hObsLimitPlain->Divide (yieldSmooth);

  repareHoles(hExpLimit);
  TH2D* hExpLimitSmooth = new TH2D (*hExpLimit);
  hExpLimitSmooth->SetName ("hExpLimitSmooth");
  hExpLimitSmooth->Smooth(1,smoothMode);
  hExpLimitSmooth->Divide (yieldSmooth);

  repareHoles(hExpP1Limit);
  TH2D* hExpP1LimitSmooth = new TH2D (*hExpP1Limit);
  hExpP1LimitSmooth->SetName ("hExpP1LimitSmooth");
  hExpP1LimitSmooth->Smooth(1,smoothMode);
  hExpP1LimitSmooth->Divide (yieldSmooth);

  repareHoles(hExpM1Limit);
  TH2D* hExpM1LimitSmooth = new TH2D (*hExpM1Limit);
  hExpM1LimitSmooth->SetName ("hExpM1LimitSmooth");
  hExpM1LimitSmooth->Smooth(1,smoothMode);
  hExpM1LimitSmooth->Divide (yieldSmooth);

  repareHoles(hExpP2Limit);
  TH2D* hExpP2LimitSmooth = new TH2D (*hExpP2Limit);
  hExpP2LimitSmooth->SetName ("hExpP2LimitSmooth");
  hExpP2LimitSmooth->Smooth(1,smoothMode);
  hExpP2LimitSmooth->Divide (yieldSmooth);

  repareHoles(hExpM2Limit);
  TH2D* hExpM2LimitSmooth = new TH2D (*hExpM2Limit);
  hExpM2LimitSmooth->SetName ("hExpM2LimitSmooth");
  hExpM2LimitSmooth->Smooth(1,smoothMode);
  hExpM2LimitSmooth->Divide (yieldSmooth);

  TFile f (outFile.c_str(), "RECREATE");
  yieldOrig->Write();
  yieldHists->Write();
  processXSection->Write();
  processXSectionOrig->Write();
  mainChannel->Write();
  main2Channel->Write();
  main3Channel->Write();
  main4Channel->Write();
  main5Channel->Write();
  ratioChannel->Write();
  ratio2Channel->Write();
  ratio3Channel->Write();
  ratio4Channel->Write();
  ratio5Channel->Write();
  hObsLimit->Write();
  hExpLimit->Write();
  hExpP1Limit->Write();
  hExpM1Limit->Write();
  hExpP2Limit->Write();
  hExpM2Limit->Write();

  yieldSmooth->Write();
  hObsLimitSmooth->Write();
  hObsLimitPlain->Write();
  hExpLimitSmooth->Write();
  hExpP1LimitSmooth->Write();
  hExpM1LimitSmooth->Write();
  hExpP2LimitSmooth->Write();
  hExpM2LimitSmooth->Write();

  cout << "Output file produced: " << outFile << endl;

  return 0;
}

