#include <sstream>
#include <string>
#include <iomanip>
#include "ExclusionPlot.hh"
#include "tdrstyle.C"


#include "TH1.h"
#include "TH2.h"
#include "TFile.h"
#include "TStyle.h"
#include "TLatex.h"
#include "TCanvas.h"
#include "TMarker.h"
#include <vector>
#include "TMath.h"

void RA7_mSUGRA_ExclusionLimit_plot1(){

  setTDRStyle();
  

  gStyle->SetPalette(1);

  //get yield plot
  //  hev = yieldPlot(mSuGraFile,mSuGraDir, mSuGraHist);
  //setPlottingStyle(*hev);

  // setPlottingStyle(*exclusionPlot,lineStyle);

  Int_t tanBeta = 3;
   
  /* TH1F* First = getHisto_1d("./","ExclusionLimit","Significance_NLO_expected_tanBeta50.root");
  setPlottingStyle(*First);
  First->SetLineStyle(1);
  First->SetLineWidth(1);

  TH1F* Second = getHisto_1d("./","ExclusionLimit","Significance_NLO_observed_tanBeta50.root"); 
  Second->SetLineStyle(2);
  Second->SetLineWidth(1);
  Second->SetLineColor(kRed);
 
  
   TH1F* Third = getHisto_1d("./","ExclusionLimit","Significance_LO_observed_tanBeta50.root");
  Third->SetLineStyle(1);
  Third->SetLineWidth(3);
  Third->SetLineColor(kGreen+2);
 
  
  exclusionPlots.push_back(First);
    exclusionPlots.push_back(Second);
    exclusionPlots.push_back(Third);*/
  
  
  CommandMSUGRA("35pb_expected_11.root",tanBeta);


}



void CommandMSUGRA(TString plotName_,Int_t tanBeta_){
  
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetPalette(1); 
  gStyle->SetTextFont(42);
  
  //convert tanb value to string
  std::stringstream tmp;
  tmp << tanBeta_;
  TString tanb( tmp.str() );
  
  
  // Output file
  cout << " create " << plotName_ << endl;
  TFile* output = new TFile( plotName_, "RECREATE" );
  if ( !output || output->IsZombie() ) { std::cout << " zombie alarm output is a zombie " << std::endl; }
  

  //set old exclusion Limits
  TGraph* LEP_ch = set_lep_ch(tanBeta_);
  TGraph* LEP_sl = set_lep_sl(tanBeta_);//slepton curve
  TGraph* TEV_sg_cdf = set_tev_sg_cdf(tanBeta_);//squark gluino cdf
  TGraph* TEV_sg_d0 = set_tev_sg_d0(tanBeta_);//squark gluino d0
  //  TGraph* TEV_tlp_cdf = set_tev_tlp_cdf(tanBeta_);//trilepton cdf
  //  TGraph* TEV_tlp_d0 = set_tev_tlp_d0(tanBeta_);//trilepton d0
  TGraph* stau = set_tev_stau(tanBeta_);//stau 

  TGraph* TEV_sn_d0_1 = set_sneutrino_d0_1(tanBeta_);
  TGraph* TEV_sn_d0_2 = set_sneutrino_d0_2(tanBeta_);

  //constant ssqquark and gluino lines
  TF1* lnsq[4];
  TF1* lngl[4];
  
  TLatex* sq_text[4];
  TLatex* gl_text[4];

  for(int i = 0; i < 4; i++){
    lnsq[i] = constant_squark(tanBeta_,i);
    sq_text[i] = constant_squark_text(i,*lnsq[i],tanBeta_);
    lngl[i] = constant_gluino(tanBeta_,i);
    gl_text[i] = constant_gluino_text(i,*lngl[i]);
  }
  
  //Legends
  TLegend* legst = makeStauLegend(0.05,tanBeta_);
  TLegend* legexp = makeExpLegend( *TEV_sg_cdf,*TEV_sg_d0,*LEP_ch,*LEP_sl,*TEV_sn_d0_1,0.04,tanBeta_);
  
 
  //make Canvas
  TCanvas* cvsSys = new TCanvas("cvsnm","cvsnm",0,0,1200,900);
  gStyle->SetOptTitle(0);
  cvsSys->SetFillColor(0);
  cvsSys->Range(0,150,300, 320);
  //  cvsSys->Range(-120.5298,26.16437,736.0927,500);
  //  cvsSys->Range(-50.5298,26.16437,736.0927,500);
  cvsSys->SetFillColor(0);
  cvsSys->SetBorderMode(0);
  cvsSys->GetPad(0)->SetBorderSize(2);
  cvsSys->GetPad(0)->SetTopMargin(0.08);
  cvsSys->GetPad(0)->SetBottomMargin(0.17);
  cvsSys->GetPad(0)->SetLeftMargin(0.15);
  cvsSys->GetPad(0)->SetRightMargin(0.05);

  cvsSys->SetTitle("tan#beta="+tanb);
 
  output->cd();
  
  //and now
  //the exclusion limits
  TGraphErrors* First ;
  TGraphErrors* Second;
  TGraphErrors* Third;

  if(tanBeta_ == 3){
    First = getObserved_NLO_tanBeta3();
    Second = getExpected_NLO_tanBeta3();
    Third = getLO_tanBeta3();
  }
  if(tanBeta_ == 10){
    First = getObserved_NLO_tanBeta10();
    Second = getExpected_NLO_tanBeta10();
    Third = getLO_tanBeta10();
  }
  if(tanBeta_ == 50){
    First = getObserved_NLO_tanBeta50();
    Second = getExpected_NLO_tanBeta50();
    Third = getLO_tanBeta50();
  }

//   First->SetMarkerColor(kWhite);
//   First->GetXaxis()->SetRangeUser(2.,500.);
//   First->GetYaxis()->SetRangeUser(80,500);
//   if(tanBeta_ == 50) First->GetXaxis()->SetRangeUser(200,500);
//   First->GetXaxis()->SetTitle("m_{0} (GeV)");
//   First->GetYaxis()->SetTitle("m_{1/2} (GeV)");
//   First->GetYaxis()->SetTitleOffset(0.8);

  double m0min = 0;
  if (tanBeta_ == 50) m0min=200;
  TH2D* hist = new TH2D("h","h",100,0,300,100,150,400);
  hist->Draw();  
  hist->GetXaxis()->SetTitle("m_{0}  (GeV/c^{2})   ");
  hist->GetYaxis()->SetTitle("m_{1/2}  (GeV/c^{2})   ");
  hist->GetYaxis()->SetTitleOffset(1.1);
  hist->GetXaxis()->SetTitleOffset(0.95);

  hist->GetXaxis()->SetNdivisions(506);
  //  if (tanBeta_ == 50)  hist->GetXaxis()->SetNdivisions(504);
  hist->GetYaxis()->SetNdivisions(506);

  int col[]={2,3,4};

  TSpline3 *sFirst = new TSpline3("sFirst",First);
  sFirst->SetLineColor(kBlack);
  sFirst->SetLineWidth(3);

  TSpline3 *sSecond = new TSpline3("sSecond",Second);
  sSecond->SetLineColor(kBlack);
  sSecond->SetLineStyle(2);
  sSecond->SetLineWidth(2);
  
  TSpline3 *sThird = new TSpline3("sThird",Third);
  sThird->SetLineColor(kGreen+2);
  sThird->SetLineStyle(4);
  sThird->SetLineWidth(3);


 


  Double_t *dum = 0;
   TPolyLine *NLO_exp = new TPolyLine(62,dum,dum,"");
   NLO_exp->SetFillColor(8);
   NLO_exp->SetLineColor(kBlack);
   NLO_exp->SetLineStyle(2);
   NLO_exp->SetLineWidth(3);

   NLO_exp->SetPoint(0,-0.1150955,225);
   NLO_exp->SetPoint(1,-0.1150955,225);
   NLO_exp->SetPoint(2,4.718867,225);
   NLO_exp->SetPoint(3,9.783018,225);
   NLO_exp->SetPoint(4,41.77924,240.4901);
   NLO_exp->SetPoint(5,71.70377,259.5891);
   NLO_exp->SetPoint(6,80.68113,264.2921);
   NLO_exp->SetPoint(7,86.66604,267.0149);
   NLO_exp->SetPoint(8,91.73019,268.5);
   NLO_exp->SetPoint(9,103.8585,270.5);
   NLO_exp->SetPoint(10,118.9717,267.5297);
   NLO_exp->SetPoint(11,122.5434,252.5792);

   NLO_exp->SetPoint(12,115.8434,230.3713);
   NLO_exp->SetPoint(13,110,220);
   NLO_exp->SetPoint(14,97.72264,201.4109);
   NLO_exp->SetPoint(15,73.,170);
   NLO_exp->SetPoint(16,75,170);
   NLO_exp->SetPoint(17,123.75,222.6);
   NLO_exp->SetPoint(18,147.4019,199.9257);
   // NLO_exp->SetPoint(19,181.7,167.5);
   NLO_exp->SetPoint(19,183.6767,165.6425);

    Double_t *dum = 0;
    TPolyLine *NLO_obs = new TPolyLine(62,dum,dum,"");
    NLO_obs->SetFillColor(8);
    NLO_obs->SetLineColor(kBlack);
    NLO_obs->SetLineStyle(0);
    NLO_obs->SetLineWidth(5);


  NLO_obs->SetPoint(0,-0.1150955,214);
    NLO_obs->SetPoint(1,-0.1150955,214);
    NLO_obs->SetPoint(2,4.718867,214);
    NLO_obs->SetPoint(3,9.783018,214);
    NLO_obs->SetPoint(4,41.77924,227.4901);
    NLO_obs->SetPoint(5,71.70377,246.5891);
    NLO_obs->SetPoint(6,80.68113,251.2921);
    NLO_obs->SetPoint(7,86.66604,254.0149);
    NLO_obs->SetPoint(8,91.73019,255.5);
    NLO_obs->SetPoint(9,102.8585,256.5);
    NLO_obs->SetPoint(10,116.9717,251.5297);
    NLO_obs->SetPoint(11,120.5434,242.5792);
    
    NLO_obs->SetPoint(12,115.8434,230.3713);
    NLO_obs->SetPoint(13,110,220);
    NLO_obs->SetPoint(14,97.72264,201.4109);
    NLO_obs->SetPoint(15,73.,170);
    NLO_obs->SetPoint(16,75,170);
    NLO_obs->SetPoint(17,106.9226,204.3812);
    NLO_obs->SetPoint(18,119.9,218.4);
    NLO_obs->SetPoint(19,137.4019,201.9257);
    //NLO_obs->SetPoint(20,171.7,167.5);
    NLO_obs->SetPoint(20,173.2085,166.0671);


  Double_t *dum = 0;
    TPolyLine *LO_obs = new TPolyLine(62,dum,dum,"");
   LO_obs->SetFillColor(8);
   LO_obs->SetLineColor(kBlack);
   LO_obs->SetLineStyle(5);
   LO_obs->SetLineWidth(4);


  LO_obs->SetPoint(0,-0.1150955,209);
   LO_obs->SetPoint(1,-0.1150955,209);
   LO_obs->SetPoint(2,4.718867,209);
   LO_obs->SetPoint(3,9.783018,209);
   LO_obs->SetPoint(4,41.77924,222.4901);
   LO_obs->SetPoint(5,71.70377,241.5891);
   LO_obs->SetPoint(6,80.68113,246.2921);
   LO_obs->SetPoint(7,86.66604,249.0149);
   LO_obs->SetPoint(8,91.73019,250.5);
   LO_obs->SetPoint(9,102.8585,251.5);
   LO_obs->SetPoint(10,116.9717,246.5297);
   LO_obs->SetPoint(11,120.5434,242.5792);

   LO_obs->SetPoint(12,115.8434,230.3713);
   LO_obs->SetPoint(13,110,220);
   LO_obs->SetPoint(14,97.72264,201.4109);
   LO_obs->SetPoint(15,73.,170);
   LO_obs->SetPoint(16,75,170);
   LO_obs->SetPoint(17,116.7491,216.5396);
   LO_obs->SetPoint(18,132.4019,201.9257);
   // LO_obs->SetPoint(19,167.7,167.5);
   LO_obs->SetPoint(19,169.1471,166.2413);

    



    
 


    //1and 2 sigma bands

  ///try to make a band around them
   int n=47;
   TGraph *grshade = new TGraph;
   //first one

 grshade->SetPoint(0,-0.0007023795,205.0267);
   grshade->SetPoint(1,4.699516,205.0267);
   grshade->SetPoint(2,9.76838,205.0267);
   grshade->SetPoint(3,41.56398,215.5438);
   grshade->SetPoint(4,71.42419,234.7489);
   grshade->SetPoint(5,80.64031,239.4739);
   grshade->SetPoint(6,86.3543,242.0143);
   grshade->SetPoint(7,91.51532,244.5546);
   grshade->SetPoint(8,103.8649,247.8063);
   grshade->SetPoint(9,115.938,242.7256);
   grshade->SetPoint(10,118.4264,232.5642);
   grshade->SetPoint(11,116.491,230.4303);
   grshade->SetPoint(12,109.5789,220.6245);
   grshade->SetPoint(13,105.8003,214.7817);
   grshade->SetPoint(14,103.5884,210.8187);
   grshade->SetPoint(15,98.51957,201.7242);
   grshade->SetPoint(16,93.35854,194.8653);
   grshade->SetPoint(17,83.86595,182.2143);
   grshade->SetPoint(18,75.57144,170.9351);
   grshade->SetPoint(19,79.71869,169.1061);
   grshade->SetPoint(20,106.7219,204.6203);
   grshade->SetPoint(21,118.4264,209.701);
   grshade->SetPoint(22,151.7887,177.4893);
   grshade->SetPoint(23,162.8547,166.4699);
   grshade->SetPoint(24,200.2658,164.9566);
   grshade->SetPoint(25,144.7845,219.1511);
   grshade->SetPoint(26,131.4211,231.4972);
   grshade->SetPoint(27,106.7219,204.6203);
   grshade->SetPoint(28,79.71869,169.1061);
   grshade->SetPoint(29,75.57144,170.9351);
   grshade->SetPoint(30,83.86595,182.2143);
   grshade->SetPoint(31,93.35854,194.8653);
   grshade->SetPoint(32,98.51957,201.7242);
   grshade->SetPoint(33,103.5884,210.8187);
   grshade->SetPoint(34,105.8003,214.7817);
   grshade->SetPoint(35,109.5789,220.6245);
   grshade->SetPoint(36,116.491,230.4303);
   grshade->SetPoint(37,127.919,272.8542);
   grshade->SetPoint(38,122.5736,282.66);
   grshade->SetPoint(39,103.8649,288.452);
   grshade->SetPoint(40,91.51532,287.7407);
   grshade->SetPoint(41,86.3543,285.2003);
   grshade->SetPoint(42,80.64031,282.3043);
   grshade->SetPoint(43,71.42419,275.7502);
   grshade->SetPoint(44,41.56398,255.8338);
   grshade->SetPoint(45,9.76838,240.1852);
   grshade->SetPoint(46,4.699516,240.1852);
   grshade->SetPoint(47,-0.0007023795,240.1852);




   //grshade->SetFillStyle(3000);
   grshade->SetFillColor(kGreen);
   grshade->SetLineStyle(2);
   grshade->SetLineWidth(3);

   //1sigma curve.....
   TGraph *grshade2 = new TGraph;
  //first one



   //first one
   grshade2->SetPoint(0,0,215);
   grshade2->SetPoint(1,4.718867,215);
   grshade2->SetPoint(2,9.783018,215);
   grshade2->SetPoint(3,41.77924,228.4901);
   grshade2->SetPoint(4,71.70377,247.5891);
   grshade2->SetPoint(5,80.68113,252.2921);
   grshade2->SetPoint(6,86.66604,255.0149);
   grshade2->SetPoint(7,91.73019,256.5);
   grshade2->SetPoint(8,103.8585,257.5);
   grshade2->SetPoint(9,115.9717,253.5297);
   grshade2->SetPoint(10,118.5434,245.5792);

   //here it goes in the gap
   grshade2->SetPoint(11,116.8434,230.3713);
   grshade2->SetPoint(12,109.8509,220.4703);
   grshade2->SetPoint(13,105.8585,214.5297);
   grshade2->SetPoint(14,103.7868,210.5693);
   grshade2->SetPoint(15,98.72264,201.4109);
   grshade2->SetPoint(16,93.65849,194.4802);
   grshade2->SetPoint(17,83.99057,181.6089);
   grshade2->SetPoint(18,75.70377,170.4703);
   grshade2->SetPoint(19,79.99057,168.4901);
   grshade2->SetPoint(20,106.9226,204.3812);
   //second part of the curve
   grshade2->SetPoint(21,120.8,219.5);
   grshade2->SetPoint(22,146.4019,194.9257);
   grshade2->SetPoint(23,175.2678,165.9909);
   //second part of the curve
   grshade2->SetPoint(24,189.6831,165.4139);
   grshade2->SetPoint(25,150.3783,203.9886);
   grshade2->SetPoint(26,127.2091,226.3583);
   //here it goes in the gap
   grshade2->SetPoint(27,106.9226,204.3812);
   grshade2->SetPoint(28,79.99057,168.4901);
   grshade2->SetPoint(29,75.70377,170.4703);
   grshade2->SetPoint(30,83.99057,181.6089);
   grshade2->SetPoint(31,93.65849,194.4802);
   grshade2->SetPoint(32,98.72264,201.4109);
   grshade2->SetPoint(33,103.7868,210.5693);
   grshade2->SetPoint(34,105.8585,214.5297);
   grshade2->SetPoint(35,109.8509,220.4703);
   grshade2->SetPoint(36,116.8434,230.3713);
   //second one
   grshade2->SetPoint(37,125.5434,262.5792);
   grshade2->SetPoint(38,120.9717,274.5297);
   grshade2->SetPoint(39,103.8585,280.5);
   grshade2->SetPoint(40,91.73019,278.5);
   grshade2->SetPoint(41,86.66604,277.0149);
   grshade2->SetPoint(42,80.68113,274.2921);
   grshade2->SetPoint(43,71.70377,267.5891);
   grshade2->SetPoint(44,41.77924,248.4901);
   grshade2->SetPoint(45,9.783018,232);
   grshade2->SetPoint(46,4.718867,232);
   grshade2->SetPoint(47,0,232);




   // grshade2->SetFillStyle(3000);
   grshade2->SetFillColor(kYellow);
   grshade2->SetLineColor(kBlack);
   grshade2->SetLineStyle(2);
   grshade2->SetLineWidth(3);




  
   //pline->Draw("");



  //  First->Draw("AP");
  
  /*
 for(vector<TH1F*>::iterator at = exclusionPlots.begin();at != exclusionPlots.end();++at){
      (*at)->SetContour(2);
      if(n == 0){
      	(*at)->DrawCopy();
	(*at)->SetTitle("tan#beta="+tanBeta_);
      }
      cout << " n " << n << endl;
     (*at)->DrawCopy("same");
      //  (*it)->Write();
      cout << " here " << endl;
      n++;
      }*/

  
   // TLegend* myleg = new TLegend(0.24,0.60,0.58,0.90,"    95% C.L. Limits:","brNDC");
  TLegend* myleg = new TLegend(0.25,0.63,0.5,0.87,"    95% C.L. Limits:","brNDC");
  myleg->SetFillColor(0); 
  myleg->SetShadowColor(0);
  myleg->SetTextSize(0.035);
  myleg->SetBorderSize(0);
  
  // myleg->AddEntry(sSecond,"NLO Expected Limit","L");
  // myleg->AddEntry(sFirst,"NLO Observed Limit","L"); 
  //myleg->AddEntry(sThird,"LO Observed Limit","L");

  myleg->AddEntry(LO_obs,"CMS LO observed","L"); 
  myleg->AddEntry(NLO_obs,"CMS NLO observed","L"); 
  //  myleg->AddEntry(NLO_exp,"CMS NLO Expected","L");    
  myleg->AddEntry(grshade2,"CMS NLO expected #pm 1#sigma","fl");
  myleg->AddEntry(grshade,"CMS NLO expected #pm 2#sigma","Fl");

  //constant squark and gluino mass contours
  for (int it=1;it<3;it++) {   
    //  for (int it=1;it<4;it++) {   
    lngl[it]->Draw("same");   
    lnsq[it]->Draw("same");
    sq_text[it]->Draw();
    gl_text[it]->Draw();
  }
   
  //expected and observed (LO & NLO) contours
  //sFirst->Draw("same");    
  //sSecond->Draw("same");   
  //sThird->Draw("same");
  grshade->Draw("f");
  grshade2->Draw("f"); 
  NLO_exp->Draw("same");
  NLO_obs->Draw("same");
  LO_obs->Draw("same");
    
  //exclusion limits previous experiments
  if(tanBeta_ == 3){
    TEV_sn_d0_1->SetLineColor(kBlue);
    TEV_sn_d0_1->SetLineWidth(3);  
    TEV_sn_d0_1->SetLineStyle(4);  
    TEV_sn_d0_1->Draw("same");
    TEV_sn_d0_2->SetLineColor(kBlue);
    TEV_sn_d0_2->SetLineWidth(3);  
    TEV_sn_d0_2->SetLineStyle(4);  
    TEV_sn_d0_2->Draw("same");
  }

  
  LEP_ch->SetLineColor(kMagenta);
  LEP_ch->SetLineWidth(3);  
  LEP_ch->SetLineStyle(7);  
  LEP_ch->Draw("same");
  LEP_sl->SetLineColor(kMagenta);
  LEP_sl->SetLineWidth(3);  
  LEP_sl->SetLineStyle(8);  
  if (tanBeta_ != 50) LEP_sl->Draw("same");

  TEV_sg_cdf->SetLineColor(kRed);
  TEV_sg_cdf->SetLineWidth(3);  
  TEV_sg_cdf->SetLineStyle(5);  
  // no tanb=5  TEV_sg_cdf->Draw("lsame");
  TEV_sg_d0->SetLineColor(kBlue);
  TEV_sg_d0->SetLineWidth(3);  
  TEV_sg_d0->SetLineStyle(6);  
  TEV_sg_d0->Draw("same");  




  //other labels
  Double_t xpos = 0;
  Double_t xposi = 0;
  Double_t ypos = 0;
  if(tanBeta_ == 50) xposi = 100;
  if(tanBeta_ == 50) xpos = 200;
  if(tanBeta_ == 50) ypos = -10;
  
  TLatex* lumilabel = new TLatex(150.,415.,"L_{int} = 35 pb^{-1},   #sqrt{s} = 7 TeV");
  lumilabel->SetTextAlign(12);
  lumilabel->SetTextSize(0.05);
  lumilabel->Draw("same");

  TLatex* cmslabel = new TLatex(10.,415., getenv ("NOPRELIMINARY") ? "CMS" : "CMS preliminary");
  cmslabel->SetTextAlign(12);
  cmslabel->SetTextSize(0.05);
  cmslabel->Draw("same");

  TString text_tanBeta;
  text_tanBeta =  "tan#beta = "+tanb+",  A_{0} = 0,  #mu > 0";
  TLatex* cmssmpars = new TLatex(160.,250,text_tanBeta);
  cmssmpars->SetTextAlign(12);
  cmssmpars->SetTextSize(0.05);

  cmssmpars->Draw("same");
 
  //LM points
 //  TMarker* LM0 = new TMarker(200.,160.,20);
//   TMarker* LM1 = new TMarker(60.,250.,20);
    
//   LM0->SetMarkerSize(1.2);
//   LM1->SetMarkerSize(1.2);
    
//   TLatex* tLM0 = new TLatex(205.,160.,"LM0");
//   tLM0->SetTextSize(0.035);
    
//   TLatex* tLM1 = new TLatex(65.,243.,"LM1");
//   tLM1->SetTextSize(0.035);
  
  if (tanBeta_ != 50){
//     LM0->Draw("same");   
//     tLM0->Draw("same");
//     LM1->Draw("same");   
//     tLM1->Draw("same");
  }
  
    /*
   Int_t n = 0;
    for(vector<TH1F*>::iterator at = exclusionPlots.begin();at != exclusionPlots.end();++at){
      (*at)->SetContour(2);
      if(n == 0){
      	(*at)->DrawCopy("same");
	(*at)->SetTitle("tan#beta=3");
      }
      cout << " n " << n << endl;
     (*at)->DrawCopy("same");
      //  (*it)->Write();
      cout << " here " << endl;
      n++;
      }
  
    */


   
  //stau=LSP contour
  stau->Draw("fsame");
  
  //legends
  legexp->Draw();
  legst->Draw();
  myleg->Draw();
  
//   hist->Draw("sameaxis");
//   cvsSys->RedrawAxis();
  cvsSys->Update();
  cvsSys->Write();
  
  
  cvsSys->SaveAs("RA7_mSUGRA_ExclusionLimit_plot1.pdf");
  if (1 || !getenv ("NOPRELIMINARY")) {
    cvsSys->SaveAs("RA7_mSUGRA_ExclusionLimit_plot1.png");
    cvsSys->SaveAs("RA7_mSUGRA_ExclusionLimit_plot1.eps");
  }
 
  output->Write();
  output->Close();
  delete output; 
  
}


void setPlottingStyle(TH1F& hsig){
  
  hsig.SetStats(kFALSE);
  
  hsig.SetAxisRange(80,500,"Y");
  hsig.SetAxisRange(0,520,"X");
  hsig.SetAxisRange(200,520,"X");

  hsig.GetXaxis()->SetTitle("m_{0} (GeV)");
  hsig.GetYaxis()->SetTitle("m_{1/2} (GeV)");
  hsig.GetYaxis()->SetTitleOffset(0.8);
  hsig.GetYaxis()->SetTitleSize(0.06);
  hsig.GetYaxis()->SetLabelSize(0.06);
  hsig.GetXaxis()->SetTitleOffset(0.9);
  hsig.GetXaxis()->SetTitleSize(0.06);
  hsig.GetXaxis()->SetLabelSize(0.06);

  hsig.SetLineWidth(1);  
  hsig.SetLineColor(kBlue);  
  
}




TGraph* set_sneutrino_d0_1(Int_t tanBeta){
  double sn_m0[14]= {0,  0, 48, 55, 80, 90,100,105,109,105,100, 72, 55,0};
  double sn_m12[14]={0,140,210,220,237,241,242,241,230,220,210,170,150,0};

  TGraph* sn_d0_gr = new TGraph(14,sn_m0,sn_m12);

  sn_d0_gr->SetFillColor(kGreen+3);
  sn_d0_gr->SetFillStyle(1001);

  return sn_d0_gr;
}

TGraph* set_sneutrino_d0_2(Int_t tanBeta){
  double sn_m0[9]= {0, 45, 75,115,130,150,163,185,0};
  double sn_m12[9]={0,140,170,213,202,183,168,140,0};

  TGraph* sn_d0_gr_2 = new TGraph(9,sn_m0,sn_m12);

  sn_d0_gr_2->SetFillColor(kGreen+3);
  sn_d0_gr_2->SetFillStyle(1001);

  return sn_d0_gr_2;
}

TGraph* set_lep_ch(Int_t tanBeta){
  if(tanBeta == 3) return set_lep_ch_tanBeta3();
  if(tanBeta == 10) return set_lep_ch_tanBeta10();
  if(tanBeta == 50) return set_lep_ch_tanBeta50();
}

TGraph* set_lep_ch_tanBeta10(){

  double ch_m0[11];
  double ch_m12[11];

  ch_m0[0] = 0;
  ch_m0[1] = 100;
  ch_m0[2] = 200;
  ch_m0[3] = 300;
  ch_m0[4] = 400;
  ch_m0[5] = 500;
  ch_m0[6] = 600;
  ch_m0[7] = 700;
  ch_m0[8] = 800; 
  ch_m0[9] = 800;
  ch_m0[10] = 0;

  ch_m12[0] = 163;
  ch_m12[1] = 162;
  ch_m12[2] = 161;
  ch_m12[3] = 160;
  ch_m12[4] = 159;
  ch_m12[5] = 158;
  ch_m12[6] = 157;
  ch_m12[7] = 156;
  ch_m12[8] = 155.4;
  ch_m12[9] = 0;
  ch_m12[10] = 0;
  
  
  TGraph* ch_gr = new TGraph(11,ch_m0,ch_m12);

  ch_gr->SetFillColor(3);
  ch_gr->SetLineColor(3);
  //  ch_gr->SetLineWidth(3);
  ch_gr->SetFillStyle(1001);

  return ch_gr;

}



TGraph* set_lep_ch_tanBeta3(){

  double ch_m0[17];
  double ch_m12[17];

  ch_m0[0] = 0;
  ch_m0[1] = 100;
  ch_m0[2] = 150;
  ch_m0[3] = 200;
  ch_m0[4] = 250;
  ch_m0[5] = 300;
  ch_m0[6] = 350;
  ch_m0[7] = 400;
  ch_m0[8] = 450;
  ch_m0[9] = 500;
  ch_m0[10] = 550;
  ch_m0[11] = 600;
  ch_m0[12] = 650;
  ch_m0[13] = 700;
  ch_m0[14] = 750;
  ch_m0[15] = 750;
  ch_m0[16] = 0;
  
  ch_m12[0] = 170;
  ch_m12[1] = 168;
  ch_m12[2] = 167;
  ch_m12[3] = 165;
  ch_m12[4] = 163;
  ch_m12[5] = 161;
  ch_m12[6] = 158;
  ch_m12[7] = 156;
  ch_m12[8] = 154;
  ch_m12[9] = 152;
  ch_m12[10] = 150;
  ch_m12[11] = 148;
  ch_m12[12] = 147;
  ch_m12[13] = 145;
  ch_m12[14] = 144;
  ch_m12[15] = 0;
  ch_m12[16] = 0;
  
  TGraph* ch_gr = new TGraph(17,ch_m0,ch_m12);

  ch_gr->SetFillColor(3);
  ch_gr->SetLineColor(3);
  // ch_gr->SetLineWidth(3);
  ch_gr->SetFillStyle(1001);

  return ch_gr;

}


TGraph* set_lep_ch_tanBeta50(){

  double ch_m0[21];
  double ch_m12[21];

  ch_m0[0] = 200;
  ch_m0[1] = 250;
  ch_m0[2] = 300;
  ch_m0[3] = 350;
  ch_m0[4] = 400;
  ch_m0[5] = 450;
  ch_m0[6] = 500;
  ch_m0[7] = 550;
  ch_m0[8] = 600;
  ch_m0[9] = 650;
  ch_m0[10] = 700;
  ch_m0[11] = 750;
  ch_m0[12] = 800;
  ch_m0[13] =850;
  ch_m0[14] = 900;
  ch_m0[15] = 950;
  ch_m0[16] = 1000;
  ch_m0[17] = 1050;
  ch_m0[18] = 1100;
  ch_m0[19] = 1100;
  ch_m0[20] = 200;
 
  ch_m12[0] = 157;
  ch_m12[1] = 156;
  ch_m12[2] = 156;
  ch_m12[3] = 155;
  ch_m12[4] = 155;
  ch_m12[5] = 154;
  ch_m12[6] = 154;
  ch_m12[7] = 153;
  ch_m12[8] = 153;
  ch_m12[9] = 152;
  ch_m12[10] = 152;
  ch_m12[11] = 152;
  ch_m12[12] = 152;
  ch_m12[13] = 152;
  ch_m12[14] = 152;
  ch_m12[15] = 153;
  ch_m12[16] = 153;
  ch_m12[17] = 153;
  ch_m12[18] = 154;
  ch_m12[19] = 0;
  ch_m12[20] = 0;
  
  
  TGraph* ch_gr = new TGraph(21,ch_m0,ch_m12);

  ch_gr->SetFillColor(3);
  ch_gr->SetLineColor(3);
  ch_gr->SetFillStyle(1001);

  return ch_gr;

}




TGraph* set_lep_sl(Int_t tanBeta){

  // CMS SUSY Summer2010 implementation
  //  double sl_m0[] =  {0,  0, 30, 50, 60, 75, 80,90,100};
  //  double sl_m12[] = {0,245,240,220,200,150,100,50,0}; 
  
  //contour from D0 trilepton paper (PLB 680 (2009) 34-43)

  double *sl_m0 = 0;
  double *sl_m12 = 0;
  int n = 0;

  double sl_m0_3[] ={0,  0, 10, 20, 30, 40, 50, 60, 70, 77,88,95};
  double sl_m12_3[]={0,245,242,239,232,222,209,189,165,140,60,0};
  int n_3 = 12;

  double sl_m0_10[]={ 0,  0, 11, 20, 24, 49, 70, 82,88,90};
  double sl_m12_10[]={0,240,237,233,230,200,150,100,50,0};
  int n_10 = 10;

  if (tanBeta==3){
    sl_m0 = sl_m0_3;
    sl_m12 = sl_m12_3;
    n = n_3;
  }
  //CMS PTDR-II
  //* Selectron_R line mass=99, ISASUGRA7.69, A0=0, m_top=175, tan(beta]=10
  if (tanBeta==10 || tanBeta==50){
    sl_m0 = sl_m0_10;
    sl_m12 = sl_m12_10;
    n = n_10;
  }

  TGraph* lep_sl = new TGraph(n,sl_m0,sl_m12);

  lep_sl->SetFillColor(5);
  lep_sl->SetLineColor(5);
  lep_sl->SetFillStyle(1001);
  
  return lep_sl;
}


TGraph* set_tev_sg_cdf(Int_t tanBeta){

  //  double sg_m0[] =  {0,  0, 20, 50,100,150,200,250,300,350,400,450,500,550,600,600};
  //  double sg_m12[] = {0,160,169,170,160,155,150,122,116,112,110,106,105,100, 98,  0};
  //  int np=16;
  //New CHF from CDF plot in ICHEP2010 talk (E. Halkiadakis)
  double sg_m0[]= {0,  0, 30, 75,150,185,225,310,360,400,430,500,600,600};
  double sg_m12[]={0,162,168,170,160,150,130,120,109,108,100, 96, 95,  0};
  int np=14;

  TGraph* sg_gr = new TGraph(np,sg_m0,sg_m12);

  //  gStyle->SetHatchesLineWidth(3);

  sg_gr->SetFillColor(2);
  sg_gr->SetLineColor(2);
  //  sg_gr->SetLineWidth(3);
  sg_gr->SetFillStyle(1001); 

  return sg_gr;

}

TGraph* set_tev_sg_d0(Int_t tanBeta){

  //  double sgd_m0[] = {0, 0,  50, 100,150,200,250,300,350,400,450,500,550,600,600};
  //  double sgd_m12[] = {0,168,167,162,157,145,125,120,110,108,95, 94 ,94 ,93,0};
  //  int np=15;
  double sgd_m0[]= {0,  0., 25., 80.,100.,150.,192.,250.,300. ,350.,400.,450. ,500.,600.,600.,0.};
double sgd_m12[]={0,167.,167.,163.,162.,157.,149.,136.,125.5,116.,109.,106.5,105.,105.,  0.,0.};
 int npd=16;

  //double sgd_m0[]= {0,  0, 30, 80,150,240,320,400,500,600,600,0};
  //double sgd_m12[]={0,167,166,162,156,138,121,109,105,105,  0,0};
 //  int npd=16;

  TGraph* sgd_gr = new TGraph(npd,sgd_m0,sgd_m12);

  gStyle->SetHatchesLineWidth(3);

  sgd_gr->SetFillColor(kMagenta+3);
  sgd_gr->SetLineColor(kMagenta+3);
  sgd_gr->SetLineWidth(3);
  sgd_gr->SetFillStyle(3335);

  return sgd_gr;

}

// TGraph* set_tev_tlp_cdf(Int_t tanBeta){
//   double tlp1_m0[] = {   0, 20, 40, 60, 70, 80, 90, 80, 70, 60};
//   double tlp1_m12[] = {170,185,200,215,220,215,210,190,175,160};
//   TGraph* tlp1_gr = new TGraph(10,tlp1_m0,tlp1_m12);

//   tlp1_gr->SetFillColor(4);
//   tlp1_gr->SetLineColor(4);
//   tlp1_gr->SetFillStyle(1001);

//   return tlp1_gr;
// }

// TGraph* set_tev_tlp_d0(Int_t tanBeta){
//   double tlp2_m0[] = {  70, 80, 90,100,105,110,120,130,140};
//   double tlp2_m12[] = {160,172,184,196,205,195,185,173,160};
//   TGraph* tlp2_gr = new TGraph(9,tlp2_m0,tlp2_m12);

//   tlp2_gr->SetFillColor(4);
//   tlp2_gr->SetFillStyle(1001); 

//   return tlp2_gr;

// }





TGraph* set_tev_stau(Int_t tanBeta){

    double st_m0_tanBeta3[] = {0,10,20,30,40,50,60,70,80,90,100,0};
    double st_m12_tanBeta3[] = {337,341,356,378,406,439,473,510,548,587,626,626};   

    double st_m0_tanBeta10[] = {0,10,20,30,40,50,60,70,80,90,100,0};
    double st_m12_tanBeta10[] = {213,220,240,275,312,351,393,435,476,518,559,559};

    double st_m0_tanBeta50[] = {200,210,220,230,240,250,260,270,280,290,310,325,200,200};
    double st_m12_tanBeta50[] = {206,226,246,267,288,310,332,354,376,399,450,500,500,206};


    TGraph* st_gr_tanBeta3 = new TGraph(12,st_m0_tanBeta3,st_m12_tanBeta3);
    TGraph* st_gr_tanBeta10 = new TGraph(12,st_m0_tanBeta10,st_m12_tanBeta10);
    TGraph* st_gr_tanBeta50 = new TGraph(14,st_m0_tanBeta50,st_m12_tanBeta50);

    st_gr_tanBeta3->SetFillColor(40);
    st_gr_tanBeta3->SetFillStyle(1001);

    st_gr_tanBeta50->SetFillColor(40);
    st_gr_tanBeta50->SetFillStyle(1001);
    
    st_gr_tanBeta10->SetFillColor(40);
    st_gr_tanBeta10->SetFillStyle(1001);


    if(tanBeta == 3)return st_gr_tanBeta3;
    if(tanBeta == 10)return st_gr_tanBeta10;
    if(tanBeta == 50)return st_gr_tanBeta50;

}




TF1* constant_squark(int tanBeta,int i){
//---lines of constant gluino/squark
  double coef1 = 0.35;
  double coef2[] = {5,5,4.6,4.1};

  char hname[200];

  sprintf(hname,"lnsq_%i",i); 

  
  TF1* lnsq = new TF1(hname,"sqrt([0]-x*x*[1]-[2])",0,1000);
  lnsq->SetParameter(0,(500+150*(i-1))*(500+150*(i-1))/coef2[i]);
  lnsq->SetParameter(1,1./coef2[i]);
  lnsq->SetParameter(2,-coef1*91*91*(2*TMath::Cos(TMath::ATan(tanBeta)))/coef2[i]);//--tanbeta=10 --> cos2beta = -99/101
  lnsq->SetLineWidth(1);


  lnsq->SetLineColor(kGray);

  return lnsq;
}


TF1* constant_gluino(int tanBeta,int i){
//---lines of constant gluino/squark
  double coef1 = 0.35;
  double coef2[] = {5,5,4.6,4.1};

  char hname[200];

  sprintf(hname,"lngl_%i",i); 
    
  TF1* lngl = new TF1(hname,"[0]+x*[1]",0,1000);
  lngl->SetParameter(0,(500+150.*(i-1))/2.4);
  lngl->SetParameter(1,-40./1400);
  lngl->SetLineWidth(1);
  lngl->SetLineColor(kGray);

  return lngl;
}


TLatex* constant_squark_text(Int_t it,TF1& lnsq,Int_t tanBeta_){
  char legnm[200];

  sprintf(legnm,"#font[92]{#tilde{q}(%i)GeV/c^{2}}",500+150*(it-1));
  Double_t place_x = 160;
  if(tanBeta_ == 50)place_x = 290;
  TLatex* t3 = new TLatex(place_x+10*(it-1),lnsq.Eval(place_x+10*(it-1))+5,legnm);
  t3->SetTextSize(0.03);
  t3->SetTextAngle(-8);
  t3->SetTextColor(kGray+2);


  
  return t3;
}

TLatex* constant_gluino_text(Int_t it,TF1& lngl){
  char legnm[200];

  sprintf(legnm,"#font[12]{#tilde{g}}#font[92]{(%i)GeV/c^{2}}",500+150*(it-1));
  TLatex* t4 = new TLatex(230,18+lngl.Eval(480),legnm);
  t4->SetTextSize(0.03);
  t4->SetTextAlign(13);
  t4->SetTextColor(kGray+2);

  return t4;
}



TLegend* makeStauLegend(Double_t txtsz,Int_t tanBeta_){
  Double_t ypos_1 = 0.86;
  Double_t ypos_2 = 0.88;
  Double_t xpos_1 = 0.15;
  Double_t xpos_2 = 0.16;
  if(tanBeta_ == 50){
    xpos_1 = 0.17;
    xpos_2 = 0.18;
    ypos_1 = 0.76;
    ypos_2 = 0.78;

  }
  TLegend* legst = new TLegend(xpos_1,ypos_1,xpos_2,ypos_2);
  legst->SetHeader("#tilde{#tau} = LSP");
  legst->SetFillStyle(0);
  legst->SetBorderSize(0);
  legst->SetTextSize(0.03);

  return legst;
}


TLegend* makeExpLegend(TGraph& sg_gr, TGraph& sgd_gr,TGraph& ch_gr,TGraph& sl_gr,TGraph& tev_sn,Double_t txtsz,Int_t tanbeta){
  //  TLegend* legexp = new TLegend(0.63,0.62,0.91,0.83,NULL,"brNDC");
  TLegend* legexp = new TLegend(0.65,0.65,0.85,0.9,NULL,"brNDC");
  legexp->SetFillColor(0);
  legexp->SetShadowColor(0);
  legexp->SetTextSize(txtsz);
  legexp->SetBorderSize(0);

  sg_gr.SetLineColor(1);
  // no tanb=5  legexp->AddEntry(&sg_gr,"CDF  #tilde{#font[12]{g}}, #tilde{#font[12]{q}}, #scale[0.8]{tan#beta=5,   #mu < 0}","l"); 
  //  sgd_gr.SetLineColor(1);
  //  sgd_gr.SetLineWidth(1);

  legexp->AddEntry(&sgd_gr,"D0   #tilde{#font[12]{g}}, #tilde{#font[12]{q}},  #scale[0.8]{#mu < 0}","l");  

  ch_gr.SetLineColor(1);
  legexp->AddEntry(&ch_gr,"LEP2   #font[122]{#tilde{#chi}_{1}^{#pm}}","l");  
  
  sl_gr.SetLineColor(1);
  if(tanbeta != 50) legexp->AddEntry(&sl_gr,"LEP2   #tilde{#font[12]{l}}^{#pm}","l"); 
  if(tanbeta == 3) legexp->AddEntry(&tev_sn,"D0  #tilde{#chi}^{#pm}_{1}, #tilde{#chi}^{0}_{2}","l");  

  return legexp;

}
