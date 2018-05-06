#include <iostream>
#include <fstream>
#include <vector>

#ifndef bikeDefined
#include "bike.h"
#define bikeDefined
#endif

#ifndef hubDefined
#include "hubClass.h"
#define hubDefined
#endif

#define TOTALHUBS 6
#define TOTALBIKES 30


int main()
{
  std::ofstream fileOutStream;
  fileOutStream.open ("hubPopulations.txt");
  srand (time(NULL)); // initialise random algorithm seed
  std::cout << "Running Hub Population Program" << std::endl;
  std::vector<hubClass> hub;
  for(int a = 0; a < TOTALHUBS; a++)
  {
    hubClass Hub;
    hub.push_back(Hub);
  }
  for(int a = 1; a <= TOTALBIKES; a++)
  {
    int hubIndex = rand() % TOTALHUBS; // create a random number between 0 and TOTALHUBS
    int number = hub.at(hubIndex).addBike(a); // adds a bike of serial number 'a' to the hub at 'hubIndex' in the vector 'hub'
  }

  for(int a = 0; a < TOTALHUBS; a++)
  {
    fileOutStream << char(65 + a) << ",";
    while(hub.at(a).getTotalBikes() > 0)
    {
      bike currentBike;
      hub.at(a).takeBike(&currentBike);
      fileOutStream << currentBike.getSN() << ":" <<currentBike.getColour() << ",";
    }
    fileOutStream << std::endl;
  }


  fileOutStream.close();
  return 0;
}
