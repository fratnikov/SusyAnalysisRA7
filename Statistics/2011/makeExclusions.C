#include <string>
#include <fstream>
#include <stdio.h>
#include "TH2D.h"
#include "TH1D.h"
#include "TMarker.h"
#include "TFile.h"

#include "ra7StatConverter.C"

const char smoothMode[] = "k3a";


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
    limitFile = "data_2011_lepRPV_4.7fb/combinedModel.out";
    outFile = "exclusions_tanb10_4.7fb.root";
    m0step = 100;
    m0min = 100;
    m0max = 2900;
    m12step = 100;
    m12min = 100;
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
    m12min = 10;
    m12max = 200;
  }
  else {
    cout << "Unknown keyword " << argv[1] << endl
	 << "Accepted: 10 3 0 HRPV LRPV tanb10 chaneu" << endl; 
    return -1;
  }

  int m0Bins = int (floor ((m0max-m0min)/m0step+1.5));
  int m12Bins = int (floor ((m12max-m12min)/m12step+1.5));
  TH2D* yieldHists = new TH2D ("yield", "yield",
			       m0Bins, m0min-0.5*m0step, m0max+0.5*m0step,			  
			       m12Bins, m12min-0.5*m12step, m12max+0.5*m12step);

  for (int im0 = 1; im0 <= m0Bins; ++im0) {
    for (int im12 = 1; im12 <= m12Bins; ++im12) {
      int m0 = int(floor(m0min+(im0-1)*m0step+0.5));
      int m12 = int(floor(m12min+(im12-1)*m12step+0.5));
      Signatures sigs;
      addDataFile (dataDir + "/data.txt", &sigs);
      string mcDataDir = dataDir + "/output";
      string mcDataFile = getFile (mcDataDir, m0, m12);
      if (mcDataFile.empty()) {
	cout << "Can not find MC data for point " << m0 << ':' << m12 << " in dir " << mcDataDir << endl;
	continue;
      }
      readMCFiles (mcDataFile, m0, m12, &sigs);
      StatModelChannels statChannels;
      convertChannels (sigs, statChannels, false);
      for (size_t iChannel = 0; iChannel < statChannels.size(); ++iChannel) {
	yieldHists->Fill (m0, m12, statChannels[iChannel].yield);
	if (m0 == 500 && m12 == 200) {
	  cout << m0 << ':' << m12 << " " << iChannel << " " << statChannels[iChannel].yield << endl;
	}
      }
    }
  }
  TH2D* yieldOrig = new TH2D(*yieldHists);
  yieldOrig->SetName ("yieldOrig");
  repareHoles(yieldHists);
  TH2D* yieldSmooth = new TH2D(*yieldHists);
  yieldSmooth->SetName ("yieldSmooth");



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
  hObsLimit->Write();
  hExpLimit->Write();
  hExpP1Limit->Write();
  hExpM1Limit->Write();
  hExpP2Limit->Write();
  hExpM2Limit->Write();

  yieldSmooth->Write();
  hObsLimitSmooth->Write();
  hExpLimitSmooth->Write();
  hExpP1LimitSmooth->Write();
  hExpM1LimitSmooth->Write();
  hExpP2LimitSmooth->Write();
  hExpM2LimitSmooth->Write();

  return 0;
}

