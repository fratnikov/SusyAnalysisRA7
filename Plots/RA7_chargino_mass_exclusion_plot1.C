{
//=========Macro generated from canvas: c1/c1
//=========  (Thu Mar  3 14:17:04 2011) by ROOT version5.27/06a

#include "tdrstyle.C"
  setTDRStyle();
  tdrStyle->SetPadTopMargin(0.08);
  tdrStyle->SetPadBottomMargin(0.13);
  tdrStyle->SetPadLeftMargin(0.12);
  tdrStyle->SetPadRightMargin(0.05);

  bool preliminary = !getenv ("NOPRELIMINARY");

  gStyle->SetMarkerSize(0);

   TCanvas *c1 = new TCanvas("c1", "c1",14,48,1200,900);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   c1->Range(82.31192,-1.25,219.4712,11.25);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetTickx(1);
   c1->SetTicky(1);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TGraph *graph = new TGraph(28);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#0000ff");
   graph->SetLineColor(ci);
   graph->SetLineWidth(2);
   graph->SetPoint(0,95.12474,15.83157);
   graph->SetPoint(1,99.60311,13.31232);
   graph->SetPoint(2,104.0656,11.3888);
   graph->SetPoint(3,108.5132,9.428938);
   graph->SetPoint(4,112.9465,8.247871);
   graph->SetPoint(5,117.3664,7.052981);
   graph->SetPoint(6,121.7736,6.091388);
   graph->SetPoint(7,126.1687,5.389917);
   graph->SetPoint(8,130.5524,4.757724);
   graph->SetPoint(9,134.9251,4.229634);
   graph->SetPoint(10,139.2876,3.729035);
   graph->SetPoint(11,143.6402,3.270141);
   graph->SetPoint(12,147.9834,2.923493);
   graph->SetPoint(13,152.3177,2.602745);
   graph->SetPoint(14,156.6435,2.301191);
   graph->SetPoint(15,160.9612,2.003385);
   graph->SetPoint(16,165.2711,1.688923);
   graph->SetPoint(17,169.5736,1.453175);
   graph->SetPoint(18,173.8689,1.223525);
   graph->SetPoint(19,178.1573,1.005572);
   graph->SetPoint(20,182.4393,0.8269963);
   graph->SetPoint(21,186.715,0.6668764);
   graph->SetPoint(22,190.985,0.539482);
   graph->SetPoint(23,195.2496,0.4443761);
   graph->SetPoint(24,199.509,0.3673927);
   graph->SetPoint(25,203.7634,0.3100767);
   graph->SetPoint(26,208.0131,0.2607527);
   graph->SetPoint(27,208.0131,0.2607527);
   
   TH1F *Graph1 = new TH1F("Graph1","Graph",100,83.83591,219.3019);
   Graph1->SetMinimum(0);
   Graph1->SetMaximum(10);
   Graph1->SetDirectory(0);
   Graph1->SetStats(0);
   Graph1->GetXaxis()->SetTitle("Chargino Mass  (GeV/c^{2})  ");
   Graph1->GetXaxis()->SetRange(10,90);
   //   Graph1->GetXaxis()->CenterTitle(true);
   Graph1->GetYaxis()->SetTitle("#sigma #times BR( #geq3l)  (pb)  ");
   Graph1->GetYaxis()->SetTitleOffset (0.8);
   //   Graph1->GetYaxis()->CenterTitle(true);
   graph->SetHistogram(Graph1);
   
   graph->Draw("ac");
   
   graph = new TGraph(2);
   graph->SetName("Graph");
   graph->SetTitle("Graph");

   ci = TColor::GetColor("#00ff00");
   graph->SetFillColor(ci);
   graph->SetFillStyle(3004);

   ci = TColor::GetColor("#00ff00");
   graph->SetLineColor(ci);
   graph->SetLineWidth(3601);
   graph->SetPoint(0,114,0);
   graph->SetPoint(1,114,10);
   
   TH1F *Graph2 = new TH1F("Graph2","Graph",100,113.9,115.1);
   Graph2->SetMinimum(0);
   Graph2->SetMaximum(11);
   Graph2->SetDirectory(0);
   Graph2->SetStats(0);
   graph->SetHistogram(Graph2);
   
   graph->Draw("cp");
   
   graph = new TGraph(2);
   graph->SetName("Graph");
   graph->SetTitle("Graph");

   ci = TColor::GetColor("#00ff00");
   graph->SetFillColor(ci);
   graph->SetFillStyle(3004);

   ci = TColor::GetColor("#00ff00");
   graph->SetLineColor(ci);
   graph->SetLineWidth(3601);
   graph->SetPoint(0,114,0);
   graph->SetPoint(1,114,10);
   
   TH1F *Graph23 = new TH1F("Graph23","Graph",100,113.9,115.1);
   Graph23->SetMinimum(0);
   Graph23->SetMaximum(11);
   Graph23->SetDirectory(0);
   Graph23->SetStats(0);
   graph->SetHistogram(Graph23);
   
   graph->Draw("cp");
   
   graph = new TGraph(2);
   graph->SetName("Graph");
   graph->SetTitle("Graph");

   ci = TColor::GetColor("#00ffff");
   graph->SetFillColor(ci);
   graph->SetFillStyle(3004);

   ci = TColor::GetColor("#00ffff");
   graph->SetLineColor(ci);
   graph->SetLineWidth(5801);
   graph->SetPoint(0,154,0);
   graph->SetPoint(1,154,10);
   
   TH1F *Graph4 = new TH1F("Graph4","Graph",100,153.9,155.1);
   Graph4->SetMinimum(0);
   Graph4->SetMaximum(11);
   Graph4->SetDirectory(0);
   Graph4->SetStats(0);
   graph->SetHistogram(Graph4);
   
   graph->Draw("cp");
   
   graph = new TGraph(2);
   graph->SetName("Graph");
   graph->SetTitle("Graph");

   ci = TColor::GetColor("#00ffff");
   graph->SetFillColor(ci);
   graph->SetFillStyle(3004);

   ci = TColor::GetColor("#00ffff");
   graph->SetLineColor(ci);
   graph->SetLineWidth(5801);
   graph->SetPoint(0,154,0);
   graph->SetPoint(1,154,10);
   
   TH1F *Graph45 = new TH1F("Graph45","Graph",100,153.9,155.1);
   Graph45->SetMinimum(0);
   Graph45->SetMaximum(11);
   Graph45->SetDirectory(0);
   Graph45->SetStats(0);
   graph->SetHistogram(Graph45);
   
   graph->Draw("cp");
   
   graph = new TGraph(28);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);

   ci = TColor::GetColor("#0000ff");
   graph->SetLineColor(ci);
   graph->SetLineWidth(2);
   graph->SetPoint(0,95.12474,15.83157);
   graph->SetPoint(1,99.60311,13.31232);
   graph->SetPoint(2,104.0656,11.3888);
   graph->SetPoint(3,108.5132,9.428938);
   graph->SetPoint(4,112.9465,8.247871);
   graph->SetPoint(5,117.3664,7.052981);
   graph->SetPoint(6,121.7736,6.091388);
   graph->SetPoint(7,126.1687,5.389917);
   graph->SetPoint(8,130.5524,4.757724);
   graph->SetPoint(9,134.9251,4.229634);
   graph->SetPoint(10,139.2876,3.729035);
   graph->SetPoint(11,143.6402,3.270141);
   graph->SetPoint(12,147.9834,2.923493);
   graph->SetPoint(13,152.3177,2.602745);
   graph->SetPoint(14,156.6435,2.301191);
   graph->SetPoint(15,160.9612,2.003385);
   graph->SetPoint(16,165.2711,1.688923);
   graph->SetPoint(17,169.5736,1.453175);
   graph->SetPoint(18,173.8689,1.223525);
   graph->SetPoint(19,178.1573,1.005572);
   graph->SetPoint(20,182.4393,0.8269963);
   graph->SetPoint(21,186.715,0.6668764);
   graph->SetPoint(22,190.985,0.539482);
   graph->SetPoint(23,195.2496,0.4443761);
   graph->SetPoint(24,199.509,0.3673927);
   graph->SetPoint(25,203.7634,0.3100767);
   graph->SetPoint(26,208.0131,0.2607527);
   graph->SetPoint(27,208.0131,0.2607527);
   
   TH1F *Graph16 = new TH1F("Graph16","Graph",100,83.83591,219.3019);
   Graph16->SetMinimum(0);
   Graph16->SetMaximum(10);
   Graph16->SetDirectory(0);
   Graph16->SetStats(0);
   Graph16->GetXaxis()->SetTitle("Chargino Mass [GeV/c^{2}]");
   Graph16->GetXaxis()->SetRange(10,90);
   Graph16->GetXaxis()->CenterTitle(true);
   Graph16->GetYaxis()->SetTitle("#sigma x BR( #geq3l) [pb]");
   Graph16->GetYaxis()->CenterTitle(true);
   graph->SetHistogram(Graph16);
   
   graph->Draw("cp");
   
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(15);
   grae->SetName("Graph");
   grae->SetTitle("Graph");

   ci = TColor::GetColor("#00ff00");
   grae->SetFillColor(ci);
   grae->SetFillStyle(1000);
   grae->SetPoint(0,95.12474,3.064019);
   grae->SetPointError(0,0,0,1.225608,2.75394);
   grae->SetPoint(1,104.0656,1.844607);
   grae->SetPointError(1,0,0,0.7378427,1.657933);
   grae->SetPoint(2,112.9465,1.412085);
   grae->SetPointError(2,0,0,0.5648341,1.269182);
   grae->SetPoint(3,121.7736,1.219382);
   grae->SetPointError(3,0,0,0.4877529,1.095981);
   grae->SetPoint(4,130.5524,1.114774);
   grae->SetPointError(4,0,0,0.4459094,1.001958);
   grae->SetPoint(5,139.2876,1.092363);
   grae->SetPointError(5,0,0,0.436945,0.9818155);
   grae->SetPoint(6,147.9834,1.129776);
   grae->SetPointError(6,0,0,0.4519103,1.015442);
   grae->SetPoint(7,156.6435,1.196499);
   grae->SetPointError(7,0,0,0.4785996,1.075413);
   grae->SetPoint(8,165.2711,1.277565);
   grae->SetPointError(8,0,0,0.511026,1.148275);
   grae->SetPoint(9,173.8689,1.273931);
   grae->SetPointError(9,0,0,0.5095723,1.145009);
   grae->SetPoint(10,182.4393,1.260052);
   grae->SetPointError(10,0,0,0.504021,1.132535);
   grae->SetPoint(11,190.985,1.236146);
   grae->SetPointError(11,0,0,0.4944582,1.111048);
   grae->SetPoint(12,199.509,1.209801);
   grae->SetPointError(12,0,0,0.4839204,1.087369);
   grae->SetPoint(13,208.0131,1.153397);
   grae->SetPointError(13,0,0,0.4613587,1.036673);
   grae->SetPoint(14,208.0131,1.153397);
   grae->SetPointError(14,0,0,0.4613587,1.036673);
   
   TH1F *Graph1 = new TH1F("Graph1","Graph",100,83.83591,219.3019);
   Graph1->SetMinimum(0.1391633);
   Graph1->SetMaximum(6.334214);
   Graph1->SetDirectory(0);
   Graph1->SetStats(0);
   grae->SetHistogram(Graph1);
   
   grae->Draw("cp4");
   
   grae = new TGraphAsymmErrors(15);
   grae->SetName("Graph");
   grae->SetTitle("Graph");

   ci = TColor::GetColor("#ffff00");
   grae->SetFillColor(ci);
   grae->SetFillStyle(1000);
   grae->SetPoint(0,95.12474,3.064019);
   grae->SetPointError(0,0,0,0.6924683,1.37697);
   grae->SetPoint(1,104.0656,1.844607);
   grae->SetPointError(1,0,0,0.4168811,0.8289663);
   grae->SetPoint(2,112.9465,1.412085);
   grae->SetPointError(2,0,0,0.3191313,0.6345911);
   grae->SetPoint(3,121.7736,1.219382);
   grae->SetPointError(3,0,0,0.2755804,0.5479904);
   grae->SetPoint(4,130.5524,1.114774);
   grae->SetPointError(4,0,0,0.2519388,0.5009792);
   grae->SetPoint(5,139.2876,1.092363);
   grae->SetPointError(5,0,0,0.2468739,0.4909077);
   grae->SetPoint(6,147.9834,1.129776);
   grae->SetPointError(6,0,0,0.2553293,0.5077212);
   grae->SetPoint(7,156.6435,1.196499);
   grae->SetPointError(7,0,0,0.2704088,0.5377067);
   grae->SetPoint(8,165.2711,1.277565);
   grae->SetPointError(8,0,0,0.2887297,0.5741377);
   grae->SetPoint(9,173.8689,1.273931);
   grae->SetPointError(9,0,0,0.2879084,0.5725045);
   grae->SetPoint(10,182.4393,1.260052);
   grae->SetPointError(10,0,0,0.2847719,0.5662676);
   grae->SetPoint(11,190.985,1.236146);
   grae->SetPointError(11,0,0,0.2793689,0.5555238);
   grae->SetPoint(12,199.509,1.209801);
   grae->SetPointError(12,0,0,0.273415,0.5436846);
   grae->SetPoint(13,208.0131,1.153397);
   grae->SetPointError(13,0,0,0.2606676,0.5183365);
   grae->SetPoint(14,208.0131,1.153397);
   grae->SetPointError(14,0,0,0.2606676,0.5183365);
   
   TH1F *Graph2 = new TH1F("Graph2","Graph",100,83.83591,219.3019);
   Graph2->SetMinimum(0.4859385);
   Graph2->SetMaximum(4.800539);
   Graph2->SetDirectory(0);
   Graph2->SetStats(0);
   grae->SetHistogram(Graph2);
   
   grae->Draw("cp4");
   
   graph = new TGraph(28);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);

   ci = TColor::GetColor("#0000ff");
   graph->SetLineColor(ci);
   graph->SetLineWidth(2);
   graph->SetPoint(0,95.12474,15.83157);
   graph->SetPoint(1,99.60311,13.31232);
   graph->SetPoint(2,104.0656,11.3888);
   graph->SetPoint(3,108.5132,9.428938);
   graph->SetPoint(4,112.9465,8.247871);
   graph->SetPoint(5,117.3664,7.052981);
   graph->SetPoint(6,121.7736,6.091388);
   graph->SetPoint(7,126.1687,5.389917);
   graph->SetPoint(8,130.5524,4.757724);
   graph->SetPoint(9,134.9251,4.229634);
   graph->SetPoint(10,139.2876,3.729035);
   graph->SetPoint(11,143.6402,3.270141);
   graph->SetPoint(12,147.9834,2.923493);
   graph->SetPoint(13,152.3177,2.602745);
   graph->SetPoint(14,156.6435,2.301191);
   graph->SetPoint(15,160.9612,2.003385);
   graph->SetPoint(16,165.2711,1.688923);
   graph->SetPoint(17,169.5736,1.453175);
   graph->SetPoint(18,173.8689,1.223525);
   graph->SetPoint(19,178.1573,1.005572);
   graph->SetPoint(20,182.4393,0.8269963);
   graph->SetPoint(21,186.715,0.6668764);
   graph->SetPoint(22,190.985,0.539482);
   graph->SetPoint(23,195.2496,0.4443761);
   graph->SetPoint(24,199.509,0.3673927);
   graph->SetPoint(25,203.7634,0.3100767);
   graph->SetPoint(26,208.0131,0.2607527);
   graph->SetPoint(27,208.0131,0.2607527);
   
   TH1F *Graph167 = new TH1F("Graph167","Graph",100,83.83591,219.3019);
   Graph167->SetMinimum(0);
   Graph167->SetMaximum(10);
   Graph167->SetDirectory(0);
   Graph167->SetStats(0);
   Graph167->GetXaxis()->SetTitle("Chargino Mass (GeV/c^{2})");
   Graph167->GetXaxis()->SetRange(10,90);
   Graph167->GetXaxis()->CenterTitle(true);
   Graph167->GetYaxis()->SetTitle("#sigma x BR( #geq3l) (pb)");
   Graph167->GetYaxis()->CenterTitle(true);
   graph->SetHistogram(Graph167);
   
   graph->Draw("cp");
   
   graph = new TGraph(15);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   graph->SetLineWidth(5);
   graph->SetPoint(0,95.12474,4.596029);
   graph->SetPoint(1,104.0656,2.76691);
   graph->SetPoint(2,112.9465,2.118128);
   graph->SetPoint(3,121.7736,1.829074);
   graph->SetPoint(4,130.5524,1.67216);
   graph->SetPoint(5,139.2876,1.638544);
   graph->SetPoint(6,147.9834,1.694664);
   graph->SetPoint(7,156.6435,1.794748);
   graph->SetPoint(8,165.2711,1.916347);
   graph->SetPoint(9,173.8689,1.910896);
   graph->SetPoint(10,182.4393,1.890079);
   graph->SetPoint(11,190.985,1.854218);
   graph->SetPoint(12,199.509,1.814702);
   graph->SetPoint(13,208.0131,1.730095);
   graph->SetPoint(14,208.0131,1.730095);
   
   TH1F *Graph8 = new TH1F("Graph8","Graph",100,83.83591,219.3019);
   Graph8->SetMinimum(1.342795);
   Graph8->SetMaximum(4.891777);
   Graph8->SetDirectory(0);
   Graph8->SetStats(0);
   graph->SetHistogram(Graph8);
   
   graph->Draw("cp");
   
   graph = new TGraph(15);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   graph->SetLineStyle(2);
   graph->SetLineWidth(3);
   graph->SetPoint(0,95.12474,3.064019);
   graph->SetPoint(1,104.0656,1.844607);
   graph->SetPoint(2,112.9465,1.412085);
   graph->SetPoint(3,121.7736,1.219382);
   graph->SetPoint(4,130.5524,1.114774);
   graph->SetPoint(5,139.2876,1.092363);
   graph->SetPoint(6,147.9834,1.129776);
   graph->SetPoint(7,156.6435,1.196499);
   graph->SetPoint(8,165.2711,1.277565);
   graph->SetPoint(9,173.8689,1.273931);
   graph->SetPoint(10,182.4393,1.260052);
   graph->SetPoint(11,190.985,1.236146);
   graph->SetPoint(12,199.509,1.209801);
   graph->SetPoint(13,208.0131,1.153397);
   graph->SetPoint(14,208.0131,1.153397);
   
   TH1F *Graph9 = new TH1F("Graph9","Graph",100,83.83591,219.3019);
   Graph9->SetMinimum(0.8951969);
   Graph9->SetMaximum(3.261185);
   Graph9->SetDirectory(0);
   Graph9->SetStats(0);
   graph->SetHistogram(Graph9);
   
   graph->Draw("cp");
   
   TLegend *leg = new TLegend(0.57,0.40,0.9,0.65,"95% C.L. Limits:","brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(42);
   leg->SetTextSize(0.04);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);

   TH1F* hdummy1 = new TH1F("hdummy","hdummy",1,0,1);

   TH1F* hdummy2 = new TH1F(*hdummy1);
   hdummy2->SetLineColor(1);
   hdummy2->SetLineStyle(1);
   hdummy2->SetLineWidth(5);
   hdummy2->SetFillColor(0);
   leg->AddEntry(hdummy2,"CMS observed", "l");

   TH1F* hdummy3 = new TH1F(*hdummy1);
   hdummy3->SetLineColor(1);
   hdummy3->SetLineStyle(2);
   hdummy3->SetLineWidth(3);
   hdummy3->SetFillColor(5);
   leg->AddEntry(hdummy3,"CMS expected #pm 1#sigma","fl");

   TH1F* hdummy4 = new TH1F(*hdummy1);
   hdummy4->SetLineColor(1);
   hdummy4->SetLineStyle(2);
   hdummy4->SetLineWidth(3);
   hdummy4->SetFillColor(3);
   leg->AddEntry(hdummy4,"CMS expected #pm 2#sigma","fl");

   TH1F* hdummy6 = new TH1F(*hdummy1);
   hdummy6->SetLineColor(0);
   hdummy6->SetLineStyle(0);
   hdummy6->SetLineWidth(0);
   hdummy6->SetFillColor(0);
   hdummy6->SetTitle("");
   leg->AddEntry(hdummy6,"","l");

   TH1F* hdummy5 = new TH1F(*hdummy1);
   hdummy5->SetLineColor(4);
   hdummy5->SetLineStyle(1);
   hdummy5->SetLineWidth(2);
   hdummy5->SetFillColor(0);
   leg->AddEntry(hdummy5,"Theory #sigma_{NLO} #times BR(#geq3l)","l");

   leg->Draw();

   TLatex *   tex = new TLatex(105,10,preliminary ? "CMS preliminary" : "CMS");
   tex->SetTextColor(1);
   tex->SetTextAlign(10);
   tex->SetTextSize(0.05);
   tex->SetTextFont(42);
   tex->Draw();
   
   tex = new TLatex(150,10,"L_{int} = 35 pb^{-1}, #sqrt{s} = 7 TeV");
   tex->SetTextColor(1);
   tex->SetTextAlign(10);
   tex->SetTextSize(0.05);
   tex->SetTextFont(42);
   tex->Draw();

      tex = new TLatex(100,8.5,"LEP");
   tex->SetTextAlign(10);
   tex->SetTextSize(0.04);
   tex->SetLineWidth(2);
   tex->SetTextFont(42);
   tex->Draw();
      tex = new TLatex(100,8,"direct");
   tex->SetTextAlign(10);
   tex->SetTextSize(0.04);
   tex->SetLineWidth(2);
   tex->SetTextFont(42);
   tex->Draw();
      tex = new TLatex(100,7.5,"Limit");
   tex->SetTextAlign(10);
   tex->SetTextSize(0.04);
   tex->SetLineWidth(2);
   tex->SetTextFont(42);
   tex->Draw();
      tex = new TLatex(126,8.5,"D0 Limit");
   tex->SetTextAlign(10);
   tex->SetTextSize(0.04);
   tex->SetLineWidth(2);
   tex->SetTextFont(42);
   tex->Draw();
      tex = new TLatex(126,8,"L=2.3fb^{-1}");
   tex->SetTextAlign(10);
   tex->SetTextSize(0.04);
   tex->SetLineWidth(2);
   tex->SetTextFont(42);
   tex->Draw();
   tex = new TLatex(160,8,"tan#beta=3, A_{0}=0, #mu>0,");
   tex->SetTextAlign(10);
   tex->SetTextSize(0.04);
   tex->SetLineWidth(2);
   tex->SetTextFont(42);
   tex->Draw();
      tex = new TLatex(160,7.3,"m_{0}=60 GeV/c^{2}");
   tex->SetTextAlign(10);
   tex->SetTextSize(0.04);
   tex->SetLineWidth(2);
   tex->SetTextFont(42);
   tex->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
   c1->SaveAs("RA7_chargino_mass_exclusion_plot1.pdf");
   if (preliminary) {
     c1->SaveAs("RA7_chargino_mass_exclusion_plot1.png");
     c1->SaveAs("RA7_chargino_mass_exclusion_plot1.eps");
   }
}
