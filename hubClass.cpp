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

int hubClass::addBike(int SN) // makes a new bike object and adds it to main storage stack within hub object.
{
  bike newBike;
  (newBike).setSN(SN);
  (newBike).setColour(makeColour(6));
  bikeStore.push(newBike);
  return bikeStore.size();
}

int hubClass::returnBike(bike *topBike) // simply adds bike object on input to the stack
{
  bikeStore.push(*topBike);
  return bikeStore.size();
}

int hubClass::takeBike(bike *topBike) // takes top element of stack, and returns it via pointer, then pops top element
{
  *topBike = bikeStore.top();
  bikeStore.pop();
  return bikeStore.size();
}


int hubClass::getTotalBikes() // does what it says on the tin
{
  return bikeStore.size();
}

void hubClass::printContents()// does what it says on the tin, this reads elements one by one,
{                             //  printing them and saving them to temp stack. then transfers them all back
  std::stack<bike> tempBikeStore;
  while (!bikeStore.empty())
  {
    std::cout << bikeStore.top().getSN() << ", ";
    tempBikeStore.push(bikeStore.top());
    bikeStore.pop();
  }
  while (!tempBikeStore.empty())
  {
    bikeStore.push(tempBikeStore.top());
    tempBikeStore.pop();
  }
}
