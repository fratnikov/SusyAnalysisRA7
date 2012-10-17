#include <stdio.h>

#include "ra7StatConverter.C"

int main (int argc, char* argv[]) {
  cout << "main..." << endl;
  if (argc < 3) {
    cout << argv[0] << "<data_points> <maxSignal> [channels]" << endl;
    return 0;
  }
  ifstream datapoints (argv[1]);
  double maxSignal = atof (argv[2]);
  int maxChannels = 0;
  if (argc > 3) maxChannels = atoi (argv[3]);
  int m0, m12, tanb;
  while (datapoints) {
    datapoints >> m0 >> m12 >> tanb;
    if (!datapoints) break;
    cout << endl << argv[0] << " ===============  processing point : " << m0 << ':' << m12 
	 << " max/channels: " << maxSignal << '/' << maxChannels
	 << "  =================" << endl;



    string dataDir (".");
    
    cout << "runStatConverter..." << endl;
    string statFile = "";
    string cardFile = runStatConverter (dataDir, m0, m12, maxChannels);

    if (!cardFile.empty()) {
      cout << "combination cards file: " <<  cardFile << endl;
      
      char buffer[1024];
      sprintf (buffer, "ra7_%d_%d_combinedModel", m0, m12);
      string jobname (buffer);
      char iterations [1024];
      sprintf (iterations, "--scanRs 1 -vR '[%f,%f,x1.5]'", maxSignal/pow(1.5,8), maxSignal*1.1);
      //  const char iterations[] = "--scanRs 1 -vR '[0.64,1.6,x1.25]'";
      // const char iterations[] = "--scanRs 1 -vR '[0.8,1.3,x1.25]'";
      // const char iterations[] = "--scanRs 1 -vR '[0.3,3.4,x1.5]'";
      //      string iterations = m12 < 1000 ? 
      //        "--scanRs 1 -vR '[5,60,x1.5]'" : // sugra
      //        //  "--scanRs 1 -vR '[2,15,x1.25]'"; // coNLSP
      //             "--scanRs 1 -vR '[1,25,x1.5]'"; // coNLSP
      //     sprintf (buffer, "lands.exe -d %s -M Hybrid --freq  --nToysForCLsb 2500 --nToysForCLb 1500  %s -n %s", cardFile.c_str(), iterations.c_str(), jobname.c_str());
      
      sprintf (buffer, "lands.exe -d %s -M Hybrid --freq  --nToysForCLsb 3000 --nToysForCLb 3000  %s -n %s", cardFile.c_str(), iterations, jobname.c_str());
      string command(buffer);
      //      command += " -D asimov_b";
      cout << "Executing: " << command << endl;
      system (command.c_str());
      sprintf (buffer, "./%s_m2lnQ.root", jobname.c_str());
      statFile = string (buffer);
      sprintf (buffer, "extractLimitLands %s %d %d", statFile.c_str(), m0, m12);
      command = buffer;
      cout << "Executing: " << command << endl;
      system (command.c_str());
    }
    else {
      cout << "failed to produce card file for the model " << m0 << ':' << m12 << endl;
    }
    if (1) {
      cout << "clean up: " << cardFile << " " << statFile << "" << endl;
      if (!cardFile.empty()) remove (cardFile.c_str());
      if (!statFile.empty()) remove (statFile.c_str());
    }
    else {
      cout << "NOT clean up: " << cardFile << " " << statFile << "" << endl;
    }
  }
  
  return 0;
}
