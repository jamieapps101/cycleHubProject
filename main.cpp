#include "hubClass.h"
#include <vector>
#include <iostream>
#include <stdlib.h>     /* srand, rand */
//#include <time.h>       /* time */
#include "hireManager.h"
#include <ctime>
#define A 0
#define B 1
#define C 2
#define D 3
#define E 4
#define F 5

#define TOTALHUBS 6
#define TOTALBIKES 30

void flag(char flagLetter);

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
  for(int a = 1; a <= TOTALBIKES; a++)
  {
    int hubIndex = rand() % TOTALHUBS; // create a random number between 0 and TOTALHUBS
    int number = hub.at(hubIndex).addBike(a); // adds a bike of serial number 'a' to the hub at 'hubIndex' in the vector 'hub'
  }
  for(int a = 0; a < TOTALHUBS; a++)
  {
    std::cout << "There are " <<  hub.at(a).getTotalBikes() << " bikes at hub " << (char)(a + 65) << std::endl;
  }
  std::cout << "End of Program, Thank You" << std::endl;
  hireManager HM;
  int time = 0;
  for(time = 0; time < 24; time ++)
  {
    // check bikes to be returned
     std::vector<struct hireRecordStruct> bikesToReturn;
     bikesToReturn = HM.checkRecords(time);
     if(bikesToReturn.size() > 0)
     {
       std::cout << "The following bikes are to be returned this hour:" << std::endl;
       int b = 0;
       for(b = 0; b < bikesToReturn.size(); b++)
       {
         std::cout << "SN: " << bikesToReturn.at(b).bikeObject.getSN() << ", hired at: " << bikesToReturn.at(b).hireTime << std::endl;
       }
     }

    // prompt user to hire bike
    bool requirementMet = false;
    while(requirementMet == false)
    {
      std::cout << "Hire new bike? (Y/N)" << std::endl;

      // where from
      // where to
      // generate how long randomly
    }

    // print bikes in hubs
  }
  // print all bikes on hire
  return 0;
}
