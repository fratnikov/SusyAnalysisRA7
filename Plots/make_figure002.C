{
#include "tdrstyle.C"
  setTDRStyle();
tdrStyle->SetPadBottomMargin(0.15);

  //   TCanvas *c1 = new TCanvas("c1", "c1",14,48,1200,900);
   TCanvas *c1 = new TCanvas("c1", "c1",0,0,1200,900);


  TH2D *h_hold=new TH2D("h_hold","; m_{#tilde{q}} - m_{#tilde{#chi^{0}_{1}}}  [GeV/c^{2}]  ; #sigma #times Br #times #varepsilon  [pb]  ",310,0.0,310,250,0.0,0.250);

  h_hold->GetYaxis()->SetTitleOffset(1.0);
  h_hold->GetXaxis()->SetTitleOffset(1.0);
  h_hold->GetYaxis()->SetTitleFont(42);
  h_hold->GetXaxis()->SetTitleFont(42);
  h_hold->GetYaxis()->SetLabelFont(42);
  h_hold->GetXaxis()->SetLabelFont(42);
  h_hold->Draw();

  double dmass [] = {5, 35, 65, 95, 125, 155, 185, 215, 245, 275};
  const int nPoints = sizeof (dmass)/sizeof(double);
  double dDmass [nPoints] = {0,0,0,0,0,0,0,0,0,0};
  
  double effJt [nPoints] = {0.0683, 0.0749,0.1026,0.1366,0.1643,0.1843,0.1865,0.192619,0.1747,0.147};
  double dEffJt [nPoints] = {0.00261343, 0.00273679, 0.00320312, 0.00369594, 0.00405339, 0.00429302, 0.00431856, 0.00438906, 0.00417971, 0.00383406};
  
  double effMet [nPoints] = {0.2225,0.2233,0.2121,0.2046,0.1996,0.2031,0.1897,0.188319,0.1695,0.1431};
  double dEffMet [nPoints] = {0.00471699, 0.00472546, 0.00460543, 0.00452327, 0.00446766, 0.00450666, 0.00435546, 0.00433979, 0.00411704, 0.00378286};

  TGraphErrors* gr_jt = new TGraphErrors (nPoints, dmass, effJt, dDmass, dEffJt);
  gr_jt->SetMarkerColor (4);
  gr_jt->SetMarkerStyle (20);
  gr_jt->SetMarkerSize (1.5);
  gr_jt->SetLineWidth (2);
  gr_jt->Draw ("psame");
  TGraphErrors* gr_met = new TGraphErrors (nPoints, dmass, effMet, dDmass, dEffMet);
  gr_met->SetMarkerColor (2);
  gr_met->SetMarkerStyle (21);
  gr_met->SetMarkerSize (1.5);
  gr_met->SetLineWidth (2);
  gr_met->Draw ("psame");

   TLegend *leg = new TLegend(0.55,0.25,0.95,0.45,"","brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(42);
   leg->SetTextSize(0.04);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);

   leg->AddEntry(gr_met,"MET>50 GeV","p"); 
   leg->AddEntry(gr_jt,"H_{T}>200 GeV","p"); 
   leg->Draw();

   TLatex *   tex = new TLatex(20,0.2505,"CMS simulation");
   tex->SetTextColor(1);
   tex->SetTextAlign(10);
   tex->SetTextSize(0.04);
   tex->SetTextFont(42);
   tex->Draw();
   
   tex = new TLatex(200,0.2505,"#sqrt{s}=7 TeV");
   tex->SetTextColor(1);
   tex->SetTextAlign(10);
   tex->SetTextSize(0.04);
   tex->SetTextFont(42);
   tex->Draw();
  
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
  

  c1->SaveAs("Figure_002.pdf");
  c1->SaveAs("Figure_002.eps");
  c1->SaveAs("Figure_002.png");
  



}
