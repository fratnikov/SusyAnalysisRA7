{
gROOT->ProcessLine(".x ra7PlotStyle.C");
//=========Macro generated from canvas: c/interpret
//=========  (Fri Aug 26 19:52:37 2011) by ROOT version5.30/01
  char* gopt = "l";
   TCanvas *c47 = new TCanvas("c47", "interpret_47",5,48,800,600);
   gStyle->SetOptFit(1);
   c47->Range(288.8889,984.8101,983.3333,1870.886);
   c47->SetFillColor(0);
   c47->SetBorderMode(0);
   c47->SetBorderSize(2);
   c47->SetTickx(1);
   c47->SetTicky(1);
   c47->SetLeftMargin(0.16);
   c47->SetRightMargin(0.12);
   c47->SetTopMargin(0.08);
   c47->SetBottomMargin(0.13);
   c47->SetFrameFillStyle(0);
   c47->SetFrameBorderMode(0);
   c47->SetFrameFillStyle(0);
   c47->SetFrameBorderMode(0);
   c47->SetGridx();
   c47->SetGridy();
   
   TH2D *frame = new TH2D("frame","",1,500,900,1,1500,2000);
   frame->SetStats(0);
   frame->SetMarkerStyle(12);
   frame->GetXaxis()->SetTitle("m_{#tilde{#chi}^{#pm}_{1}} (GeV/c^{2})   ");
   frame->GetXaxis()->SetNdivisions(505);
   frame->GetXaxis()->SetLabelFont(42);
   frame->GetXaxis()->SetLabelOffset(0.007);
   frame->GetXaxis()->SetLabelSize(0.05);
   frame->GetXaxis()->SetTitleSize(0.05);
   frame->GetXaxis()->SetTitleOffset(1.1);
   frame->GetXaxis()->SetTitleFont(42);
   frame->GetYaxis()->SetTitle("m_{#tilde{g}}  (GeV/c^{2})   ");
   frame->GetYaxis()->SetNdivisions(505);
   frame->GetYaxis()->SetLabelFont(42);
   frame->GetYaxis()->SetLabelOffset(0.007);
   frame->GetYaxis()->SetLabelSize(0.05);
   frame->GetYaxis()->SetTitleSize(0.05);
   frame->GetYaxis()->SetTitleOffset(1.2);
   frame->GetYaxis()->SetTitleFont(42);
   frame->GetZaxis()->SetLabelFont(42);
   frame->GetZaxis()->SetLabelOffset(0.007);
   frame->GetZaxis()->SetLabelSize(0.05);
   frame->GetZaxis()->SetTitleSize(0.05);
   frame->GetZaxis()->SetTitleFont(42);
   frame->Draw("");

   double xx[50];
   double yy[50];
   
   // Graph observed
   double xx[] = {610, 612, 613.417, 614.333, 626.118, 675, 700, 725, 750, 775, 800, 825, 850, 875, 900};
   double yy[] = {2000, 1950, 1900, 1850, 1800, 1763.31, 1753.6, 1740.79, 1746.34, 1753.74, 1756.87, 1758.97, 1760.56, 1763.94, 1764.1};
   TGraph* observed = new TGraph(15, xx, yy);
   // end observed

   // Graph expected
   double xx[] = {695.259, 701.229, 724.689, 750, 775, 800, 825, 850, 875, 900};
   double yy[] = {2000, 1950, 1900, 1842.91, 1832.24, 1812.92, 1802.74, 1794.53, 1789.3, 1784.08};
   TGraph* expected = new TGraph(10, xx, yy);
   // end expected

   // Graph exp1p
   double xx[] = {711.447, 714.65, 752.747, 775, 800, 825, 850, 875, 900};
   double yy[] = {2000, 1950, 1900, 1856.36, 1840.95, 1823.89, 1811.79, 1805.49, 1798.04};
   TGraph* exp1p = new TGraph(9, xx, yy);
   // end exp1p

   // Graph exp1m
   double xx[] = {658.923, 668.737, 682.785, 700, 725, 750, 775, 800, 825, 850, 875, 900};
   double yy[] = {2000, 1950, 1900, 1838.34, 1808.56, 1784.95, 1766.32, 1754.04, 1748.26, 1745.04, 1746.28, 1745.72};
   TGraph* exp1m = new TGraph(12, xx, yy);
   // end exp1m

   // Graph exp2p
   double xx[] = {713.383, 722.72, 774.074, 800, 825, 850, 875, 900};
   double yy[] = {2000, 1950, 1900, 1863.79, 1847.22, 1818.36, 1819.5, 1820.71};
   TGraph* exp2p = new TGraph(8, xx, yy);
   // end exp2p

   // Graph exp2m
   double xx[] = {617.827, 620.587, 618.081, 618.891, 632.061, 658.308, 700, 725, 750, 775, 800, 825, 850, 875, 900};
   double yy[] = {2000, 1950, 1900, 1850, 1800, 1750, 1719.47, 1709.83, 1700.39, 1693.45, 1687.93, 1687.99, 1687.47, 1683.22, 1679.86};
   TGraph* exp2m = new TGraph(15, xx, yy);
   // end exp2m



   exp2p->SetName("Exp2p");
   exp2p->SetTitle("Exp2p");
   exp2p->SetFillColor(1);

   exp2p->SetLineColor(kAzure+5);
   exp2p->SetLineWidth(2);
   exp2p->SetLineStyle(3);
   exp2p->SetMarkerStyle(8);

   
   //   exp2p->Draw(gopt);
   
   exp2m->SetName("Exp2m");
   exp2m->SetTitle("Exp2m");
   exp2m->SetFillColor(1);

   exp2m->SetLineColor(kAzure+5);
   exp2m->SetLineWidth(2);
   exp2m->SetLineStyle(3);
   exp2m->SetMarkerStyle(8);
   
   //exp2m->Draw(gopt);

   TGraph* exp2pm = new TGraph (exp2p->GetN()+exp2m->GetN());
   exp2pm->SetFillColor (exp2Fill);
   exp2pm->SetLineColor (exp2Color);
   exp2pm->SetLineWidth (exp2Width);
   exp2pm->SetLineStyle (exp2Style);

   int ipoint = 0;
   for (int i = 0; i < exp2p->GetN(); ++i) {
     double x = 0;
     double y = 0;
     exp2p->GetPoint(i, x, y);
     exp2pm->SetPoint (ipoint, x, y);
     ipoint++;
   }
   for (int i = exp2m->GetN()-1; i >= 0; --i) {
     double x = 0;
     double y = 0;
     exp2m->GetPoint(i, x, y);
     exp2pm->SetPoint (ipoint, x, y);
     ipoint++;
   }
   exp2pm->Draw("f");
   exp2pm->Draw("l");

   exp1p->SetName("Exp1p");
   exp1p->SetTitle("Exp1p");
   exp1p->SetFillColor(1);

   exp1p->SetLineColor(kAzure+5);
   exp1p->SetLineWidth(2);
   exp1p->SetMarkerStyle(8);
   
   
   //exp1p->Draw(gopt);
   
   exp1m->SetName("Exp1m");
   exp1m->SetTitle("Exp1m");
   exp1m->SetFillColor(1);

   exp1m->SetLineColor(kAzure+5);
   exp1m->SetLineWidth(2);
   exp1m->SetMarkerStyle(8);
   
   //exp1m->Draw(gopt);

   TGraph* exp1pm = new TGraph (exp1p->GetN()+exp1m->GetN());
   exp1pm->SetFillColor (exp1Fill);
   exp1pm->SetLineColor (exp1Color);
   exp1pm->SetLineWidth (exp1Width);
   exp1pm->SetLineStyle (exp1Style);
   int ipoint = 0;
   for (int i = 0; i < exp1p->GetN(); ++i) {
     double x = 0;
     double y = 0;
     exp1p->GetPoint(i, x, y);
     exp1pm->SetPoint (ipoint, x, y);
     ipoint++;
   }
   for (int i = exp1m->GetN()-1; i >= 0; --i) {
     double x = 0;
     double y = 0;
     exp1m->GetPoint(i, x, y);
     exp1pm->SetPoint (ipoint, x, y);
     ipoint++;
   }
   exp1pm->Draw("f");
   exp1pm->Draw("l");

   expected->SetName("Expected");
   expected->SetTitle("Expected");
   expected->SetFillColor(1);

   expected->SetLineColor(expectedColor);
   expected->SetLineStyle(expectedStyle);
   expected->SetLineWidth(expectedWidth);
   expected->SetMarkerStyle(8);

   expected->Draw(gopt);
   
   TGraph* expectedStyle1 = new TGraph (*expected);
   expectedStyle1->SetFillColor (exp1pm->GetFillColor());
   TGraph* expectedStyle2 = new TGraph (*expected);
   expectedStyle2->SetFillColor (exp2pm->GetFillColor());
   
   observed->SetName("Observed");
   observed->SetTitle("Observed");
   observed->SetFillColor(1);
   observed->SetLineStyle(observedStyle);
   observed->SetLineWidth(observedWidth);
   observed->SetLineColor(observedColor);
   observed->SetMarkerStyle(8);
   
   observed->Draw(gopt);
   
  TLegend* myleg = new TLegend(0.2,0.2,0.5,0.4,"95% C.L. CLs Limits","brNDC");;

 
  myleg->SetFillColor(0); 
  myleg->SetShadowColor(0);
  myleg->SetTextSize(0.035);
  myleg->SetBorderSize(0);

  myleg->AddEntry(observed,"NLO observed","l");
  myleg->AddEntry(expectedStyle1,"NLO expected #pm1#sigma","lf");
  myleg->AddEntry(expectedStyle2,"NLO expected #pm2#sigma","lf");
  myleg->Draw();

  TLatex* lumilabel = new TLatex(665,2015,"#sqrt{s} = 7 TeV,   L_{int} = 4.98 fb^{-1}");
  lumilabel->SetTextSize(0.05);
  lumilabel->Draw("same");

  TLatex* cmslabel = preliminary ? 
    new TLatex(500.,2015, "CMS Preliminary") :
    new TLatex(515.,2015, "CMS");
  cmslabel->SetTextSize(0.05);
  cmslabel->Draw("same");



   c47->Modified();
   c47->cd();
   c47->SaveAs ("exclu_conlsp4.7.pdf");
   c47->SaveAs ("exclu_conlsp4.7.png");
}
