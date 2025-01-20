#include "Clock.hpp"

// uRTCLib rtc;
uRTCLib rtc(0x68);

Clock::Clock()
{
  URTCLIB_WIRE.begin();

  //rtc.set(0, 56, 12, 5, 13, 1, 22); // set time then comment out when battery inserted
}


void Clock::refreshClock()
{
  rtc.refresh();

  second = rtc.second();
  minute = rtc.minute();
  hour = rtc.hour();
  day = rtc.day();
  month = rtc.month();
  year = rtc.year();

  clockTemperature = rtc.temp() / 100;
}