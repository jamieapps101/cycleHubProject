#define bikeDefined

class bike
{
  private:
    int serialNumber;
    char colour;

  public:
    int getSN();
    void setSN(int newSN);
    char getColour();
    void setColour(char newColour);
};
