#include "hubClass.h"
#include <vector> // needed for listing hubs
#include <iostream>
#include <stdlib.h>     /* srand, rand */
//#include <time.h>       /* time */
#include "hireManager.h"
#include<fstream>
#include <string.h>
#include <sstream>
#include <ctime> // Not sure for this one
#define A 0
#define B 1
#define C 2
#define D 3
#define E 4
#define F 5

const std::string inputFileName = "hubPopulations.txt"; // These make it easy to configure the program
#define outputFileName "finalHhubPopulation.txt"

#define TOTALHUBS 6 // again, configuration. Should work up to 26 hubs, not tested cycle limit
#define TOTALBIKES 30

std::string  getStringInput(); // a few repeatedly use code sections which are worth putting into functions
std::string  toLowerCase(std::string value);
void removeSpaces(std::string *value);
std::vector<int> getnonEmptyHubs(std::vector<hubClass> hub);

int main()
{
  srand (time(NULL)); // initialise random algorithm seed
  std::cout << "Welcome to bike simulator" << std::endl; // Say Hi
  std::vector<hubClass> hub; // instantiate vector of hub, containing no elements
  int a;
  for(a = 0; a < TOTALHUBS; a++) // add elements to vector
  {
    hubClass Hub; // create object
    hub.push_back(Hub); // add object as element
  }

  // Read files here
  std::ifstream inputFile;
  inputFile.open(inputFileName); // open input stream, on file specified above
  if(inputFile.is_open() != true) // check file actually opened
  {
    std::cout << "Cannot open file named: " << inputFileName << ", exiting" << std::endl;
    inputFile.close();
    return 1; // exit program if input data not found
  }
  std::string line;
  int lineCount = 0;
  while (std::getline(inputFile, line))// attempt to read line from file, if successful run code in while loop
  {
    char hubChar = line.at(0); // get first char which refs the hub
    int hubNumber = (int)hubChar -65; // convert to integer
    line.erase(0,2); // get rid of the char and the comma.
    while(line.size() > 1) // accounts for \n
    {
      int readTo = line.find(":");
      std::string::size_type sz;   // alias of size_t, needed for stoi function arugments
      int inputSN = std::stoi ((line.substr(0,readTo)),&sz); // converts string to int
      line.erase(0, readTo+1); //get rid of numbers and ":"
      char inputColour = (char)line.at(0); // get char corresponding to colour
      bike inputBike; // create object to hold data
      inputBike.setSN(inputSN); //populate data
      inputBike.setColour(inputColour);
      hub.at(hubNumber).returnBike(&inputBike); // add bike to relevent hub
      line.erase(0, 2); // get rid of char and comma
    }
    lineCount++;
  }
  inputFile.close(); // finished reading file, so close the stream
  // Read files there

  for(int a = 0; a < TOTALHUBS; a++) // print out contents of hubs
  {
    std::cout << "Hub " << (char)(65 + a) << " contains: ";
    hub.at(a).printContents();
    std::cout << std::endl;
  }

  hireManager HM;
  for(int currentSimulationTime = 0; currentSimulationTime < 24; currentSimulationTime ++) // main time hour loop
  {
    std::cout << "Time is Currently: " << currentSimulationTime << ":00 " << std::endl; // inform user of time
    // check bikes to be returned
     std::vector<struct hireRecordStruct> bikesToReturn; // make vector to store bikes to be returned
     bikesToReturn = HM.checkRecords(currentSimulationTime); // use recordmanager object to check due bikes
     if(bikesToReturn.size() > 0)
     {
       std::cout << "The following bikes are to be returned this hour:" << std::endl;
       int b = 0;
       for(b = 0; b < bikesToReturn.size(); b++) // print bikes to be returned, then return them to relevent hub and delete the hire record
       {
         std::cout << "Bike No " << bikesToReturn.at(b).bikeObject.getSN() << ", which  was hired at: " << bikesToReturn.at(b).hireTime << std::endl;
         int hubToReturnTo = (int)bikesToReturn.at(b).destination - 'A';
         bike returnBike = bikesToReturn.at(b).bikeObject;
         hub.at(hubToReturnTo).returnBike(&returnBike);
         HM.deleteRecord(bikesToReturn.at(b));
       }
     }

    // prompt user to hire bike, this is the main UI section
    bool requirementMet = false;
    while(requirementMet == false)
    {
      std::cout << "Hire new bike? (Y/N)" << std::endl;
      std::string hireInput = toLowerCase(getStringInput());
      if(hireInput.compare("y") == 0) // aka they answered yes
      {
        requirementMet = true;
        std::vector<int> nonEmptyHubs = getnonEmptyHubs(hub); // does what it says on the tin, and prints them
        if(nonEmptyHubs.size() < 6)
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
          std::string temp = toLowerCase(getStringInput());
          originInput = (char)temp.at(0);
          int a = 0;
          for(a = 0; a < nonEmptyHubs.size(); a++)
          {
            if(originInput == (nonEmptyHubs.at(a)+'a'))
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
        if(requirementMet == true)
        {
          char destinationInput;
          validInput = false;
          while(validInput == false)
          {
            std::cout << "Please pick a destinaton hub" << std::endl; // prompt use for destination
            destinationInput =  (toLowerCase(getStringInput()))[0];
            if(destinationInput >= 'a' && destinationInput < ('a' + TOTALHUBS))
            {
              validInput = true;
            }
          }
          int randHireTime = rand() % 24; // pick a random duration to hire bike
          struct hireRecordStruct newRecord;
          bike newBikeOut; // create bike object to tranfer details
          int bikesLeft = hub.at(originInput - 'a').takeBike(&newBikeOut); // copy over top bike object, and remove form internal stack
          newRecord.bikeObject = newBikeOut; // insert the bike obect to the record struct
          newRecord.hireTime = currentSimulationTime; // record current time
          newRecord.hireDuration = randHireTime; // record random hire time
          newRecord.destination = destinationInput-'a' + 'A'; // record desintation input
          HM.addRecord(newRecord); // add record to hire manager object record vector
          std::cout << "Bike number " << newBikeOut.getSN() << " will be hired for " << randHireTime << " hours, thank you." << std::endl;
        }
      }
      else if(hireInput.compare("n") == 0)
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
      std::cout << "Hub " << (char)(g+65) << " has bikes: ";
      hub.at(g).printContents();
      std::cout << std::endl;
    }
    std::cout << "The following bikes are on loan:" << std::endl; // print bikes on loan
    HM.printContents();
    std::cout << std::endl << std::endl;
  }

  // print all stuff to the files
  std::string templateString = outputFileName;
  for(int a = 0; a < TOTALHUBS; a++)
  {
    std::ofstream fileOutStream;
    std::stringstream ss;
    ss << "Hub" << (char)(65+a) << outputFileName;
    std::string HubNameString = ss.str();
    fileOutStream.open (HubNameString);
    fileOutStream << char(65 + a) << ",";
    while(hub.at(a).getTotalBikes() > 0)
    {
      bike currentBike;
      hub.at(a).takeBike(&currentBike);
      fileOutStream << currentBike.getSN() << ":" <<currentBike.getColour() << ",";
    }
    fileOutStream << std::endl;
    fileOutStream.close();
  }
  std::ofstream fileOutStream;
  std::stringstream ss;
  ss << "OnLoan" << outputFileName;
  std::string HubNameString = ss.str();
  HM.printContentsToFile(HubNameString);
  std::cout << "End of Program, Thank You" << std::endl;
  return 1;
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
