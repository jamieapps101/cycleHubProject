#include "bike.h"

int bike::getSN()
{
  return serialNumber;
}

void bike::setSN(int newSN)
{
  serialNumber = newSN;
}

char bike::getColour()
{
  return colour;
}

void bike::setColour(char newColour)
{
  colour = newColour;
}
