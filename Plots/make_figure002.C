{

  TString name_3mu="splitqb_outfile.root";
 
  //CMS Text Box
  Double_t latex_x=140.0;
  Double_t latex_y=0.22;
  Double_t latex_dy=0.015;
  TText *cmsPREM=new TText(latex_x,latex_y+latex_dy,"CMS Simulation");
  cmsPREM->SetTextSize(0.04);
  cmsPREM->SetTextAlign(12);
  //Lumi Box
  //TString latex_string="#sqrt{s} = 7 TeV, #int L.dt = 35 pb^{-1}";
  TString latex_string="#sqrt{s} = 7 TeV";
  TLatex l;
  l.SetTextAlign(12);
  l.SetTextSize(0.04);
  l.DrawLatex(latex_x,latex_y,latex_string);
  

  TFile *f3mu=new TFile(name_3mu);


  f3mu->cd();
  graph_expect_2mu_wmet->SetMinimum(0.0);
  graph_expect_2mu_wmet->Draw("AP");
  //Float_t my_text_size=0.11;
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetCanvasColor(kWhite);
  gStyle->SetCanvasDefH(600); //Height of canvas
  gStyle->SetCanvasDefW(600); //Width of canvas
  gStyle->SetCanvasDefX(0);   //POsition on screen
  gStyle->SetCanvasDefY(0);
  gStyle->SetPadBorderMode(0);
  // gStyle->SetPadBorderSize(Width_t size = 1);
  gStyle->SetPadColor(kWhite);
  gStyle->SetPadGridX(false);
  gStyle->SetPadGridY(false);
  gStyle->SetGridColor(0);
  gStyle->SetGridStyle(3);
  gStyle->SetGridWidth(1);
  gStyle->SetFrameBorderMode(0);
  gStyle->SetFrameBorderSize(1);
  gStyle->SetFrameFillColor(0);
  gStyle->SetFrameFillStyle(0);
  gStyle->SetFrameLineColor(1);
  gStyle->SetFrameLineStyle(1);
  gStyle->SetFrameLineWidth(1);
  //For Histo
  gStyle->SetHistLineColor(1);
  gStyle->SetHistLineStyle(0);
  gStyle->SetHistLineWidth(1);
  gStyle->SetEndErrorSize(2);
  gStyle->SetErrorX(0.);


  //gStyle->SetHistLineColor(1);
  //gStyle->SetHistLineStyle(0);
  //gStyle->SetHistLineWidth(1);
  //gStyle->SetHistFillStyle(0);
  //gStyle->SetMarkerStyle(20);


  //For Fit/function
  gStyle->SetOptFit(1); //RCG TOOK THIS OFF
  gStyle->SetFitFormat("5.4g");
  gStyle->SetFuncColor(2);
  gStyle->SetFuncStyle(1);
  gStyle->SetFuncWidth(1);

  //For the date
  gStyle->SetOptDate(0);
  //For Stat Box
  gStyle->SetOptFile(0);
  gStyle->SetOptStat(0); // To display the mean and RMS:   SetOptStat("mr");
  gStyle->SetStatColor(kWhite);
  gStyle->SetStatFont(42);
  gStyle->SetStatFontSize(0.025);
  gStyle->SetStatTextColor(1);
  gStyle->SetStatFormat("6.4g");
  gStyle->SetStatBorderSize(1);
  gStyle->SetStatH(0.1);
  gStyle->SetStatW(0.15);

  //Margins
  gStyle->SetPadTopMargin(0.05);
  gStyle->SetPadBottomMargin(0.13);
  gStyle->SetPadLeftMargin(0.16);
  gStyle->SetPadRightMargin(0.02);
  
  //For Global Title:
  gStyle->SetOptTitle(0);
  gStyle->SetTitleFont(42);
  gStyle->SetTitleColor(1);
  gStyle->SetTitleTextColor(1);
  gStyle->SetTitleFillColor(10);
  gStyle->SetTitleFontSize(0.05);

  //Axis titles:

  gStyle->SetTitleColor(1, "XYZ");
  gStyle->SetTitleFont(42, "XYZ");
  gStyle->SetTitleSize(0.06, "XYZ");
  // gStyle->SetTitleXSize(Float_t size = 0.02); // Another way to set the size?
  // gStyle->SetTitleYSize(Float_t size = 0.02);
  gStyle->SetTitleXOffset(0.9);
  gStyle->SetTitleYOffset(1.25);

  //For axis labels:
  gStyle->SetLabelColor(1, "XYZ");
  gStyle->SetLabelFont(42, "XYZ");
  gStyle->SetLabelOffset(0.007, "XYZ");
  gStyle->SetLabelSize(0.05, "XYZ");

  //For the axis:
  gStyle->SetAxisColor(1, "XYZ");
  gStyle->SetStripDecimals(kTRUE);
  gStyle->SetTickLength(0.03, "XYZ");
  gStyle->SetNdivisions(510, "XYZ");
  gStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
  gStyle->SetPadTickY(1);

  // Change for log plots:
  gStyle->SetOptLogx(0);
  gStyle->SetOptLogy(0);
  gStyle->SetOptLogz(0);

  //Postscript options
  gStyle->SetPaperSize(20.,20.);

  
  //gStyle->SetTitleX(10000);
  



  TH2D *h_hold=new TH2D("h_hold","SQB ;#Delta M  (GeV)            ; #sigma#timesBr#times#epsilon  (pb)            ",310,0.0,310,250,0.0,0.250);

  gStyle->cd();
  c1->UseCurrentStyle(); 
  h_hold->Draw();
  graph_expect_2mu_wmet->SetMarkerStyle(8);
  graph_expect_2mu_wmet->SetMarkerColor(kBlack);
  graph_expect_2mu_wmet->Draw("psame");
  graph_expect_2mu_wjt->SetMarkerColor(kBlack);
  graph_expect_2mu_wjt->Draw("psame");
  Double_t legx=0.775;
  Double_t legy=0.83;
  Double_t legx_delta=0.20;
  Double_t legy_delta=0.12;
  TLegend *myleg=new TLegend(legx,legy,legx+legx_delta,legy+legy_delta);
  myleg->AddEntry(graph_expect_2mu_wmet,"MET>50 GeV","p");
  myleg->AddEntry(graph_expect_2mu_wjt,"H_{T}>200 GeV","p");
  myleg->Draw();

  cmsPREM->Draw();
  l.DrawLatex(latex_x,latex_y,latex_string);
  

  c1->Print("Figure_002.pdf");
  c1->Print("Figure_002.eps");
  c1->Print("Figure_002.gif");
  c1->Print("Figure_002.png");




}
