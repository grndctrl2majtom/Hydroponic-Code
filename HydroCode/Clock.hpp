// Clock class contains functions relative to the time keeping for the hydroponic system
#include "Arduino.h"

class Clock
{
  public:
    Clock();

    struct ClockData
    {
      int second;
      int minute;
      int hour;
      int day;
      int month;
      int year;
      int clockTemp;
    };

    ClockData getClockData() {return clockData;}

    void initializeClock();
    void refreshClock();

    // Tests
    void dataReadTest();

  private:

    int second;
    int minute;
    int hour;
    int day;
    int month;
    int year;
    int clockTemperature;

    ClockData clockData;
};