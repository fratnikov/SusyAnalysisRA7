{
//=========Macro generated from canvas: c1/c1
//=========  (Tue Oct 26 19:17:01 2010) by ROOT version5.18/00b

  gStyle->SetPalette(1);
  gStyle->SetOptTitle(kFALSE);
  gStyle->SetPadRightMargin(0.16);  
  gStyle->SetPadLeftMargin(0.13); 

  const Int_t NRGBs = 5;
  const Int_t NCont = 255;
  
  Double_t stops[NRGBs] = { 0.00, 0.2, 0.4, 0.7, 1.00 };
  Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.61 };
  Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
  Double_t blue[NRGBs]  = { 0.61, 1.00, 0.12, 0.00, 0.00 };
  TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
  gStyle->SetNumberContours(NCont);


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

   TH2F *hbranching = new TH2F("hbranching","hbranching",60,0,300,28,160,300);
 
   hbranching->SetEntries(0);


 //   hbranching->GetZaxis()->SetRangeUser(0,35);
//    hbranching->SetEntries(420);
//    hbranching->SetStats(0) ;
//    hbranching->SetContour(20);
//    hbranching->SetContourLevel(0,0);
//    hbranching->SetContourLevel(1,2.6507);
//    hbranching->SetContourLevel(2,5.3014);
//    hbranching->SetContourLevel(3,7.952099);
//    hbranching->SetContourLevel(4,10.6028);
//    hbranching->SetContourLevel(5,13.2535);
//    hbranching->SetContourLevel(6,15.9042);
//    hbranching->SetContourLevel(7,18.5549);
//    hbranching->SetContourLevel(8,21.2056);
//    hbranching->SetContourLevel(9,23.8563);
//    hbranching->SetContourLevel(10,26.507);
//    hbranching->SetContourLevel(11,29.1577);
//    hbranching->SetContourLevel(12,31.8084);
//    hbranching->SetContourLevel(13,34.4591);
//    hbranching->SetContourLevel(14,37.1098);
//    hbranching->SetContourLevel(15,39.7605);
//    hbranching->SetContourLevel(16,42.4112);
//    hbranching->SetContourLevel(17,45.0619);
//    hbranching->SetContourLevel(18,47.7126);
//    hbranching->SetContourLevel(19,50.3633);
   hbranching->GetZaxis()->SetRangeUser(0,3.5);
   hbranching->GetZaxis()->SetTitle(" #sigma_{NLO} x BR(>=3l) [pb]");
   hbranching->GetXaxis()->SetTitle("m_{0} [GeV/c^{2}]");
   hbranching->GetYaxis()->SetTitle("m_{1/2} [GeV/c^{2}]");
   hbranching->GetYaxis()->SetTitleOffset(1.1);

   hbranching->Draw("colz");


   
   ///try to make a band around them
   int n=47;
   TGraph *grshade = new TGraph;
   //first one
   grshade->SetPoint(0,0,205);
   grshade->SetPoint(1,4.718867,205);
   grshade->SetPoint(2,9.783018,205);
   grshade->SetPoint(3,41.77924,215.4901);
   grshade->SetPoint(4,71.70377,234.5891);
   grshade->SetPoint(5,80.68113,239.2921);
   grshade->SetPoint(6,86.66604,242.0149);
   grshade->SetPoint(7,91.73019,244.5);
   grshade->SetPoint(8,103.8585,247.5);
   grshade->SetPoint(9,115.9717,242.5297);
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
   grshade->SetPoint(21,118.7491,209.5396);
   grshade->SetPoint(22,152.4019,176.9257);
   grshade->SetPoint(23,161.7,167.5);

   //second one
   grshade->SetPoint(47,0,240);
   grshade->SetPoint(46,4.718867,240);
   grshade->SetPoint(45,9.783018,240);
   grshade->SetPoint(44,41.77924,255.4901);
   grshade->SetPoint(43,71.70377,275.5891);
   grshade->SetPoint(42,80.68113,282.2921);
   grshade->SetPoint(41,86.66604,285.0149);
   grshade->SetPoint(40,91.73019,287.5);
   grshade->SetPoint(39,103.8585,288.5);
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
   grshade->SetPoint(26,126.7491,236.5396);
   grshade->SetPoint(25,145.4019,218.9257);
   grshade->SetPoint(24,197.7,167.5);


   //grshade->SetFillStyle(3000);
   grshade->SetFillColor(kGreen);
    grshade->SetLineStyle(2);
    grshade->SetLineWidth(3);
   grshade->Draw("f");


   //1sigma curve.....
   TGraph *grshade2 = new TGraph;
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
   grshade2->SetPoint(14,103.78679,210.5693);
   grshade2->SetPoint(15,98.72264,201.4109);
   grshade2->SetPoint(16,93.65849,194.4802);
   grshade2->SetPoint(17,83.99057,181.6089);
   grshade2->SetPoint(18,75.70377,170.4703);
   grshade2->SetPoint(19,79.99057,168.4901);
   grshade2->SetPoint(20,106.9226,204.3812);
   //second part of the curve
   grshade2->SetPoint(21,118.7491,221.5396);
   grshade2->SetPoint(22,146.4019,194.9257);
   grshade2->SetPoint(23,173.7,167.5);

   //second one
   grshade2->SetPoint(47,0,232);
   grshade2->SetPoint(46,4.718867,232);
   grshade2->SetPoint(45,9.783018,232);
   grshade2->SetPoint(44,41.77924,248.4901);
   grshade2->SetPoint(43,71.70377,267.5891);
   grshade2->SetPoint(42,80.68113,274.2921);
   grshade2->SetPoint(41,86.66604,277.0149);
   grshade2->SetPoint(40,91.73019,278.5);
   grshade2->SetPoint(39,103.8585,280.5);
   grshade2->SetPoint(38,120.9717,274.5297);
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
   grshade2->SetPoint(26,122.7491,230.5396);
   grshade2->SetPoint(25,150.4019,203.9257);
   grshade2->SetPoint(24,187.7,167.5);


   //grshade2->SetFillStyle(3000);
   grshade2->SetFillColor(kYellow);
     grshade2->SetLineStyle(2);
    grshade2->SetLineWidth(3);
  grshade2->Draw("f");



   TLegend *leg = new TLegend(0.46,0.55,0.84,0.85,"95% C.L. Limits:","brNDC");
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
   dR->GetXaxis()->SetTitle("m_{0} [GeV]");
   dR->GetXaxis()->SetRange(1,244);
   dR->GetXaxis()->SetTitleSize(0.05);
   dR->GetXaxis()->SetTitleOffset(0.9);
   dR->GetYaxis()->SetTitle("m_{1/2} [GeV]");
   dR->GetYaxis()->SetTitleSize(0.05);
   dR->Draw("same");
   

 


   Double_t *dum = 0;
   TPolyLine *pline = new TPolyLine(62,dum,dum,"");
   pline->SetFillColor(8);
   pline->SetLineColor(kBlack);
   pline->SetLineStyle(2);
   pline->SetLineWidth(3);

   pline->SetPoint(0,-0.1150955,225);
   pline->SetPoint(1,-0.1150955,225);
   pline->SetPoint(2,4.718867,225);
   pline->SetPoint(3,9.783018,225);
   pline->SetPoint(4,41.77924,240.4901);
   pline->SetPoint(5,71.70377,259.5891);
   pline->SetPoint(6,80.68113,264.2921);
   pline->SetPoint(7,86.66604,267.0149);
   pline->SetPoint(8,91.73019,268.5);
   pline->SetPoint(9,103.8585,270.5);
   pline->SetPoint(10,118.9717,267.5297);
   pline->SetPoint(11,122.5434,252.5792);

   pline->SetPoint(12,116.8434,230.3713);
   pline->SetPoint(13,109.8509,220.4703);
   pline->SetPoint(14,105.8585,214.5297);
   pline->SetPoint(15,103.78679,210.5693);
   pline->SetPoint(16,98.72264,201.4109);
   pline->SetPoint(17,93.65849,194.4802);
   pline->SetPoint(18,83.99057,181.6089);
   pline->SetPoint(19,75.70377,170.4703);
   pline->SetPoint(20,79.99057,168.4901);
   
   pline->SetPoint(21,106.9226,204.3812);
   pline->SetPoint(22,120.7491,225.5396);
   pline->SetPoint(23,147.4019,199.9257);
   pline->SetPoint(24,181.7,167.5);


  
   pline->Draw("");

 Double_t *dum = 0;
   TPolyLine *pline = new TPolyLine(62,dum,dum,"");
   pline->SetFillColor(8);
   pline->SetLineColor(kBlack);
   pline->SetLineStyle(5);
   pline->SetLineWidth(4);
   pline->SetPoint(0,-0.1150955,209);
   pline->SetPoint(1,-0.1150955,209);
   pline->SetPoint(2,4.718867,209);
   pline->SetPoint(3,9.783018,209);
   pline->SetPoint(4,41.77924,222.4901);
   pline->SetPoint(5,71.70377,241.5891);
   pline->SetPoint(6,80.68113,246.2921);
   pline->SetPoint(7,86.66604,249.0149);
   pline->SetPoint(8,91.73019,250.5);
   pline->SetPoint(9,102.8585,251.5);
   pline->SetPoint(10,116.9717,246.5297);
   pline->SetPoint(11,120.5434,242.5792);

   pline->SetPoint(12,115.8434,230.3713);
   pline->SetPoint(13,109.8509,220.4703);
   pline->SetPoint(14,105.8585,214.5297);
   pline->SetPoint(15,103.78679,210.5693);
   pline->SetPoint(16,98.72264,201.4109);
   pline->SetPoint(17,93.65849,194.4802);
   pline->SetPoint(18,83.99057,181.6089);
   pline->SetPoint(19,75.70377,170.4703);
   pline->SetPoint(20,79.99057,168.4901);
   pline->SetPoint(21,106.9226,204.3812);
   
   pline->SetPoint(22,116.7491,216.5396);
   pline->SetPoint(23,132.4019,201.9257);
   pline->SetPoint(24,167.7,167.5);

   pline->Draw("");


   
   TLegendEntry *entry=leg->AddEntry(pline,"CMS LO excluded","l");
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
   entry->SetTextSize(0.04);


   Double_t *dum = 0;
   TPolyLine *pline = new TPolyLine(62,dum,dum,"");
   pline->SetFillColor(8);
   pline->SetLineColor(kBlack);
   pline->SetLineStyle(0);
   pline->SetLineWidth(5);
  

   pline->SetPoint(0,-0.1150955,214);
   pline->SetPoint(1,-0.1150955,214);
   pline->SetPoint(2,4.718867,214);
   pline->SetPoint(3,9.783018,214);
   pline->SetPoint(4,41.77924,227.4901);
   pline->SetPoint(5,71.70377,246.5891);
   pline->SetPoint(6,80.68113,251.2921);
   pline->SetPoint(7,86.66604,254.0149);
   pline->SetPoint(8,91.73019,255.5);
   pline->SetPoint(9,102.8585,256.5);
   pline->SetPoint(10,116.9717,251.5297);
   pline->SetPoint(11,120.5434,242.5792);

   pline->SetPoint(12,115.8434,230.3713);
   pline->SetPoint(13,109.8509,220.4703);
   pline->SetPoint(14,105.8585,214.5297);
   pline->SetPoint(15,103.78679,210.5693);
   pline->SetPoint(16,98.72264,201.4109);
   pline->SetPoint(17,93.65849,194.4802);
   pline->SetPoint(18,83.99057,181.6089);
   pline->SetPoint(19,75.70377,170.4703);
   pline->SetPoint(20,79.99057,168.4901);
   pline->SetPoint(21,106.9226,204.3812);
  
   pline->SetPoint(22,117.7491,220.5396);
   pline->SetPoint(23,137.4019,201.9257);
   pline->SetPoint(24,171.7,167.5);
   pline->Draw("");
   
    


   TLegendEntry *entry=leg->AddEntry(pline,"CMS NLO excluded","l");
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


//    TLegendEntry *entry=leg->AddEntry(pline,"CMS NLO expected","l");
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
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(0);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextColor(1);
   entry->SetTextSize(0.04);

 TLegendEntry *entry=leg->AddEntry(grshade,"NLO expected #pm 2#sigma","fl");
   entry->SetFillColor(0);
   entry->SetFillStyle(1001);
   entry->SetLineColor(0);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(0);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextColor(1);
   entry->SetTextSize(0.04);



  //tevatron exclusion 
   Double_t *dum = 0;
   pline = new TPolyLine(60,dum,dum,"");
   pline->SetFillColor(19);
   pline->SetLineColor(kRed);
   pline->SetLineStyle(7);
   pline->SetLineWidth(5);
   pline->SetPoint(0,0,200);
   pline->SetPoint(1,41.77924,218.4901);
   pline->SetPoint(2,71.70377,236.5891);
   pline->SetPoint(3,80.68113,241.2921);
   pline->SetPoint(4,86.66604,244.0149);
   pline->SetPoint(5,91.73019,245.5);
   pline->SetPoint(6,101.8585,245.5);
   pline->SetPoint(7,105.7717,239.5297);
   pline->SetPoint(8,107.8434,234.5792);
   pline->SetPoint(9,107.8434,230.3713);
   pline->SetPoint(10,104.8509,220.4703);
   pline->SetPoint(11,101.8585,214.5297);
   pline->SetPoint(12,99.78679,210.5693);
   pline->SetPoint(13,94.72264,201.4109);
   pline->SetPoint(14,89.65849,194.4802);
   pline->SetPoint(15,79.99057,181.6089);
   pline->SetPoint(16,71.70377,170.4703);
   pline->SetPoint(17,79.99057,168.4901);
   pline->SetPoint(18,106.9226,204.3812);
   pline->SetPoint(19,114.7491,213.5396);
   pline->SetPoint(20,130.4019,199.9257);
   pline->SetPoint(21,164.7,167.5);
   pline->SetPoint(22,244.8057,165.5198);
   pline->Draw("");

   entry=leg->AddEntry(pline,"Tevatron excluded","l");
   entry->SetLineColor(2);
   entry->SetLineStyle(2);
   entry->SetLineWidth(10);
   entry->SetMarkerColor(0);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextColor(1);
   entry->SetTextSize(0.04);




 //tevatron exclusion 
   Double_t *dum = 0;
   pline = new TPolyLine(60,dum,dum,"");
   pline->SetFillColor(19);
   pline->SetLineColor(kBlue);
   pline->SetLineStyle(7);
   pline->SetLineWidth(5);
   pline->SetPoint(0,-0.1150955,243.4703);
   pline->SetPoint(1,-0.1150955,243.4703);
   pline->SetPoint(2,4.718867,243.4901);
   pline->SetPoint(3,9.783018,241.5099);
   pline->SetPoint(4,14.84717,239.5297);
   pline->SetPoint(5,19.91132,237.5495);
   pline->SetPoint(6,24.74528,234.5792);
   pline->SetPoint(7,29.80943,230.3713);
   pline->SetPoint(8,34.6434,225.4208);
   pline->SetPoint(9,41.77924,218.4901);
   pline->SetPoint(10,50,210);
   pline->SetPoint(11,65,180);
   pline->SetPoint(12,70,160);

 
   pline->Draw("");

   entry=leg->AddEntry(pline,"LEP excluded","l");
   entry->SetLineColor(2);
   entry->SetLineStyle(2);
   entry->SetLineWidth(10);
   entry->SetMarkerColor(0);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextColor(1);
   entry->SetTextSize(0.04);


   leg->Draw();


   int coord=130;
   //   TLatex *   tex = new TLatex(coord,282.115,"#sqrt{s}=7TeV, L=35pb^{-1}");
   TLatex *   tex = new TLatex(150,300,"#sqrt{s}=7TeV, L=35pb^{-1}");
   tex->SetTextColor(1);
   tex->SetTextAlign(10);
   tex->SetTextSize(0.04);
   tex->SetTextFont(42);
   tex->SetLineWidth(2);
   tex->Draw();
   //   tex = new TLatex(coord,289.6086,"CMS preliminary");
   tex = new TLatex(10,300,"CMS preliminary");
   tex->SetTextColor(1);
   tex->SetTextAlign(10);
   tex->SetTextSize(0.04);
    tex->SetTextFont(42);
  tex->SetLineWidth(2);
   tex->Draw();
   tex = new TLatex(170,285,"tan#beta = 3, A_{0} = 0, #mu > 0");
   tex->SetTextColor(1);
   tex->SetTextAlign(10);
   tex->SetTextSize(0.04);
    tex->SetTextFont(42);
  tex->SetLineWidth(2);
   tex->Draw();

   tex = new TLatex(73,222,"#chi #rightarrow #tilde{l}l");
   tex->SetTextColor(kBlack);
   tex->SetTextAlign(10);
   tex->SetTextSize(0.03);
   tex->SetTextFont(32);
   tex->SetLineWidth(2);
   tex->Draw();

   tex = new TLatex(105,186,"#chi #rightarrow ll#chi^{1}_{0}");
   tex->SetTextColor(kBlack);
   tex->SetTextAlign(10);
   tex->SetTextSize(0.03);
   tex->SetTextFont(32);
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
   dR->GetXaxis()->SetTitle("m_{0} [GeV]");
   dR->GetXaxis()->SetRange(1,244);
   dR->GetXaxis()->SetTitleSize(0.05);
   dR->GetXaxis()->SetTitleOffset(0.9);
   dR->GetYaxis()->SetTitle("m_{1/2} [GeV]");
   dR->GetYaxis()->SetTitleSize(0.05);
   dR->Draw("sameaxis");
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
   c1->SetTickx();
   c1->SetTicky();
   //c1->SetLogz();

   c1->SetTickx();
   c1->SetTicky();
   c1->SaveAs("RA7_mSUGRA_ExclusionLimit_plot2.pdf");
   c1->SaveAs("RA7_mSUGRA_ExclusionLimit_plot2.png");
   c1->SaveAs("RA7_mSUGRA_ExclusionLimit_plot2.eps");












}
