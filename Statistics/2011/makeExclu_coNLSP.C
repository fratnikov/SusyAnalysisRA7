void swap (double& x, double& y) {
  double buf = x;
  x = y;
  y = buf;
}

void orderInY (vector<double>& xx, vector<double>& yy) {
  while (1) {
    unsigned i = 0;
    for (; i < yy.size(); ++i) {
      if ((i > 0) && (yy[i] < yy[i-1])) {
	swap (yy[i], yy[i-1]);
	swap (xx[i], xx[i-1]);
	break;
      }
    }
    if (i == yy.size()) return;
  }
}

void orderInX (vector<double>& xx, vector<double>& yy) {
  while (1) {
    unsigned i = 0;
    for (; i < yy.size(); ++i) {
      if ((i > 0) && (xx[i] < xx[i-1])) {
	swap (yy[i], yy[i-1]);
	swap (xx[i], xx[i-1]);
	break;
      }
    }
    if (i == yy.size()) return;
  }
}

void orderInDir (vector<double>& xx, vector<double>& yy) {
  while (1) {
    unsigned i = 1;
    for (; i < yy.size(); ++i) {
      if (fabs(xx[i] - xx[i-1]) < fabs(yy[i] - yy[i-1])) { // order in y
	if (yy[i] > yy[i-1]) {
	  swap (yy[i], yy[i-1]);
	  swap (xx[i], xx[i-1]);
	  break;
	}
      }
      else if (fabs(xx[i] - xx[i-1]) >= fabs(yy[i] - yy[i-1])) { // order in x
	if (xx[i] < xx[i-1]) {
	  swap (yy[i], yy[i-1]);
	  swap (xx[i], xx[i-1]);
	  break;
	}
      }
    }
    if (i == yy.size()) return;
  }
}

void dumpGraph (const TGraph* graph, const string& title) {
  cout << "// Graph " << title << endl;
  int nPoints = graph->GetN();
  cout << "  double xx[] = {";
  for (int i = 0; i < nPoints; ++i) {
    if (i != 0) cout << ", ";
    cout << graph->GetX()[i];
  }
  cout << "};" << endl;

  cout << "  double yy[] = {";
  for (int i = 0; i < nPoints; ++i) {
    if (i != 0) cout << ", ";
    cout << graph->GetY()[i];
  }
  cout << "};" << endl;

  cout << "  TGraph* " << title << " = new TGraph(" << nPoints << ", xx, yy);" << endl;

  cout << "// end " << title << endl << endl;
}

TGraph* makeCurve (TH2D* hist, double scale = 1., double minX = 0., double minY = 0.) {
//   TH2D* hist = new TH2D (*hist0);
//   hist->Scale(scale);
  int nBinsX = hist->GetNbinsX();
  int nBinsY = hist->GetNbinsY();
  vector<double> xx;
  vector<double> yy;
  int minIx = 1;
  if (minX > 0) minIx = hist->GetXaxis()->FindBin (minX);
  int minIy = 1;
  if (minY > 0) minIy = hist->GetYaxis()->FindBin (minY);

  cout << "Minimal bins to be used: " << minX << ':' << minY << " -> " << minIx << ':' << minIy << endl;

  for (int ix = nBinsX; ix >= minIx; --ix) {
    double x = hist->GetXaxis()->GetBinCenter (ix);
    //    cout << "x bin: " << ix << ' ' << x << endl;
    double logyprev = 2*log (hist->GetBinContent(ix,nBinsY)) - log(hist->GetBinContent(ix,nBinsY-1));
    int iy = nBinsY;
    for (; iy > 0; --iy) {
      if (hist->GetBinContent(ix,iy) <= 0) continue;
      double logy = log (hist->GetBinContent(ix,iy));
      // cout << ix << ':'<<iy<<"  "<<hist->GetBinContent(ix,iy)<<'/'<<logy<<endl;
      if (logy < 0) {
	if (iy < nBinsY) {
	  //cout << "y bin: " << iy << ' ' << hist->GetYaxis()->GetBinCenter (iy) << endl;
	  double y = hist->GetYaxis()->GetBinCenter (iy) - 
	    (hist->GetYaxis()->GetBinCenter (iy+1)-hist->GetYaxis()->GetBinCenter (iy))*
	    logy/(logyprev-logy);
	  xx.push_back(x);
	  yy.push_back(y);
//  	  cout << "new point 1 " << x << ':' << y 
//  	       << " (" << hist->GetYaxis()->GetBinCenter (iy) << ':' << logy << ","
//  	       << hist->GetYaxis()->GetBinCenter (iy+1) << ':' << logyprev << ")"
//  	       << endl;
	}
	break;
      }
      logyprev = logy;
    }
  }

  for (int iy = nBinsY; iy >= minIy; --iy) {
    double y = hist->GetYaxis()->GetBinCenter (iy);
    // cout << "y bin: " << iy << ' ' << y << endl;
    double logyprev = 2*log (hist->GetBinContent(nBinsX, iy)) - log(hist->GetBinContent(nBinsX-1,iy));
    int ix = nBinsX;
    for (; ix > 0; --ix) {
      if (hist->GetBinContent(ix,iy) <= 0) continue;
      double logy = log (hist->GetBinContent(ix,iy));
      // cout << ix << ':'<<iy<<"  "<<hist->GetBinContent(ix,iy)<<'/'<<logy<<endl;
      if (logy < 0) {
	if (ix < nBinsX) {
	  // cout << "x bin: " << ix << ' ' << hist->GetXaxis()->GetBinCenter (ix) << endl;
	  double x = hist->GetXaxis()->GetBinCenter (ix) - 
	    (hist->GetXaxis()->GetBinCenter (ix+1)-hist->GetXaxis()->GetBinCenter (ix))*
	    logy/(logyprev-logy);
	  xx.push_back(x);
	  yy.push_back(y);
//   	  cout << "new point 2 " << x << ':' << y 
//   	       << " (" << hist->GetXaxis()->GetBinCenter (ix) << ':' << logy << ","
//   	       << hist->GetXaxis()->GetBinCenter (ix+1) << ':' << logyprev << ")"
//   	       << endl;
	}
	break;
      }
      logyprev = logy;
    }
  }

  orderInDir (xx, yy);

  TGraph* result = new TGraph (xx.size(), &(xx[0]), &(yy[0]));
  result->SetLineWidth(3);
  result->SetMarkerStyle(8);
  result->SetMarkerSize (1.0);
  return result;
}

void drawAll() {
  TCanvas* c = new TCanvas("c", "interpret", 0, 0, 800, 600);
  //TH2D* frame = new TH2D ("frame", "frame", 1, 0, 400, 1, 100, 400);
  TH2D* frame = new TH2D ("LRPV", "LRPV", 1, 500, 900, 1, 1500, 2000);
  frame->GetXaxis()->SetTitle ("m_1");
  frame->GetYaxis()->SetTitle ("m_2");
  frame->Draw();
  TGraph* observed = makeCurve (hObsLimitSmooth, 1., 675, 1800);
  observed->SetLineColor(kBlack);
  TGraph* expected = makeCurve (hExpLimitSmooth, 1., 750, 1900);
  expected->SetLineColor(kBlue);
  TGraph* expectedP1 = makeCurve (hExpP1LimitSmooth, 1., 775, 1900);
  expectedP1->SetLineColor(kMagenta);
  TGraph* expectedM1 = makeCurve (hExpM1LimitSmooth, 1., 700, 1900);
  expectedM1->SetLineColor(kMagenta);
  
  TGraph* expectedP2 = makeCurve (hExpP2LimitSmooth, 1., 800, 1900);
  expectedP2->SetLineColor(kGreen);
  TGraph* expectedM2 = makeCurve (hExpM2LimitSmooth, 1., 700, 1750);
  expectedM2->SetLineColor(kGreen);
  
  observed->Draw ("LP");
  expected->Draw ("LP");
    expectedP1->Draw ("LP");
  expectedM1->Draw ("LP");
    expectedP2->Draw ("LP");
  expectedM2->Draw ("LP");
  
  dumpGraph (observed, "observed");
  dumpGraph (expected, "expected");
  dumpGraph (expectedP1, "exp1p");
  dumpGraph (expectedM1, "exp1m");
  dumpGraph (expectedP2, "exp2p");
  dumpGraph (expectedM2, "exp2m");
  
  
  TLegend* myleg = new TLegend(0.2,0.2,0.4,0.4,"95% C.L. CLs Limits","brNDC");
  myleg->AddEntry(observed,"NLO observed","l");
  myleg->AddEntry(expected,"NLO expected median","l");
  myleg->AddEntry(expectedP1,"NLO expected #pm1#sigma","l");
  myleg->AddEntry(expectedP2,"NLO expected #pm2#sigma","l");
  myleg->Draw();
}
void drawExclu() {
  TCanvas* c = new TCanvas("c", "interpret", 0, 0, 800, 600);
  c->SetLogz();

  TGraph* observed = makeCurve (hObsLimitSmooth);
  observed->SetLineColor(kBlack);
  TGraph* expected = makeCurve (hExpLimitSmooth);
  expected->SetLineColor(kBlack);
  expected->SetLineStyle (2);

  xSecObserved->Draw("colz");
  observed->Draw ("L");
  expected->Draw ("L");
  
  
  TLegend* myleg = new TLegend(0.2,0.7,0.4,0.9,"95% C.L. CLs Limits","brNDC");
  myleg->SetFillColor(0); 
  myleg->SetShadowColor(0);
  myleg->SetTextSize(0.035);
  myleg->SetBorderSize(0);
  myleg->AddEntry(observed,"NLO observed","l");
  myleg->AddEntry(expected,"NLO expected median","l");
  myleg->Draw();
}
