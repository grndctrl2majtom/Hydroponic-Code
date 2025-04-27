// Main Driver Script for Hydroponic System
  
//#include "Clock.hpp"
//#include "SDmodule.hpp"

#include "DataLogger.hpp"

//Clock clock;
//SDmodule SDmod;

DataLogger dataLog;

void setup()
{
  Serial.begin(9600);
  Serial.println("starting");
  delay (250);
  //clock.initializeClock();
  //SDmod.ReportCard();
  //SDmod.TestWrite();
}

void loop()
{
  dataLog.writeData("test");
  delay(5000);
}
