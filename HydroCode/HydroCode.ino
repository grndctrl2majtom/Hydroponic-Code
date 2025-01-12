// Main Driver Script for Hydroponic System
  
#include "SDmodule.hpp"

SDmodule SDmod;

void setup()
{

  Serial.begin(9600);
  //SDmod.ReportCard();
  SDmod.TestWrite();
}

void loop()
{
}
