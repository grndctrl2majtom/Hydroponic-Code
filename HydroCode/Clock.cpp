#include "Clock.hpp"
#include "uRTCLib.h"

// uRTCLib rtc;
uRTCLib rtc(0x68);

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

Clock::Clock()
{
  clockData.second = 0;
  clockData.minute = 0;
  clockData.hour = 0;
  clockData.day = 0;
  clockData.month = 0;
  clockData.year = 0;
  clockData.clockTemp = 0;
}


void Clock::initializeClock()
{
	#ifdef ARDUINO_ARCH_ESP8266
		URTCLIB_WIRE.begin(0, 2); // D3 and D4 on ESP8266
	#else
		URTCLIB_WIRE.begin();
	#endif

  // rtc.set(0, 50, 19, 7, 23, 2, 25);
  // rtc.set(second, minute, hour, dayOfWeek, dayOfMonth, month, year)
  // set day of week (1=Sunday, 7=Saturday
}

void Clock::refreshClock()
{
  rtc.refresh();

  clockData.second = rtc.second();
  clockData.minute = rtc.minute();
  clockData.hour = rtc.hour();
  clockData.day = rtc.day();
  clockData.month = rtc.month();
  clockData.year = rtc.year();
}

void Clock::dataReadTest()
{
  rtc.refresh();

  Serial.print("Current Date & Time: ");
  Serial.print(rtc.month());
  Serial.print('/');
  Serial.print(rtc.day());
  Serial.print('/');
  Serial.print(rtc.year());

  Serial.print(" (");
  Serial.print(daysOfTheWeek[rtc.dayOfWeek()-1]);
  Serial.print(") ");

  Serial.print(rtc.hour());
  Serial.print(':');
  Serial.print(rtc.minute());
  Serial.print(':');
  Serial.println(rtc.second());

  Serial.print("Temperature: ");
  Serial.print(rtc.temp()  / 100);
  Serial.print("\xC2\xB0");   //shows degrees character
  Serial.println("C");

  Serial.println();
  delay(1000);
}