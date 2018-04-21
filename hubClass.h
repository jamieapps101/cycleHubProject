#include <stack>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#ifndef bikeDefined
  #include "bike.h"
#endif
#include <iostream>

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
    void printContents()
};
