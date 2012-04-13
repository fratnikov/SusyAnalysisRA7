#include <string>
#include <fstream>
#include <stdio.h>
#include "TH2D.h"
#include "TH1D.h"
#include "TMarker.h"
#include "TFile.h"

#include "ra7StatConverter.C"

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
	    hist->GetBinContent (ix-1,iy) >0 &&
	    hist->GetBinContent (ix+1,iy) >0) {
	  hist->SetBinContent (ix,iy, 0.5*(hist->GetBinContent (ix-1,iy)+hist->GetBinContent (ix+1,iy)));
	}
      }
    }
  }

  for (int iy = 1; iy <= hist->GetNbinsY(); ++iy) {
    for (int ix = 1; ix <= hist->GetNbinsX(); ++ix) {
      if (hist->GetBinContent (ix,iy) <=0) {
	if (iy > 1 && iy < hist->GetNbinsY() &&
	    hist->GetBinContent (ix,iy-1) >0 &&
	    hist->GetBinContent (ix,iy+1) >0) {
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
	    if (hist->GetBinContent (ix-1,iy-1) > 0 &&
		hist->GetBinContent (ix,iy-1) > 0 &&
		hist->GetBinContent (ix-1,iy) > 0) {
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
    if (xThis > x) {
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
    cout << argv[0] << "" << endl;
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
  if (argc >= 3) { // scale yields
    xSections = new ifstream (argv[2]);
    if (argc >= 4) { // # channels
      nChannels = atoi (argv[3]);
    }
  }
  if (string(argv[1]) == "10") {
    dataDir = "data_2011_tanb10_2.1fb";
    limitFile = "data_2011_tanb10_2.1fb/combinedModel.out";
    outFile = "exclusions_tanb10_2.1fb.root";
    m0step = 20;
    m0min = 40;
    m0max = 380;
    m12step = 20;
    m12min = 160;
    m12max = 380;
  }
  else if (string(argv[1]) == "3") {
    dataDir = "data_2011_tanb3_2.1fb";
    limitFile = "data_2011_tanb3_2.1fb/combinedModel.out";
    outFile = "exclusions_tanb3_2.1fb.root";
    m0step = 25;
    m0min = 50;
    m0max = 300;
    m12step = 25;
    m12min = 150;
    m12max = 400;
  }
  else if (string(argv[1]) == "0") {
    dataDir = "data_2011_coNLSP_4.7fb";
    limitFile = "data_2011_coNLSP_4.7fb/combinedModel.out";
    outFile = "exclusions_coNLSP_4.7fb.root";
    m0step = 25;
    m0min = 300;
    m0max = 900;
    m12step = 50;
    m12min = 1550;
    m12max = 2000;
  }
  else if (string(argv[1]) == "HRPV") {
    dataDir = "data_2011_hadRPV_4.7fb";
    limitFile = "data_2011_hadRPV_4.7fb/combinedModel.out";
    outFile = "exclusions_hadRPV_4.7fb.root";
    m0step = 100;
    m0min = 900;
    m0max = 2500;
    m12step = 50;
    m12min = 550;
    m12max = 2000;
  }
  else if (string(argv[1]) == "LRPV") {
    dataDir = "data_2011_lepRPV_4.7fb";
    limitFile = "data_2011_lepRPV_4.7fb/combinedModel.out";
    outFile = "exclusions_lepRPV_4.7fb.root";
    m0step = 100;
    m0min = 1000;
    m0max = 2100;
    m12step = 100;
    m12min = 600;
    m12max = 2000;
  }
  else if (string(argv[1]) == "tanb10") {
    dataDir = "data_2011_tanb10_4.7fb";
    limitFile = "data_2011_tanb10_4.7fb/combinedModel.out";
    outFile = "exclusions_tanb10_4.7fb.root";
    m0step = 40;
    m0min = 100;
    m0max = 2980;
    m12step = 20;
    m12min = 100;
    m12max = 400;
  }
  else if (string(argv[1]) == "tanb10_2") {
    dataDir = "data_2011_tanb10_4.7fb";
    limitFile = "data_2011_tanb10_4.7fb/combinedModel.out";
    outFile = "exclusions_tanb10_2_4.7fb.root";
    m0step = 20;
    m0min = 100;
    m0max = 2980;
    m12step = 20;
    m12min = 100;
    m12max = 400;
  }
  else if (string(argv[1]) == "tanb40") {
    dataDir = "data_2011_tanb40_4.7fb";
    limitFile = "data_2011_tanb40_4.7fb/combinedModel";
    outFile = "exclusions_tanb40_4.7fb.root";
    m0step = 40;
    m0min = 300;
    m0max = 2980;
    m12step = 40;
    m12min = 480;
    m12max = 1000;
  }
  else if (string(argv[1]) == "chaneu") {
    dataDir = "data_2011_chaneu_4.7fb";
    limitFile = "data_2011_chaneu_4.7fb/combinedModel.out";
    outFile = "exclusions_chaneu_4.7fb.root";
    m0step = 10;
    m0min = 100;
    m0max = 500;
    m12step = 10;
    m12min = 0;
    m12max = 480;
  }
  else if (string(argv[1]) == "TChiSlepSnu") {
    dataDir = "data_2011_TChiSlepSnu_4.7fb";
    limitFile = "data_2011_chaneu_4.7fb/combinedModel.out";
    outFile = "exclusions_TChiSlepSnu_4.7fb.root";
    m0step = 10;
    m0min = 100;
    m0max = 500;
    m12step = 10;
    m12min = 0;
    m12max = 480;
  }
  else if (string(argv[1]) == "TChiSlepSlep") {
    dataDir = "data_2011_TChiSlepSlep_4.7fb";
    limitFile = "data_2011_TChiSlepSlep_4.7fb/combinedModel.out";
    outFile = "exclusions_TChiSlepSlep_4.7fb.root";
    m0step = 10;
    m0min = 100;
    m0max = 500;
    m12step = 10;
    m12min = 0;
    m12max = 480;
  }
  else if (string(argv[1]) == "TChizz") {
    dataDir = "data_2011_chizz_4.7fb";
    limitFile = "data_2011_chizz_4.7fb/combinedModel.out";
    outFile = "exclusions_TChizz_4.7fb.root";
    m0step = 25;
    m0min = 100;
    m0max = 500;
    m12step = 25;
    m12min = 0;
    m12max = 400;
  }
  else if (string(argv[1]) == "TChiwz") {
    dataDir = "data_2011_chiwz_4.7fb";
    limitFile = "data_2011_chiwz_4.7fb/combinedModel.out";
    outFile = "exclusions_TChiwz_4.7fb.root";
    m0step = 25;
    m0min = 100;
    m0max = 500;
    m12step = 25;
    m12min = 0;
    m12max = 400;
  }
  else {
    cout << "Unknown keyword " << argv[1] << endl
	 << "Accepted: 10 3 0 HRPV LRPV tanb10 tanb40 chaneu TChiSlepSnu TChiSlepSlep TChizz TChiwz" << endl; 
    return -1;
  }

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
    if (xSections) {
      xsecScale = getXsection (m0, *xSections);
      cout << "point " << m0 << " xSection=" << xsecScale << endl;
    }
    for (int im12 = 1; im12 <= m12Bins; ++im12) {
      int m12 = int(floor(m12min+(im12-1)*m12step+0.5));
      Signatures sigs;
      addDataFile (dataDir + "/data.txt", &sigs);
      string mcDataDir = dataDir + "/output";
      string mcDataFile = getFile (mcDataDir, m0, m12);
      if (mcDataFile.empty()) {
	cout << "Can not find MC data for point " << m0 << ':' << m12 << " in dir " << mcDataDir << endl;
	continue;
      }
      readMCFiles (mcDataFile, m0, m12, &sigs, xsecScale);
      sort (sigs.begin(), sigs.end(), lessExpectedLimit); 

      mainChannel->Fill (m0, m12, channelNumber (sigs[0].name));
      if (sigs.size() > 1) {
	main2Channel->Fill (m0, m12, channelNumber (sigs[1].name));
	ratio2Channel->Fill (m0, m12, sigs[0].getExpectedLimit ()/sigs[1].getExpectedLimit ());
	if (sigs.size() > 2) {
	  main3Channel->Fill (m0, m12, channelNumber (sigs[2].name));
	  ratio3Channel->Fill (m0, m12, sigs[0].getExpectedLimit ()/sigs[2].getExpectedLimit ());
	  if (sigs.size() > 3) {
	    main4Channel->Fill (m0, m12, channelNumber (sigs[3].name));
	    ratio4Channel->Fill (m0, m12, sigs[0].getExpectedLimit ()/sigs[3].getExpectedLimit ());
	    if (sigs.size() > 4) {
	      main5Channel->Fill (m0, m12, channelNumber (sigs[4].name));
	      ratio5Channel->Fill (m0, m12, sigs[0].getExpectedLimit ()/sigs[4].getExpectedLimit ());
	    }
	  }
	}
      }

      if (nChannels > 0 && nChannels < sigs.size()) {
	sigs.erase (sigs.begin()+nChannels,sigs.end()); 
      }

      StatModelChannels statChannels;
      convertChannels (sigs, statChannels, false);
      
      for (size_t iChannel = 0; iChannel < statChannels.size(); ++iChannel) {
	yieldHists->Fill (m0, m12, statChannels[iChannel].yield);
	if (m0 == 500 && m12 == 200) {
	  cout << m0 << ':' << m12 << " " << iChannel << " " << statChannels[iChannel].yield << endl;
	}
      }
      double xSec = totalXSection (mcDataFile, m0, m12) * xsecScale;
      processXSection->Fill (m0, m12, xSec);
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

