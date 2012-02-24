{
gROOT->ProcessLine(".x ra7PlotStyle.C");
//=========Macro generated from canvas: c/interpret
//=========  (Fri Aug 26 19:52:37 2011) by ROOT version5.30/01
  char* gopt = "c";
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
   
// Graph expectedP2
  double xx[11] = {900, 875, 850, 825, 800, 775, 750, 725, 718.925, 703.499, 701.214};
  double yy[11] = {1807.85, 1808.82, 1808.1, 1817.23, 1832.48, 1840.54, 1842.67, 1882.12, 1900, 1950, 2000};
  TGraph* exp2p = new TGraph(11, xx, yy);
// end expectedP2
   exp2p->SetName("Exp2p");
   exp2p->SetTitle("Exp2p");
   exp2p->SetFillColor(1);

   exp2p->SetLineColor(kAzure+5);
   exp2p->SetLineWidth(2);
   exp2p->SetLineStyle(3);
   exp2p->SetMarkerStyle(8);

   
   //   exp2p->Draw(gopt);
   
// Graph expectedM2
//  double xx[17] = {900, 875, 850, 825, 800, 775, 750, 725, 700, 675, 650, 625, 615.482, 608.582, 608.453, 610.707, 596.189};
  double xx[17] = {900, 875, 850, 825, 800, 775, 750, 725, 700, 675, 650, 625, 615.482, 608.582, 608.453, 610.707, 604};
  double yy[17] = {1664.48, 1666.02, 1667.47, 1668.92, 1669.41, 1674.45, 1680.31, 1687.35, 1693.65, 1690.58, 1724.04, 1756.32, 1800, 1850, 1900, 1950, 2000};
  TGraph* exp2m = new TGraph(17, xx, yy);
// end expectedM2
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

// Graph expectedP1
//  double xx[10] = {900, 875, 850, 825, 800, 775, 750, 725, 700.378, 696.665};
  double xx[10] = {900, 875, 850, 825, 800, 775, 750, 715, 700.378, 696.665};
  double yy[10] = {1789.91, 1798.71, 1805.27, 1814.09, 1826.92, 1842.53, 1852.33, 1901.67, 1950, 2000};
  TGraph* exp1p = new TGraph(10, xx, yy);
// end expectedP1
   exp1p->SetName("Exp1p");
   exp1p->SetTitle("Exp1p");
   exp1p->SetFillColor(1);

   exp1p->SetLineColor(kAzure+5);
   exp1p->SetLineWidth(2);
   exp1p->SetMarkerStyle(8);
   
   
   //exp1p->Draw(gopt);
   
// Graph expectedM1
  double xx[13] = {900, 875, 850, 825, 800, 775, 750, 725, 708.001, 666.502, 654.902, 649.767, 645.395};
  double yy[13] = {1723.77, 1727.44, 1729.79, 1731.48, 1733.66, 1741.54, 1745.69, 1756.62, 1800, 1850, 1900, 1950, 2000};
  TGraph* exp1m = new TGraph(13, xx, yy);
// end expectedM1
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

// Graph expected
  double xx[12] = {900, 875, 850, 825, 800, 775, 750, 725, 722.789, 708.445, 689.171, 681.085};
  double yy[12] = {1765.14, 1770.46, 1775.4, 1783.09, 1790.8, 1814.13, 1825.44, 1846.84, 1850, 1900, 1950, 2000};
  TGraph* expected = new TGraph(12, xx, yy);
// end expected
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
   
// Graph observed
//  double xx[17] = {900, 875, 850, 825, 800, 775, 750, 725, 700, 675, 650, 625, 613.087, 603.488, 603.835, 606.141, 585.296};
  double xx[17] = {900, 875, 850, 825, 800, 775, 750, 725, 700, 675, 650, 625, 613.087, 603.488, 603.835, 606.141, 594};
  double yy[17] = {1748.67, 1748.18, 1745.62, 1744, 1741.07, 1738.07, 1732.65, 1728.1, 1731.89, 1734.36, 1753, 1764.55, 1800, 1850, 1900, 1950, 2000};
  TGraph* observed = new TGraph(17, xx, yy);
// end observed
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

  TLatex* lumilabel = new TLatex(665,2015,"#sqrt{s} = 7 TeV,   L_{int} = 4.7 fb^{-1}");
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
