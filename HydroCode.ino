// Main Driver Script for Hydroponic System
  
#include "SDmodule.hpp"

SDmodule SD;

void setup()
{

  Serial.begin(9600);
  SD.ReportCard();
}

void loop()
{
}
