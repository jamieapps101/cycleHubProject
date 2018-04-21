#include "hubClass.h"


char hubClass::makeColour(int totalColours)
{
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

int hubClass::addBike(int SN)
{
  bike newBike;
  (newBike).setSN(SN);
  (newBike).setColour(makeColour(6));
  bikeStore.push(newBike);
  return bikeStore.size();
}

int hubClass::returnBike(bike *topBike)
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


int hubClass::getTotalBikes()
{
  return bikeStore.size();
}

void hubClass::printContents()
{
  std::stack<bike> tempBikeStore;
  while (!bikeStore.empty())
  {
    std::cout << bikeStore.top() << ', ';
    tempBikeStore.push(bikeStore.top());
    bikeStore.pop();
  }
  while (!tempBikeStore.empty())
  {
    bikeStore.push(tempBikeStore.top());
    tempBikeStore.pop();
  }
}
