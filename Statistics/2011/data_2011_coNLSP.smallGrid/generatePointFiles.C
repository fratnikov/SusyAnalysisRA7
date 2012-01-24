#include <string>
#include <iostream>
#include <fstream>
using namespace std;

int main ()
{
  const char* baseName = "SUSY_scan_coNLSP";
  int pointsPerFile = 20;
  int fileCounter = 1;
  int pointsCounter = 0;
  int tanb = 3;
  ofstream* outFile = 0;
  for (int mc = 300; mc <= 900; mc += 50) {
    for (int mg = 1100; mg <= 1500; mg += 50) {
      if (!pointsCounter) {
	char fileName [1024];
	sprintf (fileName, "%s_%d.txt", baseName, fileCounter);
	outFile = new ofstream (fileName);
      }
      cout << mc<<':'<<mg<<" -> " << fileCounter << endl;
      *outFile << mc << ' ' << mg << ' ' << tanb << endl;
      ++pointsCounter;
      if (pointsCounter >= pointsPerFile) {
	delete outFile; outFile = 0;
	++fileCounter;
	pointsCounter = 0;
      }
    }
  }
  delete outFile;
  return 0;
}
