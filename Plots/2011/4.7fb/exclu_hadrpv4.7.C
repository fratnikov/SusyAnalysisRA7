{
  char* gopt = "c";
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
   
// Graph exp2p
  double xx[43] = {1100, 1200, 1300, 1400, 1500, 1600, 1700, 1800, 2000, 2200, 2236.23, 2269.53, 2220.88, 2200, 2169.96, 2100, 2069.77, 2000, 1977.04, 1915.5, 1900, 1811.69, 1800, 1729.24, 1700, 1600, 1500, 1490.93, 1400, 1392.8, 1355.89, 1335.04, 1311.11, 1300, 1296.92, 1279.45, 1267.13, 1283.3, 1293.13, 1243};
  double yy[43] = {551.972, 573.577, 584.667, 600.946, 596.6, 609.817, 612.781, 642.792, 663.515, 699.956, 750, 800, 850, 868.993, 900, 932.822, 950, 984.699, 1000, 1050, 1058.61, 1100, 1108.03, 1150, 1164.24, 1185.48, 1197.73, 1200, 1241.4, 1250, 1300, 1350, 1400, 1439.36, 1450, 1500, 1550, 1600, 1800, 2000};
  TGraph* exp2p = new TGraph(40, xx, yy);
// end exp2p
   exp2p->SetName("Exp2p");
   exp2p->SetTitle("Exp2p");
   exp2p->SetFillColor(1);

   exp2p->SetLineColor(kAzure+5);
   exp2p->SetLineWidth(2);
   exp2p->SetLineStyle(3);
   exp2p->SetMarkerStyle(8);

   
   //exp2p->Draw(gopt);
   
// Graph exp2m
  double xx[39] = {1000, 1100, 1200, 1300, 1400, 1500, 1600, 1700, 1784.23, 1800, 1908.42, 1900, 1866.05, 1800, 1790.39, 1712.41, 1700, 1600, 1516.64, 1500, 1418.79, 1400, 1321.82, 1300, 1266.02, 1219.64, 1200, 1192.91, 1165.72, 1149.32, 1133.73, 1125.45, 1116.78, 1110.52, 1127.43, 1140.04, 1100, 1098.18};
  double yy[39] = {580.791, 584.828, 595.347, 620.558, 647.348, 651.563, 676.19, 690.726, 750, 762.018, 800, 818.382, 850, 891.452, 900, 950, 954.439, 982.593, 1000, 1005.89, 1050, 1057.93, 1100, 1116.81, 1150, 1200, 1234.76, 1250, 1300, 1350, 1400, 1450, 1500, 1550, 1600, 1800, 1847.87, 2000};
  TGraph* exp2m = new TGraph(36, xx, yy);
// end exp2m

   exp2m->SetName("Exp2m");
   exp2m->SetTitle("Exp2m");
   exp2m->SetFillColor(1);

   exp2m->SetLineColor(kAzure+5);
   exp2m->SetLineWidth(2);
   exp2m->SetLineStyle(3);
   exp2m->SetMarkerStyle(8);
   
   //exp2m->Draw(gopt);

   TGraph* exp2pm = new TGraph (exp2p->GetN()+exp2m->GetN());
   exp2pm->SetFillColor (kCyan-10);
   exp2pm->SetLineColor (kBlue);
   exp2pm->SetLineWidth (1);
   exp2pm->SetLineStyle (3);

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

// Graph exp1p
  double xx[41] = {1100, 1200, 1300, 1400, 1500, 1600, 1700, 1800, 2000, 2100, 2172.13, 2187.52, 2169.16, 2131.84, 2100, 2029.45, 2000, 1943.14, 1900, 1878.99, 1800, 1713.8, 1700, 1600, 1590.94, 1500, 1443.79, 1400, 1383.37, 1339.37, 1312.87, 1300, 1282.48, 1264.03, 1248.08, 1243.36, 1265.91, 1269.84, 1222.04};
  double yy[41] = {555.958, 575.46, 586.401, 608.175, 598.733, 616.755, 621.232, 647.091, 671.704, 725.248, 750, 800, 850, 900, 922.757, 950, 959.768, 1000, 1039.06, 1050, 1076.98, 1100, 1105.38, 1146.02, 1150, 1176.48, 1200, 1231.76, 1250, 1300, 1350, 1370.78, 1400, 1450, 1500, 1550, 1600, 1800, 2000};
  TGraph* exp1p = new TGraph(39, xx, yy);
// end exp1p
   exp1p->SetName("Exp1p");
   exp1p->SetTitle("Exp1p");
   exp1p->SetFillColor(1);

   exp1p->SetLineColor(kAzure+5);
   exp1p->SetLineWidth(2);
   exp1p->SetMarkerStyle(8);
   
   
   //exp1p->Draw(gopt);
   
// Graph exp1m
  double xx[39] = {1000, 1100, 1200, 1300, 1400, 1500, 1600, 1700, 1800, 1900, 1939.46, 1994.71, 1974.51, 1930.48, 1900, 1871.33, 1800, 1753.95, 1700, 1615.15, 1600, 1500, 1461.79, 1400, 1382.83, 1305.7, 1300, 1275.82, 1241.33, 1213.66, 1200, 1190.48, 1180.26, 1170.55, 1163.41, 1179.32, 1196.02, 1150.6};
  double yy[39] = {568.128, 573.332, 587.42, 603.63, 631.341, 631.301, 646.074, 650.247, 693.287, 740.758, 750, 800, 850, 900, 929.947, 950, 985.737, 1000, 1017.46, 1050, 1054.33, 1082.71, 1100, 1137.55, 1150, 1200, 1208.12, 1250, 1300, 1350, 1375.71, 1400, 1450, 1500, 1550, 1600, 1800, 2000};
  TGraph* exp1m = new TGraph(38, xx, yy);
// end exp1m
   exp1m->SetName("Exp1m");
   exp1m->SetTitle("Exp1m");
   exp1m->SetFillColor(1);

   exp1m->SetLineColor(kAzure+5);
   exp1m->SetLineWidth(2);
   exp1m->SetMarkerStyle(8);
   
   //exp1m->Draw(gopt);

   TGraph* exp1pm = new TGraph (exp1p->GetN()+exp1m->GetN());
   exp1pm->SetFillColor (kCyan-4);
   exp1pm->SetLineColor (kBlue);
   exp1pm->SetLineWidth (1);
   exp1pm->SetLineStyle (3);
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
   double xx[43] = {1000, 1100, 1200, 1300, 1400, 1500, 1600, 1700, 1800, 2000, 2084.12, 2100, 2156.39, 2133.27, 2100, 2049.69, 2000, 1970.68, 1904.96, 1900, 1814.29, 1800, 1700, 1614.75, 1600, 1501.78, 1500, 1400, 1386.56, 1345.02, 1310.06, 1300, 1280.45, 1248.44, 1232.3, 1219.52, 1213.1, 1231.83, 1243.24, 1200, 1190.79};
  double yy[43] = {556.09, 562.998, 580.168, 592.274, 616.635, 611.102, 629.075, 633.702, 663.859, 691.938, 750, 756.959, 800, 850, 881.814, 900, 921.007, 950, 1000, 1004.04, 1050, 1055.22, 1076.41, 1100, 1106.05, 1150, 1150.56, 1191.98, 1200, 1250, 1300, 1317.89, 1350, 1400, 1450, 1500, 1550, 1600, 1800, 1840.42, 2000};
  TGraph* expected = new TGraph(40, xx, yy);
// end expected
   expected->SetName("Expected");
   expected->SetTitle("Expected");
   expected->SetFillColor(1);

   expected->SetLineColor(kBlue);
   expected->SetLineStyle(1);
   expected->SetLineWidth(3);
   expected->SetMarkerStyle(8);

   expected->Draw(gopt);
   
   TGraph* expectedStyle1 = new TGraph (*expected);
   expectedStyle1->SetFillColor (exp1pm->GetFillColor());
   TGraph* expectedStyle2 = new TGraph (*expected);
   expectedStyle2->SetFillColor (exp2pm->GetFillColor());
   
// Graph observed
  double xx[43] = {1000, 1100, 1200, 1300, 1400, 1500,1600, 1700, 1800, 2000, 2100, 2158, 2103.96, 2100, 1944.49, 1900, 1875.32, 1800, 1707.91, 1700, 1600, 1555.53, 1500, 1414.42, 1400, 1339.45, 1300, 1278.38, 1247.34, 1210.28, 1200, 1188.89, 1169.55, 1161.58, 1155.13, 1150.19, 1167.15, 1178.5, 1140.81};
  double yy[43] = {550.967, 559.444, 578.292, 588.126, 611.92, 599.587, 624.253, 628.242, 649.762, 684.474, 754.678, 800, 850, 852.324, 900, 936.971, 950, 979.088, 1000, 1001.79, 1035.22, 1050, 1064.67, 1100, 1107.83, 1150, 1178.62, 1200, 1250, 1300, 1320.99, 1350, 1400, 1450, 1500, 1550, 1600, 1800, 2000};
  TGraph* observed = new TGraph(39, xx, yy);
// end observed
   observed->SetName("Observed");
   observed->SetTitle("Observed");
   observed->SetFillColor(1);
   observed->SetLineWidth(5);
   observed->SetLineColor(kRed);
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

  TLatex* lumilabel = new TLatex(1300,1840,"#sqrt{s} = 7 TeV,   L_{int} = 4.7 fb^{-1}");
  lumilabel->SetTextSize(0.05);
  lumilabel->Draw("same");

  TLatex* cmslabel = new TLatex(700.,1840,"CMS");
  cmslabel->SetTextSize(0.05);
  cmslabel->Draw("same");



   c47->Modified();
   c47->cd();
   c47->SaveAs ("exclu_hadrpv4.7.pdf");
   c47->SaveAs ("exclu_hadrpv4.7.png");
}
