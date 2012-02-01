{
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
   
// Graph exp2p
  double xx[] = {1288.78, 1282.86, 1298.32, 1314.89, 1330.19, 1349.53, 1400, 1400.66, 1399.62, 1500, 1600, 1700, 1800, 1900, 2000};
  double yy[] = {2000, 1900, 1800, 1700, 1600, 1500, 1401.71, 1400, 1300, 1177.7, 1120.44, 1090.9, 1072.66, 1062.09, 1055.31};
  TGraph* exp2p = new TGraph(15, xx, yy);
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
  double xx[] = {1123.49, 1137., 1145.9, 1163.15, 1171.26, 1189.97, 1200, 1203.97, 1240.82, 1300, 1400, 1500, 1600, 1700, 1800, 1900, 2000};
  double yy[] = {2000, 1900, 1800, 1700, 1600, 1500, 1426.83, 1400, 1300, 1101.8, 1024.68, 982.835, 971.936, 951.267, 947.094, 942.347, 947.845};
  TGraph* exp2m = new TGraph(17, xx, yy);
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
  double xx[] = {1275.07, 1286.03, 1301.78, 1306.67, 1314.99, 1333.16, 1377.24, 1398, 1400, 1500, 1600, 1700, 1800, 1900, 2000};
  double yy[] = {2000, 1900, 1800, 1700, 1600, 1500, 1400, 1300, 1292.83, 1158.88, 1112.35, 1083.94, 1068.05, 1060.99, 1054.31};
  TGraph* exp1p = new TGraph(15, xx, yy);
// end exp1p
   exp1p->SetName("Exp1p");
   exp1p->SetTitle("Exp1p");
   exp1p->SetFillColor(1);

   exp1p->SetLineColor(kAzure+5);
   exp1p->SetLineWidth(2);
   exp1p->SetMarkerStyle(8);
   
   
   //exp1p->Draw(gopt);
   
// Graph exp1m
   double xx[] = {1187.67, 1200, 1208.96, 1220.5, 1228.2, 1250.4, 1271.17, 1300, 1316.82, 1330., 1400, 1500, 1600, 1700, 1800, 1900, 2000};
  double yy[] = {2000, 1900, 1800, 1700, 1600, 1500, 1400, 1342.05, 1300, 1220., 1093.04, 1044.04, 1021.33, 999.295, 993.532, 987.666, 987.568};
  TGraph* exp1m = new TGraph(17, xx, yy);
// end exp1m
   exp1m->SetName("Exp1m");
   exp1m->SetTitle("Exp1m");
   exp1m->SetFillColor(1);

   exp1m->SetLineColor(kAzure+5);
   exp1m->SetLineWidth(2);
   exp1m->SetMarkerStyle(8);
   
   // exp1m->Draw(gopt);
   
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
  double xx[] = {1249.62, 1262.84, 1264.59, 1275.49, 1289.6, 1305.63, 1339.88, 1367.51, 1400, 1500, 1600, 1700, 1800, 1900, 2000};
  double yy[] = {2000, 1900, 1800, 1700, 1600, 1500, 1400, 1300, 1193.65, 1106.78, 1075.93, 1052.01, 1040.23, 1033.51, 1031.49};
  TGraph* expected = new TGraph(15, xx, yy);
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
  double xx[] = {1160.27, 1174, 1183.74, 1196.92, 1202.17, 1225.06, 1245.07, 1268, 1300, 1400, 1500, 1600, 1700, 1800, 1900, 2000};
  double yy[] = {2000, 1900, 1800, 1700, 1600, 1500, 1400, 1300, 1166.29, 1068.1, 1020.06, 998.525, 979.808, 976.135, 971.716, 973.225};
  TGraph* observed = new TGraph(16, xx, yy);
// end observed

   observed->SetName("Observed");
   observed->SetTitle("Observed");
   observed->SetFillColor(1);
   observed->SetLineWidth(5);
   observed->SetLineColor(kRed);
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

  TLatex* lumilabel = new TLatex(1300,2040,"#sqrt{s} = 7 TeV,   L_{int} = 4.7 fb^{-1}");
  lumilabel->SetTextSize(0.05);
  lumilabel->Draw("same");

  TLatex* cmslabel = new TLatex(1000.,2040,"CMS");
  cmslabel->SetTextSize(0.05);
  cmslabel->Draw("same");



   c47->Modified();
   c47->cd();
   //   c47->SetSelected(c);
   c47->SaveAs ("exclu_leprpv4.7.pdf");
   c47->SaveAs ("exclu_leprpv4.7.png");
}
