// Main Driver Script for Hydroponic System
  
#include "Clock.hpp"
#include "SDmodule.hpp"

Clock clock;
SDmodule SDmod;

void setup()
{

  Serial.begin(9600);
  //SDmod.ReportCard();
  //SDmod.TestWrite();
}

void loop()
{
  //clock.refreshClock();
  //Serial.println("here");
  //Serial.println(clock.getSecond());

  //delay(100);
}
