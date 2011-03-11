{
//=========Macro generated from canvas: c1/c1
//=========  (Tue Oct 26 19:17:01 2010) by ROOT version5.18/00b
#include "tdrstyle.C"
  setTDRStyle();
  tdrStyle->SetPadTopMargin(0.08);
  tdrStyle->SetPadBottomMargin(0.13);
  tdrStyle->SetPadLeftMargin(0.15);
  tdrStyle->SetPadRightMargin(0.18);


  gStyle->SetPalette(1);
  gStyle->SetOptTitle(kFALSE);

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

   hbranching->SetBinContent(1,12.581);
   hbranching->SetBinContent(2,12.319);
   hbranching->SetBinContent(3,11.964);
   hbranching->SetBinContent(4,11.837);
   hbranching->SetBinContent(5,11.739);
   hbranching->SetBinContent(6,11.701);
   hbranching->SetBinContent(7,11.667);
   hbranching->SetBinContent(8,11.651);
   hbranching->SetBinContent(9,11.49);
   hbranching->SetBinContent(10,11.516);
   hbranching->SetBinContent(11,11.473);
   hbranching->SetBinContent(12,11.455);
   hbranching->SetBinContent(15,1.71);
   hbranching->SetBinContent(16,1.609);
   hbranching->SetBinContent(17,1.54);
   hbranching->SetBinContent(18,1.502);
   hbranching->SetBinContent(19,1.481);
   hbranching->SetBinContent(20,1.459);
   hbranching->SetBinContent(21,1.46);
   hbranching->SetBinContent(22,1.445);
   hbranching->SetBinContent(23,1.446);
   hbranching->SetBinContent(24,1.442);
   hbranching->SetBinContent(25,1.422);
   hbranching->SetBinContent(26,1.428);
   hbranching->SetBinContent(29,1.199);
   hbranching->SetBinContent(30,1.096);
   hbranching->SetBinContent(31,1.048);
   hbranching->SetBinContent(32,1.007);
   hbranching->SetBinContent(33,0.9938);
   hbranching->SetBinContent(34,0.9727);
   hbranching->SetBinContent(35,0.9629);
   hbranching->SetBinContent(36,0.9525);
   hbranching->SetBinContent(37,0.9488);
   hbranching->SetBinContent(38,0.9425);
   hbranching->SetBinContent(39,0.9442);
   hbranching->SetBinContent(40,0.9369);
   hbranching->SetBinContent(43,0.8762);
   hbranching->SetBinContent(44,0.7782);
   hbranching->SetBinContent(45,0.7175);
   hbranching->SetBinContent(46,0.689);
   hbranching->SetBinContent(47,0.6697);
   hbranching->SetBinContent(48,0.6585);
   hbranching->SetBinContent(49,0.649);
   hbranching->SetBinContent(50,0.642);
   hbranching->SetBinContent(51,0.6322);
   hbranching->SetBinContent(52,0.6264);
   hbranching->SetBinContent(53,0.6289);
   hbranching->SetBinContent(54,0.63);
   hbranching->SetBinContent(57,0.6658);
   hbranching->SetBinContent(58,0.5596);
   hbranching->SetBinContent(59,0.5056);
   hbranching->SetBinContent(60,0.4855);
   hbranching->SetBinContent(61,0.466);
   hbranching->SetBinContent(62,0.4539);
   hbranching->SetBinContent(63,0.4448);
   hbranching->SetBinContent(64,0.4361);
   hbranching->SetBinContent(65,0.4309);
   hbranching->SetBinContent(66,0.4266);
   hbranching->SetBinContent(67,0.4231);
   hbranching->SetBinContent(68,0.4235);
   hbranching->SetBinContent(71,0.5207);
   hbranching->SetBinContent(72,0.4165);
   hbranching->SetBinContent(73,0.3685);
   hbranching->SetBinContent(74,0.3375);
   hbranching->SetBinContent(75,0.3252);
   hbranching->SetBinContent(76,0.3099);
   hbranching->SetBinContent(77,0.3048);
   hbranching->SetBinContent(78,0.2981);
   hbranching->SetBinContent(79,0.298);
   hbranching->SetBinContent(80,0.2942);
   hbranching->SetBinContent(81,0.2888);
   hbranching->SetBinContent(82,0.2895);
   hbranching->SetBinContent(85,0.4289);
   hbranching->SetBinContent(86,0.3238);
   hbranching->SetBinContent(87,0.2772);
   hbranching->SetBinContent(88,0.2476);
   hbranching->SetBinContent(89,0.2308);
   hbranching->SetBinContent(90,0.2207);
   hbranching->SetBinContent(91,0.214);
   hbranching->SetBinContent(92,0.2089);
   hbranching->SetBinContent(93,0.2069);
   hbranching->SetBinContent(94,0.2057);
   hbranching->SetBinContent(95,0.2026);
   hbranching->SetBinContent(96,0.2027);
   hbranching->SetBinContent(99,0.3688);
   hbranching->SetBinContent(100,0.2652);
   hbranching->SetBinContent(101,0.2137);
   hbranching->SetBinContent(102,0.1833);
   hbranching->SetBinContent(103,0.1681);
   hbranching->SetBinContent(104,0.1586);
   hbranching->SetBinContent(105,0.1527);
   hbranching->SetBinContent(106,0.1479);
   hbranching->SetBinContent(107,0.1464);
   hbranching->SetBinContent(108,0.1435);
   hbranching->SetBinContent(109,0.1429);
   hbranching->SetBinContent(110,0.1405);
   hbranching->SetBinContent(113,0.3242);
   hbranching->SetBinContent(114,0.2213);
   hbranching->SetBinContent(115,0.171);
   hbranching->SetBinContent(116,0.1429);
   hbranching->SetBinContent(117,0.1271);
   hbranching->SetBinContent(118,0.1176);
   hbranching->SetBinContent(119,0.1114);
   hbranching->SetBinContent(120,0.1058);
   hbranching->SetBinContent(121,0.1039);
   hbranching->SetBinContent(122,0.1022);
   hbranching->SetBinContent(123,0.1008);
   hbranching->SetBinContent(124,0.1009);
   hbranching->SetBinContent(127,0.2946);
   hbranching->SetBinContent(128,0.1935);
   hbranching->SetBinContent(129,0.1403);
   hbranching->SetBinContent(130,0.1133);
   hbranching->SetBinContent(131,0.0975);
   hbranching->SetBinContent(132,0.0886);
   hbranching->SetBinContent(133,0.0824);
   hbranching->SetBinContent(134,0.0785);
   hbranching->SetBinContent(135,0.0765);
   hbranching->SetBinContent(136,0.0739);
   hbranching->SetBinContent(137,0.0722);
   hbranching->SetBinContent(138,0.0711);
   hbranching->SetBinContent(141,0.2788);
   hbranching->SetBinContent(142,0.171);
   hbranching->SetBinContent(143,0.1202);
   hbranching->SetBinContent(144,0.0941);
   hbranching->SetBinContent(145,0.0778);
   hbranching->SetBinContent(146,0.068);
   hbranching->SetBinContent(147,0.0625);
   hbranching->SetBinContent(148,0.0582);
   hbranching->SetBinContent(149,0.0557);
   hbranching->SetBinContent(150,0.0542);
   hbranching->SetBinContent(151,0.052);
   hbranching->SetBinContent(152,0.0519);
   hbranching->SetBinContent(155,0.2692);
   hbranching->SetBinContent(156,0.1586);
   hbranching->SetBinContent(157,0.1057);
   hbranching->SetBinContent(158,0.0787);
   hbranching->SetBinContent(159,0.0633);
   hbranching->SetBinContent(160,0.0535);
   hbranching->SetBinContent(161,0.0481);
   hbranching->SetBinContent(162,0.0438);
   hbranching->SetBinContent(163,0.0414);
   hbranching->SetBinContent(164,0.0397);
   hbranching->SetBinContent(165,0.0384);
   hbranching->SetBinContent(166,0.0373);
   hbranching->SetBinContent(169,0.2571);
   hbranching->SetBinContent(170,0.1483);
   hbranching->SetBinContent(171,0.0968);
   hbranching->SetBinContent(172,0.0687);
   hbranching->SetBinContent(173,0.0532);
   hbranching->SetBinContent(174,0.0437);
   hbranching->SetBinContent(175,0.0378);
   hbranching->SetBinContent(176,0.034);
   hbranching->SetBinContent(177,0.0318);
   hbranching->SetBinContent(178,0.0298);
   hbranching->SetBinContent(179,0.0283);
   hbranching->SetBinContent(180,0.0276);
   hbranching->SetBinContent(183,0.2544);
   hbranching->SetBinContent(184,0.1423);
   hbranching->SetBinContent(185,0.0889);
   hbranching->SetBinContent(186,0.0607);
   hbranching->SetBinContent(187,0.046);
   hbranching->SetBinContent(188,0.0359);
   hbranching->SetBinContent(189,0.0305);
   hbranching->SetBinContent(190,0.027);
   hbranching->SetBinContent(191,0.0246);
   hbranching->SetBinContent(192,0.0228);
   hbranching->SetBinContent(193,0.0215);
   hbranching->SetBinContent(194,0.0206);
   hbranching->SetBinContent(197,0.2494);
   hbranching->SetBinContent(198,0.1385);
   hbranching->SetBinContent(199,0.0846);
   hbranching->SetBinContent(200,0.0564);
   hbranching->SetBinContent(201,0.0405);
   hbranching->SetBinContent(202,0.0314);
   hbranching->SetBinContent(203,0.0255);
   hbranching->SetBinContent(204,0.0218);
   hbranching->SetBinContent(205,0.0193);
   hbranching->SetBinContent(206,0.0175);
   hbranching->SetBinContent(207,0.0164);
   hbranching->SetBinContent(208,0.0156);
   hbranching->SetBinContent(211,0.2462);
   hbranching->SetBinContent(212,0.1357);
   hbranching->SetBinContent(213,0.081);
   hbranching->SetBinContent(214,0.0529);
   hbranching->SetBinContent(215,0.0369);
   hbranching->SetBinContent(216,0.0276);
   hbranching->SetBinContent(217,0.0219);
   hbranching->SetBinContent(218,0.0182);
   hbranching->SetBinContent(219,0.0158);
   hbranching->SetBinContent(220,0.0141);
   hbranching->SetBinContent(221,0.0128);
   hbranching->SetBinContent(222,0.0238);
   hbranching->SetEntries(219);
 

   hbranching->GetZaxis()->SetRangeUser(0,0.6);
   hbranching->GetZaxis()->SetTitle(" #sigma_{NLO}  (pb)   ");
   hbranching->GetXaxis()->SetTitle("Chargino Mass  (GeV/c^{2})   ");
   hbranching->GetYaxis()->SetTitle("Gluino Mass  (GeV/c^{2})   ");
    hbranching->GetYaxis()->SetTitleOffset(1.1);
    hbranching->GetXaxis()->SetTitleOffset(0.9);

   hbranching->GetZaxis()->SetTitleOffset(0.9);


   hbranching->Draw("colz");




   TLegend *leg = new TLegend(0.37,0.6,0.84,0.75,"95% C.L. Limits:","brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(42);
   leg->SetTextColor(10);
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
   

 


   Double_t *dum = 0;
   TPolyLine *pline = new TPolyLine(62,dum,dum,"");
   pline->SetFillColor(8);
   pline->SetLineColor(kBlack);
   pline->SetLineStyle(7);
   pline->SetLineWidth(5);

  //  pline->SetPoint(0,300,1130);
//    pline->SetPoint(1,350,1120);
//    pline->SetPoint(2,400,1100);
//    pline->SetPoint(3,450,1080);
//    pline->SetPoint(4,500,1060);
//    pline->SetPoint(5,550,1050);
//    pline->SetPoint(6,600,1045);
//    pline->SetPoint(7,650,1040);
//    pline->SetPoint(8,700,1040);
//    pline->SetPoint(9,750,1040);
//    pline->SetPoint(10,800,1040);
//    pline->SetPoint(11,850,1040);
//    pline->SetPoint(12,900,1040);

   pline->SetPoint(0,300,1280);
   pline->SetPoint(1,350,1120);
   pline->SetPoint(2,400,1080);
   pline->SetPoint(3,450,1070);
   pline->SetPoint(4,500,1065);
   pline->SetPoint(5,550,1065);
   pline->SetPoint(6,600,1065);
   pline->SetPoint(7,650,1065);
   pline->SetPoint(8,700,1065);
   pline->SetPoint(9,750,1064);
   pline->SetPoint(10,800,1063);
   pline->SetPoint(11,850,1062);
   pline->SetPoint(12,900,1061);

  
   pline->Draw("");

   TLegendEntry *entry=leg->AddEntry(pline,"CMS NLO expected","l");
   entry->SetFillColor(0);
   entry->SetFillStyle(1001);
   entry->SetLineColor(0);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(0);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextColor(10);


   Double_t *dum = 0;
   TPolyLine *pline = new TPolyLine(62,dum,dum,"");
   pline->SetFillColor(8);
   pline->SetLineColor(kBlack);
   pline->SetLineStyle(0);
   pline->SetLineWidth(5);

  pline->SetPoint(0,300,1065);
  pline->SetPoint(1,350,1053);
  pline->SetPoint(2,400,1041);
  pline->SetPoint(3,450,1040);
  pline->SetPoint(4,500,1040);
  pline->SetPoint(5,550,1040);
  pline->SetPoint(6,600,1040);
  pline->SetPoint(7,650,1040);
  pline->SetPoint(8,700,1040);
  pline->SetPoint(9,750,1040);
  pline->SetPoint(10,800,1039);
  pline->SetPoint(11,850,1038);
  pline->SetPoint(12,900,1037);
  pline->Draw("");


   TLegendEntry *entry=leg->AddEntry(pline,"CMS NLO  excluded","l");
   entry->SetFillColor(0);
   entry->SetFillStyle(1001);
   entry->SetLineColor(5);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(5);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextColor(10);
   leg->Draw();


 Double_t *dum = 0;
   TPolyLine *pline = new TPolyLine(62,dum,dum,"");
   pline->SetFillColor(8);
   pline->SetLineColor(kBlack);
   pline->SetLineStyle(5);
   pline->SetLineWidth(5);

  pline->SetPoint(0,300,1025);
  pline->SetPoint(1,350,1019);
  pline->SetPoint(2,400,1018);
  pline->SetPoint(3,450,1018);
  pline->SetPoint(4,500,1020);
  pline->SetPoint(5,550,1020);
  pline->SetPoint(6,600,1020);
  pline->SetPoint(7,650,1020);
  pline->SetPoint(8,700,1020);
  pline->SetPoint(9,750,1020);
  pline->SetPoint(10,800,1019);
  pline->SetPoint(11,850,1018);
  pline->SetPoint(12,900,1019);

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
   entry->SetTextColor(10);
   leg->Draw();

 



  int coord=520;
  //   TLatex *   tex = new TLatex(coord,1400,"#sqrt{s}=7TeV, L=35pb^{-1}");
   TLatex *   tex = new TLatex(600,1600,"L_{int} = 35 pb^{-1}, #sqrt{s} = 7 TeV");
   tex->SetTextColor(1);
   tex->SetTextAlign(10);
   tex->SetTextSize(0.05);
   tex->SetTextFont(42);
   tex->SetLineWidth(2);
   tex->Draw();
   //  tex = new TLatex(coord,1450,"CMS preliminary");
   tex = new TLatex(340,1600,"CMS preliminary");
   tex->SetTextColor(1);
   tex->SetTextAlign(10);
   tex->SetTextSize(0.05);
   tex->SetTextFont(42);
   tex->SetLineWidth(2);
   tex->Draw();
   // tex = new TLatex(13.62961,277.0205,"mSUGRA: tan#beta = 3, A_{0} = 0, #mu > 0");
   // tex->SetTextColor(0);
   // tex->SetTextAlign(10);
   // tex->SetTextSize(0.04);
   // tex->SetLineWidth(2);
   // tex->Draw();

 
   // tex = new TLatex(105,186,"#chi #rightarrow ll#chi^{1}_{0}");
   // tex->SetTextColor(kBlack);
   // tex->SetTextAlign(10);
   // tex->SetTextSize(0.03);
   // tex->SetLineWidth(2);
   // tex->Draw();
   
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
   //c1->SetLogz();
   c1->SetSelected(c1);
   //c1->SetLogz();
   c1->SetTickx();
   c1->SetTicky();
   c1->SaveAs("RA7_GGM_ExclusionLimit_plot2.pdf");
   c1->SaveAs("RA7_GGM_ExclusionLimit_plot2.png");
   c1->SaveAs("RA7_GGM_ExclusionLimit_plot2.eps");






}
