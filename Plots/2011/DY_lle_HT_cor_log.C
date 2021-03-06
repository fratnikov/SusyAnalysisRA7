{
//=========Macro generated from canvas: c1_n2/c1_n2
//=========  (Wed Oct 19 20:49:02 2011) by ROOT version5.28/00e
   TCanvas *c1_n2 = new TCanvas("c1_n2", "c1_n2",0,0,600,600);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   
   gStyle->SetErrorX(0.);
   
   gStyle->SetMarkerStyle(20);


   c1_n2->Range(-98.76542,-1.929326,518.5185,4.867355);
  
 c1_n2->SetFillColor(0);
  c1_n2->SetBorderMode(0);
  c1_n2->SetBorderSize(2);
  c1_n2->SetLogy();
  c1_n2->SetTickx(1);
  c1_n2->SetTicky(1);
  c1_n2->SetLeftMargin(0.16);
  c1_n2->SetRightMargin(0.06);
  c1_n2->SetTopMargin(0.1);
  c1_n2->SetBottomMargin(0.13);
  c1_n2->SetFrameFillStyle(0);
  c1_n2->SetFrameBorderMode(0);
  c1_n2->SetFrameFillStyle(0);
  c1_n2->SetFrameBorderMode(0);

   
   TH1F *hd_HT_mme = new TH1F("hd_HT_mme","",25,0,500);
   hd_HT_mme->SetBinContent(3,278);
   hd_HT_mme->SetBinContent(4,126);
   hd_HT_mme->SetBinContent(5,63);
   hd_HT_mme->SetBinContent(6,76);
   hd_HT_mme->SetBinContent(7,46);
   hd_HT_mme->SetBinContent(8,44);
   hd_HT_mme->SetBinContent(9,29);
   hd_HT_mme->SetBinContent(10,20);
   hd_HT_mme->SetBinContent(11,17);
   hd_HT_mme->SetBinContent(12,13);
   hd_HT_mme->SetBinContent(13,5);
   hd_HT_mme->SetBinContent(14,10);
   hd_HT_mme->SetBinContent(15,5);
   hd_HT_mme->SetBinContent(16,9);
   hd_HT_mme->SetBinContent(17,2);
   hd_HT_mme->SetBinContent(18,6);
   hd_HT_mme->SetBinContent(19,4);
   hd_HT_mme->SetBinContent(20,2);
   hd_HT_mme->SetBinContent(21,3);
   hd_HT_mme->SetBinContent(22,2);
   hd_HT_mme->SetBinContent(24,1);
   hd_HT_mme->SetBinContent(25,3);
   hd_HT_mme->SetBinContent(26,3);
   hd_HT_mme->SetMinimum(0.09);
   hd_HT_mme->SetMaximum(33691.57);
   hd_HT_mme->SetEntries(764);
   hd_HT_mme->SetLineStyle(0);
   hd_HT_mme->SetMarkerStyle(20);
   hd_HT_mme->GetXaxis()->SetTitle("H_{T} [GeV]");
  
   hd_HT_mme->GetXaxis()->SetLabelFont(42);
   hd_HT_mme->GetXaxis()->SetLabelOffset(0.007);
   hd_HT_mme->GetXaxis()->SetLabelSize(0.04);
   hd_HT_mme->GetXaxis()->SetTitleSize(0.04);
   hd_HT_mme->GetXaxis()->SetTitleOffset(1.25);
   hd_HT_mme->GetXaxis()->SetTitleFont(42);
   hd_HT_mme->GetYaxis()->SetTitle("Events/5GeV");
   hd_HT_mme->GetYaxis()->SetLabelFont(42);
   hd_HT_mme->GetYaxis()->SetLabelOffset(0.007);
   hd_HT_mme->GetYaxis()->SetLabelSize(0.04);
   hd_HT_mme->GetYaxis()->SetTitleSize(0.04);
   hd_HT_mme->GetYaxis()->SetTitleOffset(1.3);
   hd_HT_mme->GetYaxis()->SetTitleFont(42);
   hd_HT_mme->GetZaxis()->SetLabelFont(42);
   hd_HT_mme->GetZaxis()->SetLabelOffset(0.007);
   hd_HT_mme->GetZaxis()->SetLabelSize(0.05);
   hd_HT_mme->GetZaxis()->SetTitleSize(0.06);
   hd_HT_mme->GetZaxis()->SetTitleFont(42);

   hd_HT_mme->Draw("E1");
   
   THStack * abc= new THStack();
   abc->SetName("");
   abc->SetTitle("");
   
   TH1F *a2__2 = new TH1F("2__2","",25,0,500);
   a2__2->SetMinimum(0.1347663);
   a2__2->SetMaximum(539.0651);
   a2__2->SetDirectory(0);
   a2__2->SetStats(0);
   a2__2->SetLineStyle(0);
   a2__2->SetMarkerStyle(20);
   a2__2->GetXaxis()->SetLabelFont(42);
   a2__2->GetXaxis()->SetLabelOffset(0.007);
   a2__2->GetXaxis()->SetLabelSize(0.05);
   a2__2->GetXaxis()->SetTitleSize(0.06);
   a2__2->GetXaxis()->SetTitleOffset(0.9);
   a2__2->GetXaxis()->SetTitleFont(42);
   a2__2->GetYaxis()->SetLabelFont(42);
   a2__2->GetYaxis()->SetLabelOffset(0.007);
   a2__2->GetYaxis()->SetLabelSize(0.05);
   a2__2->GetYaxis()->SetTitleSize(0.06);
   a2__2->GetYaxis()->SetTitleOffset(1.25);
   a2__2->GetYaxis()->SetTitleFont(42);
   a2__2->GetZaxis()->SetLabelFont(42);
   a2__2->GetZaxis()->SetLabelOffset(0.007);
   a2__2->GetZaxis()->SetLabelSize(0.05);
   a2__2->GetZaxis()->SetTitleSize(0.06);
   a2__2->GetZaxis()->SetTitleFont(42);
   abc->SetHistogram(a2__2);
   
   
   TH1F *hd_HT_mme = new TH1F("hd_HT_mme_VVJets","hd_HT_mme",25,0,500);
   hd_HT_mme->SetBinContent(3,1.54578);
   hd_HT_mme->SetBinContent(4,0.7798532);
   hd_HT_mme->SetBinContent(5,0.4595563);
   hd_HT_mme->SetBinContent(6,0.3342228);
   hd_HT_mme->SetBinContent(7,0.1392595);
   hd_HT_mme->SetBinContent(8,0.3342228);
   hd_HT_mme->SetBinContent(9,0.1810373);
   hd_HT_mme->SetBinContent(10,0.09748165);
   hd_HT_mme->SetBinContent(11,0.1114076);
   hd_HT_mme->SetBinContent(12,0.01392595);
   hd_HT_mme->SetBinContent(13,0.0557038);
   hd_HT_mme->SetBinContent(14,0.04177785);
   hd_HT_mme->SetBinContent(15,0.0835557);
   hd_HT_mme->SetBinContent(16,0.04177785);
   hd_HT_mme->SetBinContent(17,0.09748165);
   hd_HT_mme->SetBinContent(18,0.0557038);
   hd_HT_mme->SetBinContent(19,0.0557038);
   hd_HT_mme->SetBinContent(20,0.0278519);
   hd_HT_mme->SetBinContent(21,0.01392595);
   hd_HT_mme->SetBinContent(23,0.01392595);
   hd_HT_mme->SetBinContent(24,0.01392595);
   hd_HT_mme->SetBinContent(25,0.01392595+0.04177785);
   hd_HT_mme->SetBinContent(26,0.04177785);
   hd_HT_mme->SetEntries(327);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#33ff33");
   hd_HT_mme->SetFillColor(ci);
   hd_HT_mme->SetLineStyle(0);
   hd_HT_mme->SetMarkerStyle(20);
   hd_HT_mme->GetXaxis()->SetLabelFont(42);
   hd_HT_mme->GetXaxis()->SetLabelOffset(0.007);
   hd_HT_mme->GetXaxis()->SetLabelSize(0.05);
   hd_HT_mme->GetXaxis()->SetTitleSize(0.06);
   hd_HT_mme->GetXaxis()->SetTitleOffset(0.9);
   hd_HT_mme->GetXaxis()->SetTitleFont(42);
   hd_HT_mme->GetYaxis()->SetLabelFont(42);
   hd_HT_mme->GetYaxis()->SetLabelOffset(0.007);
   hd_HT_mme->GetYaxis()->SetLabelSize(0.05);
   hd_HT_mme->GetYaxis()->SetTitleSize(0.06);
   hd_HT_mme->GetYaxis()->SetTitleOffset(1.25);
   hd_HT_mme->GetYaxis()->SetTitleFont(42);
   hd_HT_mme->GetZaxis()->SetLabelFont(42);
   hd_HT_mme->GetZaxis()->SetLabelOffset(0.007);
   hd_HT_mme->GetZaxis()->SetLabelSize(0.05);
   hd_HT_mme->GetZaxis()->SetTitleSize(0.06);
   hd_HT_mme->GetZaxis()->SetTitleFont(42);
   abc->Add(hd_HT_mme,"");
   
   TH1F *hd_HT_mme = new TH1F("hd_HT_mme_ttbar","hd_HT_mme",25,0,500);
   hd_HT_mme->SetBinContent(3,24.88241);
   hd_HT_mme->SetBinContent(4,15.63367);
   hd_HT_mme->SetBinContent(5,15.00464);
   hd_HT_mme->SetBinContent(6,19.36679);
   hd_HT_mme->SetBinContent(7,16.85595);
   hd_HT_mme->SetBinContent(8,13.51441);
   hd_HT_mme->SetBinContent(9,11.82824);
   hd_HT_mme->SetBinContent(10,8.771992);
   hd_HT_mme->SetBinContent(11,7.439404);
   hd_HT_mme->SetBinContent(12,8.228349);
   hd_HT_mme->SetBinContent(13,5.327725);
   hd_HT_mme->SetBinContent(14,3.134858);
   hd_HT_mme->SetBinContent(15,2.486947);
   hd_HT_mme->SetBinContent(16,2.282178);
   hd_HT_mme->SetBinContent(17,1.911149);
   hd_HT_mme->SetBinContent(18,2.430323);
   hd_HT_mme->SetBinContent(19,0.9092036);
   hd_HT_mme->SetBinContent(20,1.150768);
   hd_HT_mme->SetBinContent(21,1.007855);
   hd_HT_mme->SetBinContent(22,1.076998);
   hd_HT_mme->SetBinContent(23,0.7940879);
   hd_HT_mme->SetBinContent(24,0.6452338);
   hd_HT_mme->SetBinContent(25,0.1202489+2.359338);
   hd_HT_mme->SetBinContent(26,2.359338);
   hd_HT_mme->SetEntries(1315);

   ci = TColor::GetColor("#ff3333");
   //   hd_HT_mme->SetFillColor(ci);
   hd_HT_mme->SetFillColor(kMagenta);

   hd_HT_mme->SetLineStyle(0);
   hd_HT_mme->SetMarkerStyle(20);
   hd_HT_mme->GetXaxis()->SetLabelFont(42);
   hd_HT_mme->GetXaxis()->SetLabelOffset(0.007);
   hd_HT_mme->GetXaxis()->SetLabelSize(0.05);
   hd_HT_mme->GetXaxis()->SetTitleSize(0.06);
   hd_HT_mme->GetXaxis()->SetTitleOffset(0.9);
   hd_HT_mme->GetXaxis()->SetTitleFont(42);
   hd_HT_mme->GetYaxis()->SetLabelFont(42);
   hd_HT_mme->GetYaxis()->SetLabelOffset(0.007);
   hd_HT_mme->GetYaxis()->SetLabelSize(0.05);
   hd_HT_mme->GetYaxis()->SetTitleSize(0.06);
   hd_HT_mme->GetYaxis()->SetTitleOffset(1.25);
   hd_HT_mme->GetYaxis()->SetTitleFont(42);
   hd_HT_mme->GetZaxis()->SetLabelFont(42);
   hd_HT_mme->GetZaxis()->SetLabelOffset(0.007);
   hd_HT_mme->GetZaxis()->SetLabelSize(0.05);
   hd_HT_mme->GetZaxis()->SetTitleSize(0.06);
   hd_HT_mme->GetZaxis()->SetTitleFont(42);
   abc->Add(hd_HT_mme,"");
   
   TH1F *hd_HT_mme = new TH1F("hd_HT_mme","hd_HT_mme",25,0,500);

   ci = TColor::GetColor("#3333ff");
   hd_HT_mme->SetFillColor(ci);
   hd_HT_mme->SetLineStyle(0);
   hd_HT_mme->SetMarkerStyle(20);
   hd_HT_mme->GetXaxis()->SetLabelFont(42);
   hd_HT_mme->GetXaxis()->SetLabelOffset(0.007);
   hd_HT_mme->GetXaxis()->SetLabelSize(0.05);
   hd_HT_mme->GetXaxis()->SetTitleSize(0.06);
   hd_HT_mme->GetXaxis()->SetTitleOffset(0.9);
   hd_HT_mme->GetXaxis()->SetTitleFont(42);
   hd_HT_mme->GetYaxis()->SetLabelFont(42);
   hd_HT_mme->GetYaxis()->SetLabelOffset(0.007);
   hd_HT_mme->GetYaxis()->SetLabelSize(0.05);
   hd_HT_mme->GetYaxis()->SetTitleSize(0.06);
   hd_HT_mme->GetYaxis()->SetTitleOffset(1.25);
   hd_HT_mme->GetYaxis()->SetTitleFont(42);
   hd_HT_mme->GetZaxis()->SetLabelFont(42);
   hd_HT_mme->GetZaxis()->SetLabelOffset(0.007);
   hd_HT_mme->GetZaxis()->SetLabelSize(0.05);
   hd_HT_mme->GetZaxis()->SetTitleSize(0.06);
   hd_HT_mme->GetZaxis()->SetTitleFont(42);
   abc->Add(hd_HT_mme,"");
   
   TH1F *hd_HT_mme = new TH1F("hd_HT_mme","hd_HT_mme",25,0,500);
   hd_HT_mme->SetBinContent(3,23.17246);
   hd_HT_mme->SetBinContent(4,4.634492);
   hd_HT_mme->SetBinContent(5,4.634492);
   hd_HT_mme->SetEntries(7);

   ci = TColor::GetColor("#ffff33");
   hd_HT_mme->SetFillColor(ci);

   ci = TColor::GetColor("#ffff33");
   hd_HT_mme->SetLineColor(ci);
   hd_HT_mme->SetLineStyle(0);
   hd_HT_mme->SetMarkerStyle(20);
   hd_HT_mme->GetXaxis()->SetLabelFont(42);
   hd_HT_mme->GetXaxis()->SetLabelOffset(0.007);
   hd_HT_mme->GetXaxis()->SetLabelSize(0.05);
   hd_HT_mme->GetXaxis()->SetTitleSize(0.06);
   hd_HT_mme->GetXaxis()->SetTitleOffset(0.9);
   hd_HT_mme->GetXaxis()->SetTitleFont(42);
   hd_HT_mme->GetYaxis()->SetLabelFont(42);
   hd_HT_mme->GetYaxis()->SetLabelOffset(0.007);
   hd_HT_mme->GetYaxis()->SetLabelSize(0.05);
   hd_HT_mme->GetYaxis()->SetTitleSize(0.06);
   hd_HT_mme->GetYaxis()->SetTitleOffset(1.25);
   hd_HT_mme->GetYaxis()->SetTitleFont(42);
   hd_HT_mme->GetZaxis()->SetLabelFont(42);
   hd_HT_mme->GetZaxis()->SetLabelOffset(0.007);
   hd_HT_mme->GetZaxis()->SetLabelSize(0.05);
   hd_HT_mme->GetZaxis()->SetTitleSize(0.06);
   hd_HT_mme->GetZaxis()->SetTitleFont(42);
   abc->Add(hd_HT_mme,"");
   
   TH1F *hd_HT_mme = new TH1F("hd_HT_mme","hd_HT_mme",25,0,500);
   hd_HT_mme->SetBinContent(3,287.3151);
   hd_HT_mme->SetBinContent(4,100.7625);
   hd_HT_mme->SetBinContent(5,71.13127);
   hd_HT_mme->SetBinContent(6,55.89175);
   hd_HT_mme->SetBinContent(7,35.54599);
   hd_HT_mme->SetBinContent(8,22.48158);
   hd_HT_mme->SetBinContent(9,16.30529);
   hd_HT_mme->SetBinContent(10,10.32636);
   hd_HT_mme->SetBinContent(11,7.759389);
   hd_HT_mme->SetBinContent(12,9.886882);
   hd_HT_mme->SetBinContent(13,8.006184);
   hd_HT_mme->SetBinContent(14,5.380677);
   hd_HT_mme->SetBinContent(15,5.949743);
   hd_HT_mme->SetBinContent(16,2.968635);
   hd_HT_mme->SetBinContent(17,2.514755);
   hd_HT_mme->SetBinContent(18,2.650596);
   hd_HT_mme->SetBinContent(19,1.25835);
   hd_HT_mme->SetBinContent(20,0.9912916);
   hd_HT_mme->SetBinContent(21,0.999126);
   hd_HT_mme->SetBinContent(22,1.10764);
   hd_HT_mme->SetBinContent(23,1.705976);
   hd_HT_mme->SetBinContent(24,0.136766);
   hd_HT_mme->SetBinContent(25,0.136766+3.595469);
   hd_HT_mme->SetBinContent(26,3.595469);
   hd_HT_mme->SetEntries(3163);

   ci = TColor::GetColor("#ffff33");
   hd_HT_mme->SetFillColor(ci);
   hd_HT_mme->SetLineStyle(0);
   hd_HT_mme->SetMarkerStyle(20);
   hd_HT_mme->GetXaxis()->SetLabelFont(42);
   hd_HT_mme->GetXaxis()->SetLabelOffset(0.007);
   hd_HT_mme->GetXaxis()->SetLabelSize(0.05);
   hd_HT_mme->GetXaxis()->SetTitleSize(0.06);
   hd_HT_mme->GetXaxis()->SetTitleOffset(0.9);
   hd_HT_mme->GetXaxis()->SetTitleFont(42);
   hd_HT_mme->GetYaxis()->SetLabelFont(42);
   hd_HT_mme->GetYaxis()->SetLabelOffset(0.007);
   hd_HT_mme->GetYaxis()->SetLabelSize(0.05);
   hd_HT_mme->GetYaxis()->SetTitleSize(0.06);
   hd_HT_mme->GetYaxis()->SetTitleOffset(1.25);
   hd_HT_mme->GetYaxis()->SetTitleFont(42);
   hd_HT_mme->GetZaxis()->SetLabelFont(42);
   hd_HT_mme->GetZaxis()->SetLabelOffset(0.007);
   hd_HT_mme->GetZaxis()->SetLabelSize(0.05);
   hd_HT_mme->GetZaxis()->SetTitleSize(0.06);
   hd_HT_mme->GetZaxis()->SetTitleFont(42);
   abc->Add(hd_HT_mme,"");
   abc->Draw("same");
   
   TH1F *hd_HT_mme = new TH1F("hd_HT_mme","",25,0,500);
   hd_HT_mme->SetBinContent(3,278);
   hd_HT_mme->SetBinContent(4,126);
   hd_HT_mme->SetBinContent(5,63);
   hd_HT_mme->SetBinContent(6,76);
   hd_HT_mme->SetBinContent(7,46);
   hd_HT_mme->SetBinContent(8,44);
   hd_HT_mme->SetBinContent(9,29);
   hd_HT_mme->SetBinContent(10,20);
   hd_HT_mme->SetBinContent(11,17);
   hd_HT_mme->SetBinContent(12,13);
   hd_HT_mme->SetBinContent(13,5);
   hd_HT_mme->SetBinContent(14,10);
   hd_HT_mme->SetBinContent(15,5);
   hd_HT_mme->SetBinContent(16,9);
   hd_HT_mme->SetBinContent(17,2);
   hd_HT_mme->SetBinContent(18,6);
   hd_HT_mme->SetBinContent(19,4);
   hd_HT_mme->SetBinContent(20,2);
   hd_HT_mme->SetBinContent(21,3);
   hd_HT_mme->SetBinContent(22,2);
   hd_HT_mme->SetBinContent(24,1);
   hd_HT_mme->SetBinContent(25,3);
   hd_HT_mme->SetBinContent(26,3);
   hd_HT_mme->SetMinimum(0.09);
   hd_HT_mme->SetMaximum(33691.57);
   hd_HT_mme->SetEntries(764);
   hd_HT_mme->SetLineStyle(0);
   hd_HT_mme->SetMarkerStyle(20);
   hd_HT_mme->GetXaxis()->SetTitle("H_{T} [GeV]");
   hd_HT_mme->GetXaxis()->SetLabelFont(42);
   hd_HT_mme->GetXaxis()->SetLabelOffset(0.007);
   hd_HT_mme->GetXaxis()->SetLabelSize(0.05);
   hd_HT_mme->GetXaxis()->SetTitleSize(0.06);
   hd_HT_mme->GetXaxis()->SetTitleOffset(0.9);
   hd_HT_mme->GetXaxis()->SetTitleFont(42);
   hd_HT_mme->GetYaxis()->SetTitle("Events/20GeV");
   hd_HT_mme->GetYaxis()->SetLabelFont(42);
   hd_HT_mme->GetYaxis()->SetLabelOffset(0.007);
   hd_HT_mme->GetYaxis()->SetLabelSize(0.03);
   hd_HT_mme->GetYaxis()->SetTitleOffset(1.25);
   hd_HT_mme->GetYaxis()->SetTitleFont(42);
   hd_HT_mme->GetZaxis()->SetLabelFont(42);
   hd_HT_mme->GetZaxis()->SetLabelOffset(0.007);
   hd_HT_mme->GetZaxis()->SetLabelSize(0.05);
   hd_HT_mme->GetZaxis()->SetTitleSize(0.06);
   hd_HT_mme->GetZaxis()->SetTitleFont(42);
   hd_HT_mme->Draw("E1 same");
   
   TLegend *leg = new TLegend(0.6,0.5,0.91,0.85,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(42);
   leg->SetTextSize(0.04);
   leg->SetLineColor(0);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(4000);

  
   TLegendEntry *entry=leg->AddEntry("hd_HT_mme","DATA","pl");
   entry->SetLineColor(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("hd_HT_mme_VVJets","VV+Jets","f");

   ci = TColor::GetColor("#33ff33");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);
   entry->SetLineColor(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("hd_HT_mme_ttbar","t#bar{t}+Jets","f");

   ci = TColor::GetColor("#ff3333");
   // entry->SetFillColor(ci);
   entry->SetFillColor(kMagenta);

   entry->SetFillStyle(1001);
   entry->SetLineColor(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("hd_HT_mme_DYJets","DY+Jets","f");

   ci = TColor::GetColor("#ffff33");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);
   entry->SetLineColor(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   leg->Draw();
 

 TLatex *   tex = new TLatex(0,38000,"CMS preliminary");
   tex->SetTextAlign(10);
   tex->SetLineWidth(2);
   tex->SetTextFont(42);
   tex->SetTextSize(0.04);
   tex->Draw();
   TLatex *   tex = new TLatex(300,38000,"#sqrt{s}=7TeV,  L_{int}=2.1fb^{-1}");
   tex->SetTextAlign(10);
   tex->SetLineWidth(2);
   tex->SetTextFont(42);
   tex->SetTextSize(0.04);
   tex->Draw();

   c1_n2->Modified();
   c1_n2->cd();
   c1_n2->SetSelected(c1_n2);


   gPad->RedrawAxis();

}
