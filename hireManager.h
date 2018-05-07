#include <vector>
#include<fstream>
#include <iostream>
#include <string.h>
#ifndef bikeDefined
  #include "bike.h"
#endif

struct hireRecordStruct
{
 bike bikeObject;
 int hireTime;
 int hireDuration;
 char destination;
};

class hireManager
{
  private:
    std::vector<struct hireRecordStruct> Records;

  public:
    void addRecord(struct hireRecordStruct input);
    void deleteRecord(struct hireRecordStruct input);
    std::vector<struct hireRecordStruct> checkRecords(int currentTime);
    std::vector<struct hireRecordStruct> getRecords();
    void printContents();
    void printContentsToFile(std::string input);
};
