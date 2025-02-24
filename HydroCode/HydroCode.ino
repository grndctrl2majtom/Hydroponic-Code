// Main Driver Script for Hydroponic System
  
//#include "Clock.hpp"
//#include "SDmodule.hpp"

#include "DataLogger.hpp"

//Clock clock;
//SDmodule SDmod;

DataLogger dataLog;

void setup()
{
  delay (2000);
  Serial.begin(9600);
  Serial.println("starting");
  //clock.initializeClock();
  //SDmod.ReportCard();
  //SDmod.TestWrite();
}

void loop()
{
  dataLog.writeData();
}
