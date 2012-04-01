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
  
   TH2D *frame = new TH2D("frame","",1,900,2000,1,600,2000);
   frame->SetStats(0);
   frame->SetMarkerStyle(12);
   frame->GetXaxis()->SetTitle("m_{#tilde{q}} (GeV/c^{2})   ");
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
  double xx[] = {1179.54, 1214.77, 1201.46, 1213.22, 1220.36, 1241.04, 1264.1, 1311.83, 1400, 1500, 1600, 1700, 1800, 1900, 2000, 2100};
  double yy[] = {2000, 1900, 1800, 1700, 1600, 1500, 1400, 1300, 1088.86, 1038.46, 1014.97, 993.942, 987.138, 983.672, 984.539, 1005.36};
  TGraph* observed = new TGraph(16, xx, yy);
  observed->RemovePoint (1);
// end observed

// Graph expected
  double xx[] = {1254.79, 1270.07, 1278.93, 1288.71, 1298.32, 1317.44, 1357.01, 1376.4, 1410.68, 1500, 1600, 1700, 1800, 1900, 2000, 2100};
  double yy[] = {2000, 1900, 1800, 1700, 1600, 1500, 1400, 1300, 1200, 1125.88, 1089.82, 1065.66, 1051.37, 1041.46, 1036.95, 1049.71};
  TGraph* expected = new TGraph(16, xx, yy);
// end expected

// Graph exp1p
  double xx[] = {1286.76, 1295.64, 1313.52, 1323.68, 1335.77, 1358.49, 1399.32, 1400, 1408.46, 1500, 1600, 1700, 1800, 1900, 2000, 2100};
  double yy[] = {2000, 1900, 1800, 1700, 1600, 1500, 1400, 1393.43, 1300, 1169.55, 1121.28, 1093.35, 1079.96, 1069.15, 1062.04, 1065.82};
  TGraph* exp1p = new TGraph(16, xx, yy);
// end exp1p

// Graph exp1m
  double xx[] = {1204.11, 1230.42, 1223.97, 1235.56, 1245.08, 1264.16, 1286.51, 1329.77, 1400, 1500, 1600, 1700, 1800, 1900, 2000, 2100};
  double yy[] = {2000, 1900, 1800, 1700, 1600, 1500, 1400, 1300, 1115.33, 1059.75, 1034.94, 1013, 1005.41, 999.848, 997.869, 1016.91};
  TGraph* exp1m = new TGraph(16, xx, yy);
  exp1m->RemovePoint (1);
// end exp1m

// Graph exp2p
  double xx[] = {1311.1, 1313.82, 1329.93, 1342.31, 1356.27, 1381, 1400, 1412.86, 1423.7, 1500, 1600, 1700, 1800, 1900, 2000, 2100};
  double yy[] = {2000, 1900, 1800, 1700, 1600, 1500, 1443, 1400, 1300, 1204.59, 1143.92, 1116.37, 1102.16, 1090.76, 1068.14, 1066.55};
  TGraph* exp2p = new TGraph(16, xx, yy);
// end exp2p

// Graph exp2m
  double xx[] = {1142.84, 1175.45, 1166.31, 1178.75, 1184.31, 1200, 1207.55, 1222.92, 1300, 1400, 1500, 1600, 1700, 1800, 1900, 2000};
  double yy[] = {2000, 1900, 1800, 1700, 1600, 1529.88, 1500, 1400, 1133.75, 1048.34, 997.346, 984.752, 967.314, 962.85, 956.984, 959.367};
  TGraph* exp2m = new TGraph(16, xx, yy);
  exp2m->RemovePoint (1);
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
   
   // exp1m->Draw(gopt);
   
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
   
  TLegend* myleg = new TLegend(0.60,0.65,0.75,0.85,"95% C.L. CLs Limits","brNDC");;

 
  myleg->SetFillColor(0); 
  myleg->SetShadowColor(0);
  myleg->SetTextSize(0.035);
  myleg->SetBorderSize(0);

  myleg->AddEntry(observed,"NLO observed","l");
  myleg->AddEntry(expectedStyle1,"NLO expected #pm1#sigma","lf");
  myleg->AddEntry(expectedStyle2,"NLO expected #pm2#sigma","lf");
  myleg->Draw();

  TLatex* lumilabel = new TLatex(1400,2040,"#sqrt{s} = 7 TeV,   L_{int} = 5.0 fb^{-1}");
  lumilabel->SetTextSize(0.05);
  lumilabel->Draw("same");

  TLatex* cmslabel = preliminary ? 
    new TLatex(900.,2040,"CMS Preliminary") :
    new TLatex(1000.,2040,"CMS");
  cmslabel->SetTextSize(0.05);
  cmslabel->Draw("same");



   c47->Modified();
   c47->cd();
   //   c47->SetSelected(c);
   c47->SaveAs ("exclu_leprpv4.7.pdf");
   c47->SaveAs ("exclu_leprpv4.7.png");
}
