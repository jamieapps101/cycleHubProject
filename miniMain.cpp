#include "hubClass.h"
#include <vector>
#include <iostream>
#include <stdlib.h>     /* srand, rand */
//#include <time.h>       /* time */
#include "hireManager.h"
#include<fstream>
#include <string.h>
#include <ctime>
#define A 0
#define B 1
#define C 2
#define D 3
#define E 4
#define F 5

#define fileName "hubPopulations.txt"

#define TOTALHUBS 6
#define TOTALBIKES 30

std::string  getStringInput();
std::string  toLowerCase(std::string value);
void removeSpaces(std::string *value);
std::vector<int> getnonEmptyHubs(std::vector<hubClass> hub);

int main()
{
  srand (time(NULL)); // initialise random algorithm seed
  std::cout << "Welcome to bike simulator" << std::endl;
  std::vector<hubClass> hub;
  int a;
  for(a = 0; a < TOTALHUBS; a++)
  {
    hubClass Hub;
    hub.push_back(Hub);
  }

  // Read files here
  std::ifstream inputFile;
  inputFile.open(fileName);
  if(inputFile.is_open() != true)
  {
    inputFile.close();
    return 1;
  }
  std::string line;
  int lineCount = 0;
  while (std::getline(inputFile, line))
  {
    char hubChar = line.at(0); // get first char which refs the hub
    int hubNumber = (int)hubChar -65; // convert to integer
    line.erase(0,2); // get rid of the char and the comma.
    while(line.size() > 1) // accounts for \n
    {
      int readTo = line.find(":");
      std::string::size_type sz;   // alias of size_t
      int inputSN = std::stoi ((line.substr(0,readTo)),&sz);
      line.erase(0, readTo+1); //get rid of numbers and ":"
      char inputColour = (char)line.at(0); // get char corresponding to colour
      bike inputBike;
      inputBike.setSN(inputSN);
      inputBike.setColour(inputColour);
      hub.at(hubNumber).returnBike(&inputBike);
      line.erase(0, 2); // get rid of char and comma
    }
    lineCount++;
  }
  inputFile.close();
  // Read files there
}
