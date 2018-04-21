#include <vector>
#ifndef bikeDefined
  #include "bike.h"
#endif

struct hireRecordStruct
{
 bike bikeObject;
 int hireTime;
 int hireDuration;
};

class hireManager
{
  private:
    std::vector<struct hireRecordStruct> Records;

  public:
    void addRecord(struct hireRecordStruct input);
    std::vector<struct hireRecordStruct> checkRecords(int currentTime);
    std::vector<struct hireRecordStruct> getRecords();
};
