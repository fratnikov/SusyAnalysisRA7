#include <sstream>
#include <string>
#include <iomanip>
#include "ExclusionPlot.hh"
 
#include "TH1.h"
#include "TH2.h"
#include "TFile.h"
#include "TStyle.h"
#include "TLatex.h"
#include "TCanvas.h"
#include "TMarker.h"
#include <vector>
#include "TMath.h"

void ExclusionPlot(){
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
  TLegend* legexp = makeExpLegend( *TEV_sg_cdf,*TEV_sg_d0,*LEP_ch,*LEP_sl,*TEV_sn_d0_1,0.035,tanBeta_);
  
 
  //make Canvas
  TCanvas* cvsSys = new TCanvas("cvsnm","cvsnm",0,0,800,600);
  gStyle->SetOptTitle(0);
  cvsSys->SetFillColor(0);
  cvsSys->GetPad(0)->SetRightMargin(0.07);
  cvsSys->Range(-120.5298,26.16437,736.0927,500);
  //  cvsSys->Range(-50.5298,26.16437,736.0927,500);
  cvsSys->SetFillColor(0);
  cvsSys->SetBorderMode(0);
  cvsSys->GetPad(0)->SetBorderSize(2);
  cvsSys->GetPad(0)->SetLeftMargin(0.1407035);
  cvsSys->GetPad(0)->SetTopMargin(0.08);
  cvsSys->GetPad(0)->SetBottomMargin(0.13);

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
  TH2D* hist = new TH2D("h","h",100,m0min,500,100,80,500);
  hist->Draw();  
  hist->GetXaxis()->SetTitle("m_{0} (GeV)");
  hist->GetYaxis()->SetTitle("m_{1/2} (GeV)");
  hist->GetYaxis()->SetTitleOffset(1.);
  hist->GetXaxis()->SetNdivisions(506);
  //  if (tanBeta_ == 50)  hist->GetXaxis()->SetNdivisions(504);
  hist->GetYaxis()->SetNdivisions(506);

  int col[]={2,3,4};

  TSpline3 *sFirst = new TSpline3("sFirst",First);
  sFirst->SetLineColor(kRed);
  sFirst->SetLineWidth(3);

  TSpline3 *sSecond = new TSpline3("sSecond",Second);
  sSecond->SetLineColor(kBlue);
  sSecond->SetLineStyle(2);
  sSecond->SetLineWidth(3);
  
  TSpline3 *sThird = new TSpline3("sThird",Third);
  sThird->SetLineColor(kGreen+2);
  sThird->SetLineStyle(4);
  sThird->SetLineWidth(3);


 


  Double_t *dum = 0;
   TPolyLine *NLO_exp = new TPolyLine(62,dum,dum,"");
   NLO_exp->SetFillColor(8);
   NLO_exp->SetLineColor(kBlue);
   NLO_exp->SetLineStyle(7);
   NLO_exp->SetLineWidth(5);

   NLO_exp->SetPoint(0,-0.1150955,225);
   NLO_exp->SetPoint(1,-0.1150955,225);
   NLO_exp->SetPoint(2,4.718867,225);
   NLO_exp->SetPoint(3,9.783018,225);
   NLO_exp->SetPoint(4,41.77924,238.4901);
   NLO_exp->SetPoint(5,71.70377,257.5891);
   NLO_exp->SetPoint(6,80.68113,262.2921);
   NLO_exp->SetPoint(7,86.66604,265.0149);
   NLO_exp->SetPoint(8,91.73019,268.5);
   NLO_exp->SetPoint(9,103.8585,270.5);
   NLO_exp->SetPoint(10,118.9717,265.5297);
   NLO_exp->SetPoint(11,122.5434,252.5792);

   NLO_exp->SetPoint(12,116.8434,230.3713);
   NLO_exp->SetPoint(13,109.8509,220.4703);
   NLO_exp->SetPoint(14,105.8585,214.5297);
   NLO_exp->SetPoint(15,103.78679,210.5693);
   NLO_exp->SetPoint(16,98.72264,201.4109);
   NLO_exp->SetPoint(17,93.65849,194.4802);
   NLO_exp->SetPoint(18,83.99057,181.6089);
   NLO_exp->SetPoint(19,75.70377,170.4703);

  
   NLO_exp->SetPoint(20,79.99057,168.4901);
   NLO_exp->SetPoint(21,106.9226,204.3812);
   NLO_exp->SetPoint(22,121.7491,227.5396);
   NLO_exp->SetPoint(23,147.4019,201.9257);
   NLO_exp->SetPoint(24,183.7,167.5);


    Double_t *dum = 0;
    TPolyLine *NLO_obs = new TPolyLine(62,dum,dum,"");
    NLO_obs->SetFillColor(8);
    NLO_obs->SetLineColor(kRed);
    NLO_obs->SetFillColor(kRed);
    NLO_obs->SetLineStyle(0);
    NLO_obs->SetLineWidth(5);
    NLO_obs->SetPoint(0,-0.1150955,215);
    NLO_obs->SetPoint(1,-0.1150955,215);
    NLO_obs->SetPoint(2,4.718867,215);
    NLO_obs->SetPoint(3,9.783018,215);
    NLO_obs->SetPoint(4,41.77924,228.4901);
    NLO_obs->SetPoint(5,71.70377,247.5891);
    NLO_obs->SetPoint(6,80.68113,252.2921);
    NLO_obs->SetPoint(7,86.66604,255.0149);
    NLO_obs->SetPoint(8,91.73019,256.5);
    NLO_obs->SetPoint(9,102.8585,257.5);
    NLO_obs->SetPoint(10,116.9717,252.5297);
    NLO_obs->SetPoint(11,120.5434,242.5792);
    
    NLO_obs->SetPoint(12,115.8434,230.3713);
    NLO_obs->SetPoint(13,109.8509,220.4703);
    NLO_obs->SetPoint(14,105.8585,214.5297);
    NLO_obs->SetPoint(15,103.78679,210.5693);
    NLO_obs->SetPoint(16,98.72264,201.4109);
    NLO_obs->SetPoint(17,93.65849,194.4802);
    NLO_obs->SetPoint(18,83.99057,181.6089);
    NLO_obs->SetPoint(19,75.70377,170.4703);
    NLO_obs->SetPoint(20,0,170.4703);

    TPolyLine *NLO_obs2 = new TPolyLine(62,dum,dum,"");
    NLO_obs2->SetFillColor(8);
    NLO_obs2->SetLineColor(kBlack);
    NLO_obs2->SetFillColor(kRed);
    NLO_obs2->SetLineStyle(0);
    NLO_obs2->SetLineWidth(5);
    NLO_obs2->SetPoint(0,79.99057,168.4901);
    NLO_obs2->SetPoint(1,106.9226,204.3812);
    NLO_obs2->SetPoint(2,118.7491,223.5396);
    NLO_obs2->SetPoint(3,136.4019,203.9257);
    NLO_obs2->SetPoint(4,173.7,162.5);
    NLO_obs2->SetPoint(5,80,167.5);


    //1and 2 sigma bands

  ///try to make a band around them
   int n=47;
   TGraph *grshade = new TGraph;
   //first one
   grshade->SetPoint(0,0,210);
   grshade->SetPoint(1,4.718867,210);
   grshade->SetPoint(2,9.783018,210);
   grshade->SetPoint(3,41.77924,218.4901);
   grshade->SetPoint(4,71.70377,237.5891);
   grshade->SetPoint(5,80.68113,242.2921);
   grshade->SetPoint(6,86.66604,245.0149);
   grshade->SetPoint(7,91.73019,247.5);
   grshade->SetPoint(8,103.8585,250.5);
   grshade->SetPoint(9,115.9717,245.5297);
   grshade->SetPoint(10,118.5434,232.5792);
   //here it goes in the gap
   grshade->SetPoint(11,116.8434,230.3713);
   grshade->SetPoint(12,109.8509,220.4703);
   grshade->SetPoint(13,105.8585,214.5297);
   grshade->SetPoint(14,103.78679,210.5693);
   grshade->SetPoint(15,98.72264,201.4109);
   grshade->SetPoint(16,93.65849,194.4802);
   grshade->SetPoint(17,83.99057,181.6089);
   grshade->SetPoint(18,75.70377,170.4703);
   grshade->SetPoint(19,79.99057,168.4901);
   grshade->SetPoint(20,106.9226,204.3812);
   //second part of the curve
   grshade->SetPoint(21,118.7491,210.5396);
   grshade->SetPoint(22,147.4019,180.9257);
   grshade->SetPoint(23,160.7,167.5);

   //second one
   grshade->SetPoint(47,0,240);
   grshade->SetPoint(46,4.718867,240);
   grshade->SetPoint(45,9.783018,240);
   grshade->SetPoint(44,41.77924,253.4901);
   grshade->SetPoint(43,71.70377,275.5891);
   grshade->SetPoint(42,80.68113,282.2921);
   grshade->SetPoint(41,86.66604,285.0149);
   grshade->SetPoint(40,91.73019,288.5);
   grshade->SetPoint(39,103.8585,290.5);
   grshade->SetPoint(38,122.9717,282.5297);
   grshade->SetPoint(37,128.5434,272.5792);
   //here it goes in the gap
   grshade->SetPoint(36,116.8434,230.3713);
   grshade->SetPoint(35,109.8509,220.4703);
   grshade->SetPoint(34,105.8585,214.5297);
   grshade->SetPoint(33,103.78679,210.5693);
   grshade->SetPoint(32,98.72264,201.4109);
   grshade->SetPoint(31,93.65849,194.4802);
   grshade->SetPoint(30,83.99057,181.6089);
   grshade->SetPoint(29,75.70377,170.4703);
   grshade->SetPoint(28,79.99057,168.4901);
   grshade->SetPoint(27,106.9226,204.3812);
   //second part of the curve
   grshade->SetPoint(26,128.7491,240.5396);
   grshade->SetPoint(25,149.4019,220.9257);
   grshade->SetPoint(24,200.7,167.5);


   //grshade->SetFillStyle(3000);
   grshade->SetFillColor(kGreen);



   //1sigma curve.....
   TGraph *grshade2 = new TGraph;
   //first one
   grshade2->SetPoint(0,0,220);
   grshade2->SetPoint(1,4.718867,220);
   grshade2->SetPoint(2,9.783018,220);
   grshade2->SetPoint(3,41.77924,231.4901);
   grshade2->SetPoint(4,71.70377,250.5891);
   grshade2->SetPoint(5,80.68113,255.2921);
   grshade2->SetPoint(6,86.66604,258.0149);
   grshade2->SetPoint(7,91.73019,260.5);
   grshade2->SetPoint(8,103.8585,263.5);
   grshade2->SetPoint(9,115.9717,258.5297);
   grshade2->SetPoint(10,118.5434,245.5792);
   //here it goes in the gap
   grshade2->SetPoint(11,116.8434,230.3713);
   grshade2->SetPoint(12,109.8509,220.4703);
   grshade2->SetPoint(13,105.8585,214.5297);
   grshade2->SetPoint(14,103.78679,210.5693);
   grshade2->SetPoint(15,98.72264,201.4109);
   grshade2->SetPoint(16,93.65849,194.4802);
   grshade2->SetPoint(17,83.99057,181.6089);
   grshade2->SetPoint(18,75.70377,170.4703);
   grshade2->SetPoint(19,79.99057,168.4901);
   grshade2->SetPoint(20,106.9226,204.3812);
   //second part of the curve
   grshade2->SetPoint(21,118.7491,225.5396);
   grshade2->SetPoint(22,147.4019,195.9257);
   grshade2->SetPoint(23,175.7,167.5);

   //second one
   grshade2->SetPoint(47,0,230);
   grshade2->SetPoint(46,4.718867,230);
   grshade2->SetPoint(45,9.783018,230);
   grshade2->SetPoint(44,41.77924,243.4901);
   grshade2->SetPoint(43,71.70377,265.5891);
   grshade2->SetPoint(42,80.68113,272.2921);
   grshade2->SetPoint(41,86.66604,275.0149);
   grshade2->SetPoint(40,91.73019,278.5);
   grshade2->SetPoint(39,103.8585,280.5);
   grshade2->SetPoint(38,120.9717,272.5297);
   grshade2->SetPoint(37,125.5434,262.5792);
   //here it goes in the gap
   grshade2->SetPoint(36,116.8434,230.3713);
   grshade2->SetPoint(35,109.8509,220.4703);
   grshade2->SetPoint(34,105.8585,214.5297);
   grshade2->SetPoint(33,103.78679,210.5693);
   grshade2->SetPoint(32,98.72264,201.4109);
   grshade2->SetPoint(31,93.65849,194.4802);
   grshade2->SetPoint(30,83.99057,181.6089);
   grshade2->SetPoint(29,75.70377,170.4703);
   grshade2->SetPoint(28,79.99057,168.4901);
   grshade2->SetPoint(27,106.9226,204.3812);
   //second part of the curve
   grshade2->SetPoint(26,122.7491,232.5396);
   grshade2->SetPoint(25,149.4019,205.9257);
   grshade2->SetPoint(24,190.7,167.5);


   //grshade2->SetFillStyle(3000);
   grshade2->SetFillColor(kYellow);




  
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

  
  TLegend* myleg = new TLegend(0.33,0.75,0.58,0.9,NULL,"brNDC");
  myleg->SetFillColor(0); 
  myleg->SetShadowColor(0);
  myleg->SetTextSize(0.03);
  myleg->SetBorderSize(0);
  
  // myleg->AddEntry(sSecond,"NLO Expected Limit","L");
  // myleg->AddEntry(sFirst,"NLO Observed Limit","L"); 
  //myleg->AddEntry(sThird,"LO Observed Limit","L");

  myleg->AddEntry(NLO_obs,"CMS Observed Limit","f"); 
  myleg->AddEntry(NLO_exp,"CMS Expected Limit","L");    
  //myleg->AddEntry(grshade2,"#pm 1#sigma Expected Limit","F");
  //myleg->AddEntry(grshade,"#pm 2#sigma Expected Limit","F");




  //constant squark and gluino mass contours
  for (int it=1;it<4;it++) {   
    lngl[it]->Draw("same");   
    lnsq[it]->Draw("same");
    sq_text[it]->Draw();
    gl_text[it]->Draw();
  }
   


  //draw lep before
  LEP_ch->Draw("fsame");
  if (tanBeta_ != 50) LEP_sl->Draw("fsame");

  NLO_exp->Draw("same");
  NLO_obs->Draw("fsame");
  NLO_obs2->Draw("fsame");
   
    
 //  //exclusion limits previous experiments
   if(tanBeta_ == 3){
     //TEV_sn_d0_1->Draw("fsame");
     //TEV_sn_d0_2->Draw("fsame");
     TEV_sn_d0_1->Draw("same");
     TEV_sn_d0_2->Draw("same");
   }
   //LEP_ch->Draw("fsame");
  //if (tanBeta_ != 50) LEP_sl->Draw("fsame");

  //TEV_sg_cdf->Draw("fsame");
  //TEV_sg_d0->Draw("same");  
  //TEV_sg_d0->Draw("fsame");

  TEV_sg_cdf->Draw("same");
  TEV_sg_d0->Draw("same");  
  //TEV_sg_d0->Draw("same");


  //other labels
  Double_t xpos = 0;
  Double_t xposi = 0;
  Double_t ypos = 0;
  if(tanBeta_ == 50) xposi = 100;
  if(tanBeta_ == 50) xpos = 200;
  if(tanBeta_ == 50) ypos = -10;
  
  TLatex* lumilabel = new TLatex(135.+xposi,510.,"L_{int} = 35 pb^{-1}, #sqrt{s} = 7 TeV");
  lumilabel->SetTextSize(0.05);
  lumilabel->Draw("same");

  TLatex* cmslabel = new TLatex(10.,510.,"CMS");
  cmslabel->SetTextSize(0.05);
  cmslabel->Draw("same");

  TString text_tanBeta;
  text_tanBeta =  "tan#beta = "+tanb+", A_{0} = 0, #mu > 0";
  TLatex* cmssmpars = new TLatex(70.+xpos,340.+ypos,text_tanBeta);
  cmssmpars->SetTextSize(0.04);

  cmssmpars->Draw("same");
 
  //LM points
  TMarker* LM0 = new TMarker(200.,160.,20);
  TMarker* LM1 = new TMarker(60.,250.,20);
    
  LM0->SetMarkerSize(1.2);
  LM1->SetMarkerSize(1.2);
    
  TLatex* tLM0 = new TLatex(205.,160.,"LM0");
  tLM0->SetTextSize(0.035);
    
  TLatex* tLM1 = new TLatex(65.,243.,"LM1");
  tLM1->SetTextSize(0.035);
  
  if (tanBeta_ != 50){
    LM0->Draw("same");   
    tLM0->Draw("same");
    LM1->Draw("same");   
    tLM1->Draw("same");
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


  //expected and observed (LO & NLO) contours
  //sFirst->Draw("same");    
  //sSecond->Draw("same");   
  //sThird->Draw("same");
  //grshade->Draw("f");
  //grshade2->Draw("f"); 

  //i plotted them befor...
  // NLO_exp->Draw("same");
//   NLO_obs->Draw("fsame");
//   NLO_obs2->Draw("fsame");
   
  //stau=LSP contour
  stau->Draw("fsame");
  
  //legends
  legexp->Draw();
  legst->Draw();
  myleg->Draw();
  
  hist->Draw("sameaxis");
  cvsSys->RedrawAxis();
  cvsSys->Update();
  cvsSys->Write();
  
  
  cvsSys->SaveAs("RA7_mSUGRA_ExclusionLimit_plot5.pdf");
//   cvsSys->SaveAs("RA7_ExclusionLimit_tanb"+tanb+".png");
//   cvsSys->SaveAs("RA7_ExclusionLimit_tanb"+tanb+".eps");
  
  
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
  //double sn_m0[14]= {0,  0, 48, 55, 80, 90,100,105,109,105,100, 72, 55,0};
  //double sn_m12[14]={0,140,210,220,237,241,242,241,230,220,210,170,150,0};
  double sn_m0[12]= {  15, 48, 55, 80, 90,100,105,109,105,100, 72, 72};
  double sn_m12[12]={165,210,220,237,241,242,241,230,220,210,170,170};

  //TGraph* sn_d0_gr = new TGraph(14,sn_m0,sn_m12);
  TGraph* sn_d0_gr = new TGraph(12,sn_m0,sn_m12);

  sn_d0_gr->SetFillColor(kGreen+3);
  sn_d0_gr->SetLineColor(kGreen+3);
  sn_d0_gr->SetLineWidth(3);
  sn_d0_gr->SetFillStyle(1001);

  return sn_d0_gr;
}

TGraph* set_sneutrino_d0_2(Int_t tanBeta){
  //double sn_m0[9]= {0, 45, 75,115,130,150,163,185,0};
  //double sn_m12[9]={0,140,170,213,202,183,168,140,0};
  double sn_m0[7]= { 75, 75,115,130,150,163,180};
  double sn_m12[7]={170,170,213,202,183,168,150};

  //TGraph* sn_d0_gr_2 = new TGraph(9,sn_m0,sn_m12);
  TGraph* sn_d0_gr_2 = new TGraph(7,sn_m0,sn_m12);

  sn_d0_gr_2->SetFillColor(kGreen+3);
  sn_d0_gr_2->SetLineColor(kGreen+3);
  sn_d0_gr_2->SetLineWidth(3);
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

  sg_gr->SetFillColor(kAzure+6);
  sg_gr->SetLineColor(kAzure+6);
  sg_gr->SetLineWidth(3);
  //  sg_gr->SetLineWidth(3);
  // sg_gr->SetFillStyle(1001); 

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

  sgd_gr->SetFillColor(kMagenta+2);
  sgd_gr->SetLineColor(kMagenta+2);
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
    st_gr_tanBeta3->SetLineColor(40);
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

  sprintf(legnm,"#font[92]{#tilde{q}(%i)GeV}",500+150*(it-1));
  Double_t place_x = 170;
  if(tanBeta_ == 50)place_x = 290;
  TLatex* t3 = new TLatex(place_x+10*(it-1),lnsq.Eval(place_x+10*(it-1))+5,legnm);
  t3->SetTextSize(0.03);
  t3->SetTextAngle(-8);
  t3->SetTextColor(kGray+2);


  
  return t3;
}

TLatex* constant_gluino_text(Int_t it,TF1& lngl){
  char legnm[200];

  sprintf(legnm,"#font[12]{#tilde{g}}#font[92]{(%i)GeV}",500+150*(it-1));
  TLatex* t4 = new TLatex(423,18+lngl.Eval(480),legnm);
  t4->SetTextSize(0.03);
  t4->SetTextAlign(13);
  t4->SetTextColor(kGray+2);

  return t4;
}



TLegend* makeStauLegend(Double_t txtsz,Int_t tanBeta_){
  Double_t ypos_1 = 0.86;
  Double_t ypos_2 = 0.88;
  Double_t xpos_1 = 0.16;
  Double_t xpos_2 = 0.17;
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
  TLegend* legexp = new TLegend(0.61,0.65,0.91,0.9,NULL,"brNDC");
  legexp->SetFillColor(0);
  legexp->SetShadowColor(0);
  legexp->SetTextSize(txtsz);
  legexp->SetBorderSize(0);

  sg_gr.SetLineColor(1);
  //legexp->AddEntry(&sg_gr,"CDF  #tilde{#font[12]{g}}, #tilde{#font[12]{q}}, #scale[0.8]{tan#beta=5, #mu < 0}","f"); 
legexp->AddEntry(&sg_gr,"CDF  #tilde{#font[12]{g}}, #tilde{#font[12]{q}}, #scale[0.8]{tan#beta=5, #mu < 0}","l"); 
  //  sgd_gr.SetLineColor(1);
  //  sgd_gr.SetLineWidth(1);

  //legexp->AddEntry(&sgd_gr,"D0   #tilde{#font[12]{g}}, #tilde{#font[12]{q}}, #scale[0.8]{tan#beta=3, #mu < 0}","f");  
 legexp->AddEntry(&sgd_gr,"D0   #tilde{#font[12]{g}}, #tilde{#font[12]{q}}, #scale[0.8]{tan#beta=3, #mu < 0}","l"); 
  ch_gr.SetLineColor(1);
  legexp->AddEntry(&ch_gr,"LEP2   #tilde{#chi}_{1}^{#pm}","f");  
  
  sl_gr.SetLineColor(1);
  if(tanbeta != 50) legexp->AddEntry(&sl_gr,"LEP2   #tilde{#font[12]{l}}^{#pm}","f"); 
  //if(tanbeta == 3) legexp->AddEntry(&tev_sn,"D0  #chi^{#pm}_{1}, #chi^{0}_{2}","f"); 
  if(tanbeta == 3) legexp->AddEntry(&tev_sn,"D0  #chi^{#pm}_{1}, #chi^{0}_{2}","l"); 
 

  return legexp;

}
