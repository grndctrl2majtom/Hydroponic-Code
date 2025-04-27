// SDmodulle class contains functions relative to the SD card logging for the hydroponic system

#include "Clock.hpp"

#include <SD.h>

class SDmodule
{
  public:
    SDmodule();

    void ReportCard();

    void recordData(String dataString);

    // Test functions
    void TestWrite();

  private:
    const int csPin = 53; // comunicatin pin for uno  
    
    Clock::ClockData clockDat;

    File dataFile;

    void checkForCard();
    void createFiles();
    void writeLine(String dataString);
};