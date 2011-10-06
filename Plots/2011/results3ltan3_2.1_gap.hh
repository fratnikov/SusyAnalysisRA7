

TGraph* observed3lg( ){
// Graph observed
  double xx[19] = {300,     275,     250,     225,     200,     175,    165, 150, 101, 100, 99, 100, 147, 150, 140, 125,     100,     75,      50};
  double yy[19] = {185.882, 215.039, 210.842, 232.092, 243.312, 247.23, 250, 260, 207, 206, 207,208, 267, 280, 295, 303.407, 312.182, 297.408, 265};
  TGraph* graph = new TGraph(19, xx, yy);
// end observed
  graph->SetFillColor(1);
  graph->SetLineWidth(3);
  graph->SetMarkerStyle(8);
  return graph;
}

TGraph* expected3lg () {
// Graph expected
  double xx[11] = {300, 275, 250, 225, 200, 175, 150, 125, 100, 75, 50};
  //  double yy[11] = {278.321, 267.33, 260.329, 251.985, 267.298, 270.7, 306.279, 316.554, 324.245, 322.988, 320.111};
  double yy[11] = {260, 267.33, 260.329, 251.985, 267.298, 270.7, 306.279, 316.554, 324.245, 322.988, 310};
  TGraph* graph = new TGraph(11, xx, yy);
// end expected
   graph->SetLineWidth(3);
   graph->SetMarkerStyle(8);
  return graph;
}

TGraph* expectedP13lg () {
// Graph expectedP1
  double xx[11] = {300, 275, 250, 225, 200, 175, 150, 125, 100, 75, 50};
  double yy[11] = {282.992, 278.115, 272.148, 264.918, 275.072, 279.622, 312.986, 324.012, 333.882, 346.334, 329.948};
  TGraph* graph = new TGraph(11, xx, yy);
// end expectedP1
   graph->SetLineWidth(3);
   graph->SetMarkerStyle(8);
  return graph;
}

TGraph* expectedM13lg () {
// Graph expectedM1
  double xx[11] = {300, 275, 250, 225, 200, 175, 150, 125, 100, 75, 50};
  double yy[11] = {182.438, 213.787, 214.181, 238.284, 253.815, 258.243, 296.778, 304.56, 313.075, 302.003, 270};
  TGraph* graph = new TGraph(11, xx, yy);
// end expectedM1
   graph->SetLineWidth(3);
   graph->SetMarkerStyle(8);
  return graph;
}



