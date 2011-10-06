{
//=========Macro generated from canvas: c/interpret
//=========  (Fri Aug 26 19:52:37 2011) by ROOT version5.30/01
   TCanvas *c = new TCanvas("c", "interpret",5,48,800,600);
   gStyle->SetOptFit(1);
   c->Range(288.8889,984.8101,983.3333,1870.886);
   c->SetFillColor(0);
   c->SetBorderMode(0);
   c->SetBorderSize(2);
   c->SetTickx(1);
   c->SetTicky(1);
   c->SetLeftMargin(0.16);
   c->SetRightMargin(0.12);
   c->SetTopMargin(0.08);
   c->SetBottomMargin(0.13);
   c->SetFrameFillStyle(0);
   c->SetFrameBorderMode(0);
   c->SetFrameFillStyle(0);
   c->SetFrameBorderMode(0);
   
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
  double xx[18] = {900, 875, 850, 825, 800, 775, 750, 725, 700, 675, 650, 625, 614.703, 606.91, 599.335, 596.595, 600.148, 590.559};
  double yy[18] = {1621.71, 1619.46, 1616.47, 1615.57, 1614.87, 1620.36, 1625.57, 1630.58, 1633.64, 1647.31, 1685.59, 1731.77, 1750, 1800, 1850, 1900, 1950, 2000};
  TGraph* observed = new TGraph(18, xx, yy);
// end observed
   observed->SetName("Observed");
   observed->SetTitle("Observed");
   observed->SetFillColor(1);
   observed->SetLineWidth(3);
   observed->SetLineColor(kRed);
   observed->SetMarkerStyle(8);
   
   observed->Draw("c");
   
// Graph expected
  double xx[15] = {900, 875, 850, 825, 800, 775, 750, 725, 700, 675, 650, 635.89, 634.801, 635.552, 634.481};
  double yy[15] = {1680.2, 1681.16, 1681.55, 1680.92, 1681.26, 1692.84, 1703.84, 1714.99, 1737.29, 1772.61, 1820.22, 1850, 1900, 1950, 2000};
  TGraph* expected = new TGraph(15, xx, yy);
// end expected
   expected->SetName("Expected");
   expected->SetTitle("Expected");
   expected->SetFillColor(1);

   expected->SetLineColor(kBlue);
   expected->SetLineStyle(2);
   expected->SetLineWidth(3);
   expected->SetMarkerStyle(8);

   expected->Draw("c");
   
// Graph expectedP1
  double xx[15] = {900, 875, 850, 825, 800, 775, 750, 725, 700, 675, 650, 649.625, 646.651, 646.429, 644.398};
  double yy[15] = {1687.34, 1689.56, 1692.2, 1693.05, 1693.9, 1706.14, 1715.63, 1727.29, 1756.98, 1800.08, 1849.35, 1850, 1900, 1950, 2000};
  TGraph* exp1p = new TGraph(15, xx, yy);
// end expectedP1
   exp1p->SetName("Exp1p");
   exp1p->SetTitle("Exp1p");
   exp1p->SetFillColor(1);

   exp1p->SetLineColor(kAzure+5);
   exp1p->SetLineWidth(2);
   exp1p->SetMarkerStyle(8);
   
   
   //exp1p->Draw("c");
   
// Graph expectedM1
  double xx[17] = {900, 875, 850, 825, 800, 775, 750, 725, 700, 675, 650, 634.921, 621.339, 611.059, 610.172, 611.572, 605.83};
  double yy[17] = {1654.41, 1655.58, 1655.24, 1655.81, 1656.61, 1662.37, 1670.04, 1680.57, 1695.39, 1705.85, 1729.17, 1750, 1800, 1850, 1900, 1950, 2000};
  TGraph* exp1m = new TGraph(17, xx, yy);
// end expectedM1
   exp1m->SetName("Exp1m");
   exp1m->SetTitle("Exp1m");
   exp1m->SetFillColor(1);

   exp1m->SetLineColor(kAzure+5);
   exp1m->SetLineWidth(2);
   exp1m->SetMarkerStyle(8);
   
    exp1m->Draw("c");

// Graph expectedP2
  double xx[15] = {925, 900, 875, 850, 825, 800, 775, 750, 725, 700, 675, 662.343, 658.042, 654.609, 658.816};
  double yy[15] = {1702.6, 1697.76, 1692.98, 1698.01, 1705.68, 1720.34, 1722.9, 1716.43, 1753.27, 1774.34, 1822.03, 1850, 1900, 1950, 2000};
  TGraph* exp2p = new TGraph(15, xx, yy);
// end expectedP2
   exp2p->SetName("Exp2p");
   exp2p->SetTitle("Exp2p");
   exp2p->SetFillColor(1);

   exp2p->SetLineColor(kAzure+5);
   exp2p->SetLineWidth(2);
   exp2p->SetLineStyle(3);
   exp2p->SetMarkerStyle(8);

   
   //   exp2p->Draw("c");
   
// Graph expectedM2
  double xx[20] = {900, 875, 850, 825, 800, 775, 750, 725, 700, 675, 650, 625, 600, 590.931, 586.057, 576.603, 566.996, 567.581, 563.629, 559.288};
  double yy[20] = {1588.06, 1585.93, 1583.69, 1584.47, 1585.36, 1590.14, 1597.14, 1602.57, 1607.77, 1612.3, 1628.77, 1647, 1680.27, 1700, 1750, 1800, 1850, 1900, 1950, 2000};
  TGraph* exp2m = new TGraph(20, xx, yy);
// end expectedM2
   exp2m->SetName("Exp2m");
   exp2m->SetTitle("Exp2m");
   exp2m->SetFillColor(1);

   exp2m->SetLineColor(kAzure+5);
   exp2m->SetLineWidth(2);
   exp2m->SetLineStyle(3);
   exp2m->SetMarkerStyle(8);
   
      exp2m->Draw("c");

  TLegend* myleg = new TLegend(0.6,0.6,0.7,0.85,"95% C.L. CLs Limits","brNDC");;

 
  myleg->SetFillColor(0); 
  myleg->SetShadowColor(0);
  myleg->SetTextSize(0.035);
  myleg->SetBorderSize(0);

  myleg->AddEntry(observed,"NLO observed","l");
  myleg->AddEntry(expected,"NLO expected median","l");
  myleg->AddEntry(exp1p,"NLO expected +1#sigma","l");
  myleg->AddEntry(exp2p,"NLO expected +2#sigma","l");
//   myleg->AddEntry(exp1p,"NLO expected #pm1#sigma","l");
//   myleg->AddEntry(exp2p,"NLO expected #pm2#sigma","l");
  myleg->Draw();

  TLatex* lumilabel = new TLatex(675,2015,"#sqrt{s} = 7 TeV,   L_{int} = 2.1 fb^{-1}");
  lumilabel->SetTextSize(0.05);
  lumilabel->Draw("same");

  TLatex* cmslabel = new TLatex(505.,2015,"CMS Preliminary");
  cmslabel->SetTextSize(0.05);
  cmslabel->Draw("same");



   c->Modified();
   c->cd();
   c->SetSelected(c);
}
