#include "hubClass.h"
#include <vector>
#include <iostream>
#include <stdlib.h>     /* srand, rand */
//#include <time.h>       /* time */
#include "hireManager.h"
#include <string.h>
#include <ctime>
#define A 0
#define B 1
#define C 2
#define D 3
#define E 4
#define F 5

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
  for(int a = 1; a <= TOTALBIKES; a++)
  {
    int hubIndex = rand() % TOTALHUBS; // create a random number between 0 and TOTALHUBS
    int number = hub.at(hubIndex).addBike(a); // adds a bike of serial number 'a' to the hub at 'hubIndex' in the vector 'hub'
  }
  for(int a = 0; a < TOTALHUBS; a++)
  {
    std::cout << "There are " <<  hub.at(a).getTotalBikes() << " bikes at hub " << (char)(a + 65) << std::endl;
  }

  hireManager HM;
  int currentSimulationTime = 0;
  for(currentSimulationTime = 0; currentSimulationTime < 24; currentSimulationTime ++)
  {
    std::cout << "Time is Currently: " << currentSimulationTime << ":00 " << std::endl;
    // check bikes to be returned
     std::vector<struct hireRecordStruct> bikesToReturn;
     bikesToReturn = HM.checkRecords(currentSimulationTime);
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
      std::string hireInput = toLowerCase(getStringInput());
      if(hireInput.compare("Y") == 0) // aka they answered yes
      {
        requirementMet = true;
        std::vector<int> nonEmptyHubs = getnonEmptyHubs(hub);
        if(nonEmptyHubs.size() > 0)
        {
          std::cout << "The following hubs have bikes in: ";
          int a = 0;
          for(a = 0; a < nonEmptyHubs.size(); a++)
          {
            std::cout << (char)(nonEmptyHubs.at(a) + 65);
            if(a != (nonEmptyHubs.size() - 1))
            {
              std::cout << ", ";
            }
          }
          std::cout << std::endl;
        }
        else
        {
          std::cout << "All hubs have at least one bike in" << std::endl;
        }
        char originInput;
        bool validInput = false;
        while(validInput == false)
        {
          std::cout << "Please pick a hub to hire a bike from, or type 'X' to cancel" << std::endl;
          originInput = (toLowerCase(getStringInput()))[0];
          int a = 0;
          for(a = 0; a < nonEmptyHubs.size(); a++)
          {
            if(originInput == (char)(nonEmptyHubs.at(a)+'a'))
            {
              validInput = true;
            }
          }
          if(originInput == 'x')
          {
            validInput = true;
            requirementMet = false;
          }
        }
        validInput = false;
        while(validInput == false) // we know where from
        {
          char destinationInput = (toLowerCase(getStringInput()))[0];
          if(destinationInput >= 'a' && destinationInput < ('a' + TOTALHUBS))
          {
            validInput = true;
          }
        }
        int randHireTime = rand() % 24; // pick a random duration to hire bike
        std::cout << "This bike will be hired for " << randHireTime << "hours, thank you." << std::endl;
        struct hireRecordStruct newRecord;
        bike newBikeOut; // create bike object to tranfer details
        int bikesLeft = hub.at(originInput - 'a').takeBike(&newBikeOut); // copy over top bike object, and remove form internal stack
        newRecord.bikeObject = newBikeOut; // insert the bike obect to the record struct
        newRecord.hireTime = currentSimulationTime; // record current time
        newRecord.hireDuration = randHireTime; // record random hire time
        HM.addRecord(newRecord); // add record to hire manager object record vector
      }
      else if(hireInput.compare("N") == 0)
      {
        std::cout << "OK!" << std::endl;
        requirementMet = true;
      }
      else
      {
        std::cout << "That doesn't make any sense, sorry." << std::endl;
      }
    }

    // print bikes in hubs
    int g = 0;
    for(g = 0; g < TOTALHUBS; g++)
    {
      std::cout "Hub " << (char)(g+65) << "has bikes: ";
      hub.at(g).printContents();
      std::cout <<std::endl;
    }
  }
  // print all bikes on hire
    std::cout << "End of Program, Thank You" << std::endl;
  return 0;
}

std::string getStringInput() // a private function that gets a string input from cin
{
  std::string input = ""; // instantiate string
  std::cin >> input; // pipe the command line input into the string
  return input; // set the value at the address of the pointer arguement to the value of the input string.
}

std::string toLowerCase(std::string value) // a privae function that converts letters in a a string to lower case
{
  char *store; // create char array for easy access
  store = new char[(value).length()]; // allocate the correct amount of space
  strcpy(store, (value).c_str()); // copy contents of the string to the char array
  for(int a = 0; a < (value).length(); a++) // iterate through the string
  {
    if (store[a] >= 'A' && store[a] <= 'Z') // if the char is a capital letter
    {
      store[a] = store[a] + ('a' - 'A'); // shift it by the difference, to convert
    }
  }
  return std::string(store); // convert char array back to string object, and assign its value to the pointer argument
}

std::vector<int> getnonEmptyHubs(std::vector<hubClass> hub)
{
  std::vector<int> results;
  int a = 0;
  for(a = 0; a < hub.size(); a++)
  {
    if(hub.at(a).getTotalBikes() > 0) // ie is that hub not empty
    {
      results.push_back(a);
    }
  }
  return results;
}
