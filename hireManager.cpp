#include "hireManager.h"


void hireManager::addRecord(struct hireRecordStruct input) // adds record struct as element of storage vector
{
  Records.push_back(input);
}

void hireManager::deleteRecord(struct hireRecordStruct input) // finds vector element with matching serial number, then erases it
{
  for(int a = 0; a < Records.size(); a++)
  {
    if(Records.at(a).bikeObject.getSN() == input.bikeObject.getSN())
    {
      Records.erase(Records.begin()+a);
    }
  }
}

std::vector<struct hireRecordStruct> hireManager::checkRecords(int currentTime) // checks records for bikes needing to be returned
{
  std::vector<struct hireRecordStruct> recordsToReturn;
  int a;
  for(a = 0; a < Records.size(); a++)
  {
    int expireTime = Records.at(a).hireTime + Records.at(a).hireDuration;
    if(expireTime ==  currentTime)
    {
      recordsToReturn.push_back(Records.at(a));
    }
  }
  return(recordsToReturn);
}

std::vector<struct hireRecordStruct> hireManager::getRecords() // returns entire record struct
{
  return Records;
}

void hireManager::printContents() // does what it says on the tin
{
  //std::cout << "There are " << Records.size() << " records" << std::endl;
  for(int a = 0; a < Records.size(); a++)
  {
    std::cout << "Bike No: " << Records.at(a).bikeObject.getSN();
    std::cout << ", going to hub " << Records.at(a).destination;
    std::cout << ", over: " << Records.at(a).hireDuration << " hours";
    std::cout << ", starting at: " << Records.at(a).hireTime << std::endl;
  }
}

void hireManager::printContentsToFile(std::string input)// opens file stream, then does what it says on the tin
{
  std::ofstream fileOutStream;
  fileOutStream.open(input);
  for(int a = 0; a < Records.size(); a++)
  {
    fileOutStream << "Bike No: " << Records.at(a).bikeObject.getSN();
    fileOutStream << ", going to: " << Records.at(a).destination;
    fileOutStream << ", over: " << Records.at(a).hireDuration << "hours";
    fileOutStream << ", starting at: " << Records.at(a).hireTime << std::endl;
  }
  fileOutStream.close();
}
