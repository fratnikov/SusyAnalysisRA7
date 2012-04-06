{
gROOT->ProcessLine(".x ra7PlotStyle.C");
  char* gopt = "l";
  TCanvas *c47 = new TCanvas("c47", "interpret_47",0,0,800,600);
   gStyle->SetOptFit(1);
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
   
   TH2D *frame = new TH2D("frame","",1,600,2300,1,600,1800);
   frame->SetStats(0);
   frame->SetMarkerStyle(12);
   frame->GetXaxis()->SetTitle("m_{#tilde{q}_{R}} (GeV/c^{2})   ");
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
  double xx[] = {1160.9, 1197.55, 1183.49, 1166.9, 1173.61, 1183.6, 1195.02, 1217.56, 1240.53, 1275.96, 1308.65, 1336.5, 1357.13, 1400, 1500, 1600, 1638.38, 1700, 1800, 1809.28, 1900, 2000, 2100, 2140.76, 2186.6, 2174.68, 2100, 2000, 1900, 1800, 1700, 1600, 1500, 1400};
  double yy[] = {2000, 1800, 1600, 1550, 1500, 1450, 1400, 1350, 1300, 1250, 1200, 1150, 1100, 1073.44, 1070.45, 1060.58, 1050, 1028.21, 1003.82, 1000, 966.195, 893.338, 874.872, 850, 800, 750, 725.952, 669.289, 682.268, 645.287, 597.641, 596.989, 587.39, 592.383};
  TGraph* observed = new TGraph(34, xx, yy);
// end observed

// Graph expected
  double xx[] = {1203.75, 1251.13, 1239.62, 1220.08, 1227.52, 1245.43, 1265.39, 1292.07, 1316.3, 1359.97, 1391.92, 1400, 1500, 1513.34, 1600, 1685, 1700, 1800, 1854.3, 1900, 1925.44, 2000, 2100, 2153.66, 2170.31, 2123.37, 2100, 2000, 1900, 1800, 1700, 1600, 1500, 1400};
  double yy[] = {2000, 1800, 1600, 1550, 1500, 1450, 1400, 1350, 1300, 1250, 1200, 1181.47, 1153.58, 1150, 1126.63, 1100, 1096.58, 1073.03, 1050, 1020.9, 1000, 950.144, 906.998, 850, 800, 750, 741.663, 681.182, 691.335, 653.833, 607.641, 602.841, 594.582, 601.233};
  TGraph* expected = new TGraph(34, xx, yy);
// end expected

// Graph exp1p
  double xx[] = {1233.91, 1277.8, 1267.8, 1246.67, 1252.96, 1275.67, 1299.73, 1330.21, 1354.36, 1399.46, 1400, 1464.82, 1500, 1600, 1608.81, 1700, 1735.85, 1800, 1900, 1911.53, 1979.83, 2000, 2100, 2198.67, 2200, 2230.4, 2222.09, 2200, 2100, 2000, 1900, 1800, 1700, 1600, 1500, 1400};
  double yy[] = {2000, 1800, 1600, 1550, 1500, 1450, 1400, 1350, 1300, 1250, 1249.08, 1200, 1184.41, 1153.1, 1150, 1113.14, 1100, 1084.58, 1056.02, 1050, 1000, 987.36, 941.811, 850, 845.532, 800, 750, 711.737, 698.691, 657.937, 672.868, 638.182, 596.077, 594.759, 586.21, 585.333};
  TGraph* exp1p = new TGraph(36, xx, yy);
// end exp1p

// Graph exp1m
  double xx[] = {1162.88, 1207.22, 1189.54, 1172.57, 1179.75, 1193.1, 1209.06, 1235.1, 1260.32, 1293.33, 1322.86, 1348.82, 1368.58, 1400, 1500, 1600, 1662.59, 1700, 1800, 1807.8, 1900, 2000, 2002.79, 2100, 2111.54, 2100, 2000, 1983.86, 1900, 1800, 1700, 1600, 1500, 1400};
  double yy[] = {2000, 1800, 1600, 1550, 1500, 1450, 1400, 1350, 1300, 1250, 1200, 1150, 1100, 1079.23, 1077.6, 1066.71, 1050, 1036, 1004.66, 1000, 953.542, 850.718, 850, 822.444, 800, 792.065, 764.876, 750, 730.073, 685.466, 637.74, 631.767, 614.675, 618.544};
  TGraph* exp1m = new TGraph(34, xx, yy);
// end exp1m

// Graph exp2p
  double xx[] = {1265.06, 1299.4, 1284.84, 1268.44, 1279.5, 1302.54, 1325.15, 1350.48, 1371.41, 1400, 1413.31, 1461.8, 1500, 1600, 1628.08, 1700, 1800, 1840.15, 1900, 1936, 1987.85, 2000, 2100, 2200, 2250.74, 2290.67, 2276.47, 2200, 2100, 2000, 1900, 1800, 1700, 1600, 1500, 1400};
  double yy[] = {2000, 1800, 1600, 1550, 1500, 1450, 1400, 1350, 1300, 1259.25, 1250, 1200, 1183.41, 1158.65, 1150, 1125.63, 1122.54, 1100, 1075.38, 1050, 1000, 991.618, 935.162, 895.882, 850, 800, 750, 687.579, 678.29, 642.373, 660.425, 629.893, 592.016, 590.74, 582.359, 574.836};
  TGraph* exp2p = new TGraph(36, xx, yy);
// end exp2p

// Graph exp2m
  double xx[] = {1110.82, 1151.67, 1133.3, 1117.1, 1125.3, 1136.53, 1147.4, 1163.84, 1179.9, 1209.96, 1239.25, 1273.01, 1298.55, 1373.52, 1400, 1500, 1566.29, 1600, 1700, 1800, 1900, 1903.62, 1927.92, 1900, 1813.12, 1800, 1700, 1600, 1500, 1400};
  double yy[] = {2000, 1800, 1600, 1550, 1500, 1450, 1400, 1350, 1300, 1250, 1200, 1150, 1100, 1050, 1033.95, 1018.63, 1000, 993.118, 968.193, 915, 853.496, 850, 800, 783.719, 750, 743.03, 676.507, 663.082, 642.676, 638.73};
  TGraph* exp2m = new TGraph(30, xx, yy);
// end exp2m

   exp2p->SetName("Exp2p");
   exp2p->SetTitle("Exp2p");
   exp2p->SetFillColor(1);

   exp2p->SetLineColor(kAzure+5);
   exp2p->SetLineWidth(2);
   exp2p->SetLineStyle(3);
   exp2p->SetMarkerStyle(8);

   
   //exp2p->Draw(gopt);
   

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
   
  TLegend* myleg = new TLegend(0.55,0.65,0.85,0.85,"95% C.L. CLs Limits","brNDC");;

 
  myleg->SetFillColor(0); 
  myleg->SetShadowColor(0);
  myleg->SetTextSize(0.035);
  myleg->SetBorderSize(0);

  myleg->AddEntry(observed,"NLO observed","l");
  myleg->AddEntry(expectedStyle1,"NLO expected #pm1#sigma","lf");
  myleg->AddEntry(expectedStyle2,"NLO expected #pm2#sigma","lf");
  myleg->Draw();

  TLatex* lumilabel = new TLatex(1350,1840,"#sqrt{s} = 7 TeV,   L_{int} = 4.98 fb^{-1}");
  lumilabel->SetTextSize(0.05);
  lumilabel->Draw("same");

  TLatex* cmslabel = preliminary ? 
    new TLatex(600.,1840,"CMS Preliminary") :
    new TLatex(700.,1840,"CMS");
  cmslabel->SetTextSize(0.05);
  cmslabel->Draw("same");



   c47->Modified();
   c47->cd();
   c47->SaveAs ("exclu_hadrpv4.7.pdf");
   c47->SaveAs ("exclu_hadrpv4.7.png");
}
