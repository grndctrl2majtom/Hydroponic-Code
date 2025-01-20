// SDmodulle class contains functions relative to the SD card logging for the hydroponic system

class SDmodule
{
  public:
    SDmodule();
    void ReportCard();
    void TestWrite();

  private:
    const int csPin = 53; // comunicatin pin for uno  

};