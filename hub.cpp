#include "hubClass.h"


char hubClass::makeColour(int totalColours)
{
  srand (time(NULL)); // initialise random algorithm seed
  int colourNum = rand() % totalColours; // genterate a random number between 0 and totalColours
  switch(colourNum)
  {
    case 0:
    {
      return 'R'; // Red
    }
    break;
    case 1:
    {
      return 'B'; // Blue
    }
    break;
    case 2:
    {
      return 'G'; // Green
    }
    break;
    case 3:
    {
      return 'W'; // White
    }
    break;
    case 4:
    {
      return 'P'; // Pink
    }
    break;
    default:
    {
      return 'G'; // Grey
    }
    break;
  }
}

void hubClass::init(int totalBikes)
{
  int a = 1;
  for(a = 1; a <= totalBikes; a++)
  {
    bike *newBike;
    (*newBike).setSN(a);
    (*newBike).setColour(makeColour(6));
    addBike(newBike);
  }
}

int hubClass::addBike(bike *topBike)
{
  bikeStore.push(*topBike);
  return bikeStore.size();
}

int hubClass::takeBike(bike *topBike)
{
  *topBike = bikeStore.top();
  bikeStore.pop();
  return bikeStore.size();
}

int hubClass::totalBikes()
{
  return bikeStore.size();
}
