{
//=========Macro generated from canvas: c1/c1
//=========  (Tue Oct 26 19:17:01 2010) by ROOT version5.18/00b

  gStyle->SetPalette(1);
  gStyle->SetOptTitle(kFALSE);
  gStyle->SetPadRightMargin(0.16);  
  gStyle->SetPadLeftMargin(0.13); 

  // const Int_t NRGBs = 5;
  // const Int_t NCont = 255;
  
  // Double_t stops[NRGBs] = { 0.00, 0.2, 0.4, 0.7, 1.00 };
  // Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.61 };
  // Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
  // Double_t blue[NRGBs]  = { 0.61, 1.00, 0.12, 0.00, 0.00 };
  // TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
  // gStyle->SetNumberContours(NCont);


//   const Int_t NRGBs = 2;
//   const Int_t NCont = 255;
  
//   Double_t stops[NRGBs] = { 0.00,  1.00 };
//   Double_t red[NRGBs]   = { 0.00, 0.71 };
//   Double_t green[NRGBs] = { 0.00, 0.00 };
//   Double_t blue[NRGBs]  = { 0.71, 0.00 };
//   TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
//   gStyle->SetNumberContours(NCont);



   TCanvas *c1 = new TCanvas("c1", "c1",29,28,1100,800);
   gStyle->SetOptStat(0);
   c1->Range(-30.5,142.5,274.5,317.5);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);

  TH2F *hbranching = new TH2F("hbranching","hbranching",12,300,900,15,850,1600);

   hbranching->SetEntries(0);
 
   hbranching->GetZaxis()->SetRangeUser(0,3.5);
   hbranching->GetZaxis()->SetTitle(" #sigma_{NLO} [pb]");
   hbranching->GetXaxis()->SetTitle("Chargino Mass [GeV/c^{2}]");
   hbranching->GetYaxis()->SetTitle("Gluino Mass [GeV/c^{2}]");
   hbranching->GetYaxis()->SetTitleOffset(1.5);


   hbranching->Draw("colz");




   TLegend *leg = new TLegend(0.38,0.60,0.84,0.90,"95% C.L. Limits:","brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(42);
   leg->SetTextSize(0.04);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   
   TH1 *dR = new TH2F("dR","dR",300,0,300,140,160,300);
   dR->SetStats(0);
   dR->GetXaxis()->SetTitle("Charigino Mass [GeV/c^{2}]");
   dR->GetXaxis()->SetRange(1,244);
   dR->GetXaxis()->SetTitleSize(0.05);
   dR->GetXaxis()->SetTitleOffset(0.9);
   dR->GetYaxis()->SetTitle("Gluino Mass [GeV/c^{2}]");
   dR->GetYaxis()->SetTitleSize(0.05);
   dR->Draw("same");
   





   
   ///try to make a band around them
   int n=13;
   double x[n],ymax[n],ymin[n];
   //first one
   x[0]=300; ymax[0]= 1560; ymin[0]= 1040;
   x[1]=350; ymax[1]= 1200; ymin[1]= 1005;
   x[2]=400; ymax[2]= 1130; ymin[2]= 1000;
   x[3]=450; ymax[3]= 1110; ymin[3]= 1000;
   x[4]=500; ymax[4]= 1108; ymin[4]= 1000;
   x[5]=550; ymax[5]= 1108; ymin[5]= 1000;
   x[6]=600; ymax[6]= 1108; ymin[6]= 1000;
   x[7]=650; ymax[7]= 1108; ymin[7]= 1000;
   x[8]=700; ymax[8]= 1108; ymin[8]= 1000;
   x[9]=750; ymax[9]= 1108; ymin[9]= 1000;
   x[10]=800; ymax[10]= 1107; ymin[10]= 999;
   x[11]=850; ymax[11]= 1106; ymin[11]= 998;
   x[12]=900; ymax[12]= 1105; ymin[12]= 997;

   TGraph *grshade = new TGraph(n);
   for(int i=0;i<n;i++) {
      grshade->SetPoint(i,x[i],ymax[i]);
      grshade->SetPoint(n+i,x[n-i-1],ymin[n-i-1]);
   }
   //grshade->SetFillStyle(3000);
   grshade->SetFillColor(kGreen);
    grshade->SetLineStyle(2);
    grshade->SetLineWidth(3);
  grshade->Draw("f");


 

   //second one
   x[0]=300; ymax[0]= 1450;      ymin[0]= 1120;
   x[1]=350; ymax[1]= 1160;      ymin[1]= 1060;
   x[2]=400; ymax[2]= 1100;      ymin[2]= 1050;
   x[3]=450; ymax[3]= 1090;      ymin[3]= 1040;
   x[4]=500; ymax[4]= 1080;      ymin[4]= 1040;
   x[5]=550; ymax[5]= 1080;      ymin[5]= 1040;
   x[6]=600; ymax[6]= 1080;      ymin[6]= 1040;
   x[7]=650; ymax[7]= 1080;      ymin[7]= 1040;
   x[8]=700; ymax[8]= 1080;      ymin[8]= 1040;
   x[9]=750; ymax[9]= 1080;      ymin[9]= 1040;
   x[10]=800; ymax[10]= 1079;    ymin[10]= 1039;
   x[11]=850; ymax[11]= 1078;    ymin[11]= 1038;
   x[12]=900; ymax[12]= 1077;    ymin[12]= 1037;


   TGraph *grshade2 = new TGraph(n);
   for(int i=0;i<n;i++) {
      grshade2->SetPoint(i,x[i],ymax[i]);
      grshade2->SetPoint(n+i,x[n-i-1],ymin[n-i-1]);
   }
   //grshade2->SetFillStyle(3000);
   grshade2->SetFillColor(kYellow);
    grshade2->SetLineStyle(2);
    grshade2->SetLineWidth(3);
   grshade2->Draw("f");












 

   Double_t *dum = 0;
   TPolyLine *NLO_exp = new TPolyLine(62,dum,dum,"");
   NLO_exp->SetFillColor(kBlack);
   NLO_exp->SetLineColor(kBlack);
   NLO_exp->SetLineStyle(2);
   NLO_exp->SetLineWidth(3);


   NLO_exp->SetPoint(0,300,1280);
   NLO_exp->SetPoint(1,350,1120);
   NLO_exp->SetPoint(2,400,1080);
   NLO_exp->SetPoint(3,450,1070);
   NLO_exp->SetPoint(4,500,1065);
   NLO_exp->SetPoint(5,550,1065);
   NLO_exp->SetPoint(6,600,1065);
   NLO_exp->SetPoint(7,650,1065);
   NLO_exp->SetPoint(8,700,1065);
   NLO_exp->SetPoint(9,750,1064);
   NLO_exp->SetPoint(10,800,1063);
   NLO_exp->SetPoint(11,850,1062);
   NLO_exp->SetPoint(12,900,1061);

   //NLO_exp->Draw("");
   NLO_exp->Draw("");




   Double_t *dum = 0;
   TPolyLine *NLO_excl = new TPolyLine(62,dum,dum,"");
   NLO_excl->SetFillColor(kBlack);
   NLO_excl->SetLineColor(kBlack);
   NLO_excl->SetLineStyle(0);
   NLO_excl->SetLineWidth(4);


  NLO_excl->SetPoint(0,300,1065);
  NLO_excl->SetPoint(1,350,1053);
  NLO_excl->SetPoint(2,400,1041);
  NLO_excl->SetPoint(3,450,1040);
  NLO_excl->SetPoint(4,500,1040);
  NLO_excl->SetPoint(5,550,1040);
  NLO_excl->SetPoint(6,600,1040);
  NLO_excl->SetPoint(7,650,1040);
  NLO_excl->SetPoint(8,700,1040);
  NLO_excl->SetPoint(9,750,1040);
  NLO_excl->SetPoint(10,800,1039);
  NLO_excl->SetPoint(11,850,1038);
  NLO_excl->SetPoint(12,900,1037);
  NLO_excl->Draw("");





Double_t *dum = 0;
   TPolyLine *LO_excl = new TPolyLine(62,dum,dum,"");
   LO_excl->SetFillColor(8);
   LO_excl->SetLineColor(kBlack);
   LO_excl->SetLineStyle(5);
   LO_excl->SetLineWidth(4);

  LO_excl->SetPoint(0,300,1025);
  LO_excl->SetPoint(1,350,1019);
  LO_excl->SetPoint(2,400,1018);
  LO_excl->SetPoint(3,450,1018);
  LO_excl->SetPoint(4,500,1020);
  LO_excl->SetPoint(5,550,1020);
  LO_excl->SetPoint(6,600,1020);
  LO_excl->SetPoint(7,650,1020);
  LO_excl->SetPoint(8,700,1020);
  LO_excl->SetPoint(9,750,1020);
  LO_excl->SetPoint(10,800,1019);
  LO_excl->SetPoint(11,850,1018);
  LO_excl->SetPoint(12,900,1019);

  LO_excl->Draw("");

  TLegendEntry *entry=leg->AddEntry(LO_excl,"LO excluded","l");
   entry->SetFillColor(0);
   entry->SetFillStyle(1001);
   entry->SetLineColor(5);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(5);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextColor(1);
   entry->SetTextSize(0.04);
   leg->Draw();


   TLegendEntry *entry=leg->AddEntry(NLO_excl,"NLO excluded","l");
   entry->SetFillColor(0);
   entry->SetFillStyle(1001);
   entry->SetLineColor(5);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(5);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextColor(1);
   entry->SetTextSize(0.04);
   leg->Draw();

 


//   TLegendEntry *entry=leg->AddEntry(NLO_exp,"CMS NLO expected 95%CL","l");
//    entry->SetFillColor(0);
//    entry->SetFillStyle(1001);
//    entry->SetLineColor(0);
//    entry->SetLineStyle(1);
//    entry->SetLineWidth(1);
//    entry->SetMarkerColor(0);
//    entry->SetMarkerStyle(21);
//    entry->SetMarkerSize(1);
//    entry->SetTextColor(1);
//    entry->SetTextSize(0.04);

   TLegendEntry *entry=leg->AddEntry(grshade2,"NLO expected #pm 1#sigma","fl");
   entry->SetFillColor(0);
   entry->SetFillStyle(1001);
   entry->SetLineColor(0);
   entry->SetLineStyle(7);
   entry->SetLineWidth(5);
   entry->SetMarkerColor(0);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextSize(0.04);
   entry->SetTextColor(1);

   TLegendEntry *entry=leg->AddEntry(grshade,"NLO expected #pm 2#sigma","fl");
   entry->SetFillColor(0);
   entry->SetFillStyle(1001);
   entry->SetLineColor(0);
   entry->SetLineStyle(7);
   entry->SetLineWidth(5);
   entry->SetMarkerColor(0);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextSize(0.04);
   entry->SetTextColor(1);


   leg->Draw();




   int coord=525;
   //   TLatex *   tex = new TLatex(coord,1400,"#sqrt{s}=7TeV, L=35pb^{-1}");
   TLatex *   tex = new TLatex(600,1600,"#sqrt{s}=7TeV, L=35pb^{-1}");
   tex->SetTextColor(1);
   tex->SetTextAlign(10);
   tex->SetTextSize(0.04);
   tex->SetTextFont(42);
   tex->SetLineWidth(2);
   tex->Draw();
   // tex = new TLatex(coord,1450,"CMS preliminary");
   tex = new TLatex(340,1600,"CMS preliminary");
   tex->SetTextColor(1);
   tex->SetTextAlign(10);
   tex->SetTextSize(0.04);
   tex->SetTextFont(42);
   tex->SetLineWidth(2);
   tex->Draw();

 
 
   
   TPaveText *pt = new TPaveText(0.01,0.945,0.06589744,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(2);
   pt->SetFillColor(19);
   text = pt->AddText("dR");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);




//Primitive: xaxis/m_{0} [GeV]. You must implement TAxis::SavePrimitive
   
   TH1 *dR = new TH2F("dR","dR",300,0,300,140,160,300);
   dR->GetXaxis()->SetTitle("m_{chargino} [GeV]");
   dR->GetXaxis()->SetRange(1,244);
   dR->GetXaxis()->SetTitleSize(0.05);
   dR->GetXaxis()->SetTitleOffset(0.9);
   dR->GetYaxis()->SetTitle("m_{glunio} [GeV]");
   dR->GetYaxis()->SetTitleSize(0.05);
   dR->Draw("sameaxis");
   c1->Modified();
   c1->cd();

   c1->SetSelected(c1);
   //c1->SetLogz();
   c1->SetTickx();
   c1->SetTicky();
   c1->SaveAs("RA7_GGM_ExclusionLimit_plot1.pdf");
   c1->SaveAs("RA7_GGM_ExclusionLimit_plot1.png");
   c1->SaveAs("RA7_GGM_ExclusionLimit_plot1.eps");


   



}
