#include <stack>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>

#ifndef bikeDefined
  #include "bike.h"
  #define bikeDefined
#endif

#define hubDefined

class hubClass
{
  private:
    std::stack<bike> bikeStore;
    char makeColour(int totalColours);

  public:
    int addBike(int SN);
    int returnBike(bike *topBike);
    int takeBike(bike *topBike);
    int getTotalBikes();
    void printContents();
};
