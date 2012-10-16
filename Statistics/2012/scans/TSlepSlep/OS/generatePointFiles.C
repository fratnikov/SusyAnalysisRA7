#include <string>
#include <iostream>
#include <fstream>
using namespace std;

int generatePointFiles ()
{
  const char* baseName = "SUSY_scan_v1";
  int pointsPerFile = 10;
  int fileCounter = 1;
  int pointsCounter = 0;
  int tanb = 3;
  ofstream* outFile = 0;
  for (int m1 = 100; m1 <= 300; m1 += 25) {
    for (int m2 = 0; m2 <= m1-25; m2 += 25) {
      if (!pointsCounter) {
	char fileName [1024];
	sprintf (fileName, "%s.%d.txt", baseName, fileCounter);
	outFile = new ofstream (fileName);
      }
      cout << m1<<':'<<m2<<" -> " << fileCounter << endl;
      *outFile << m1 << ' ' << m2 << ' ' << tanb << endl;
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
