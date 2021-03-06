

TGraph* observed3lg( ){
// Graph observed
//   double xx[18] = {380, 360, 340, 320, 300, 280, 260, 240, 220, 200, 180, 160, 140, 120, 100, 80, 60, 40};
//   double yy[18] = {258.98, 257.112, 261.187, 274.206, 218.373, 196.141, 181.905, 216.591, 206.656, 201.831, 214.94, 251.545, 318.174, 316.022, 306.358, 290.668, 278.415, nan};
  double xx[18] = {380, 360, 340, 320, 300, 280, 260, 240, 220, 200, 180, 160, 140, 120, 100, 80, 60, 30};
  double yy[18] = {258.98, 257.112, 261.187, 232.585, 218.373, 196.141, 181.905, 216.591, 206.656, 201.831, 214.94, 251.545, 318.174, 316.022, 306.358, 290.668, 278.415, 275};
  TGraph* graph = new TGraph(18, xx, yy);
// end observed

// Graph observed2
//  double xx[17] = {380, 360, 340, 320, 300, 280, 260, 240, 220, 200, 180, 160, 140, 120, 100, 80, 60};
//  double yy[17] = {194.566, 257.112, 261.187, 232.585, 218.373, 168.419, 181.905, 216.591, 206.656, 177.944, 214.94, 251.545, 318.174, 316.022, 306.358, 290.668, 278.415};
// end observed2
   graph->SetLineWidth(3);
   graph->SetMarkerStyle(8);
   return graph;
}

TGraph* expected3lg () {
// Graph expected
//  double xx[18] = {380, 360, 340, 320, 300, 280, 260, 240, 220, 200, 180, 160, 140, 120, 100, 80, 60, 40};
//  double yy[18] = {285.634, 282.091, 276.56, 281.139, 283.444, 249.783, 228.243, 281.157, 254.447, 251.344, 259.875, 329.314, 340.648, 330.304, 325.311, 314.915, nan, nan};
  double xx[18] = {380, 360, 340, 320, 300, 280, 260, 240, 220, 200, 180, 160, 140, 120, 100, 80, 60, 30};
  double yy[18] = {285.634, 282.091, 276.56, 281.139, 267, 249.783, 244, 252, 254.447, 251.344, 259.875, 329.314, 340.648, 330.304, 325.311, 314.915, 307, 300};
  TGraph* graph = new TGraph(18, xx, yy);
// end expected

// Graph expected2
//  double xx[16] = {380, 360, 340, 320, 300, 280, 260, 240, 220, 200, 180, 160, 140, 120, 100, 80};
//  double yy[16] = {285.634, 282.091, 276.56, 281.139, 259.838, 249.783, 228.243, 237.466, 254.447, 251.344, 259.875, 329.314, 340.648, 330.304, 325.311, 314.915};
// end expected2
   graph->SetLineWidth(3);
   graph->SetMarkerStyle(8);
  return graph;
}

TGraph* expectedP13lg () {
// Graph expectedP1
//  double xx[18] = {380, 360, 340, 320, 300, 280, 260, 240, 220, 200, 180, 160, 140, 120, 100, 80, 60, 40};
//  double yy[18] = {294.871, 295.868, 299.638, 291.802, 294.156, 292.892, 302.725, 287.575, 285.741, 283.964, 325.084, 340.949, 348.302, 337.863, 334.487, 330.856, nan, nan};
  double xx[18] = {380, 360, 340, 320, 300, 280, 260, 240, 220, 200, 180, 160, 140, 120, 100, 80, 60, 30};
  double yy[18] = {294.871, 295.868, 299.638, 291.802, 294.156, 292.892, 292, 287.575, 285.741, 283.964, 325.084, 340.949, 348.302, 337.863, 334.487, 330.856, 327, 320};
  TGraph* graph = new TGraph(18, xx, yy);
// end expectedP1

// Graph expectedP12
//  double xx[16] = {380, 360, 340, 320, 300, 280, 260, 240, 220, 200, 180, 160, 140, 120, 100, 80};
//  double yy[16] = {294.871, 295.868, 299.638, 291.802, 294.156, 292.892, 236.291, 287.575, 285.741, 283.964, 273.033, 340.949, 348.302, 337.863, 334.487, 330.856};
// end expectedP12
   graph->SetLineWidth(3);
   graph->SetMarkerStyle(8);
  return graph;
}

TGraph* expectedM13lg () {
// Graph expectedM1
//  double xx[18] = {380, 360, 340, 320, 300, 280, 260, 240, 220, 200, 180, 160, 140, 120, 100, 80, 60, 40};
//  double yy[18] = {250.49, 246.889, 238.724, 264.169, 226.952, 201.25, 187.117, 213.846, 207.3, 201.964, 240.428, 255.716, 319.013, 314.37, 302.86, 291.295, 289.755, nan};
  double xx[18] = {380, 360, 340, 320, 300, 280, 260, 240, 220, 200, 180, 160, 140, 120, 100, 80, 60, 30};
  double yy[18] = {250.49, 246.889, 238.724, 236.335, 226.952, 201.25, 187.117, 213.846, 207.3, 201.964, 216.76, 255.716, 319.013, 314.37, 302.86, 291.295, 289.755, 283};
  TGraph* graph = new TGraph(18, xx, yy);
// end expectedM1

// Graph expectedM12
//  double xx[17] = {380, 360, 340, 320, 300, 280, 260, 240, 220, 200, 180, 160, 140, 120, 100, 80, 60};
//  double yy[17] = {197.241, 246.889, 238.724, 236.335, 226.952, 169.133, 187.117, 213.846, 207.3, 177.607, 216.76, 255.716, 319.013, 314.37, 302.86, 291.295, 289.755};
// end expectedM12
   graph->SetLineWidth(3);
   graph->SetMarkerStyle(8);
  return graph;
}



