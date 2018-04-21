#include "hireManager.h"

void hireManager::addRecord(struct hireRecordStruct input)
{
  Records.push_back(input);
}

std::vector<struct hireRecordStruct> hireManager::checkRecords(int currentTime)
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

std::vector<struct hireRecordStruct> hireManager::getRecords()
{
  return Records;
}
