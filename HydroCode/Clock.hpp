// Clock class contains functions relative to the time keeping for the hydroponic system

#include "uRTCLib.h"

class Clock
{
  public:
    Clock();

    int getSecond() {return second;}
    int getMinute() {return minute;}
    int getHour() {return hour;}
    int getDay() {return day;}
    int getMonth() {return month;}
    int getYear() {return year;}
    int getClockTemperature() {return clockTemperature;}

    void refreshClock();

  private:

    int second;
    int minute;
    int hour;
    int day;
    int month;
    int year;
    int clockTemperature;

};