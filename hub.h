#include <stack>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "bike.h"

class hub
{
  private:
    std::stack<bike> bikeStore;
    char makeColour(int totalColours);

  public:
    void init(int totalBikes);
    int addBike(bike *topBike);
    int takeBike(bike *topBike);
};
