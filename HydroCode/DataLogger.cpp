
#include "Clock.hpp"
#include "DataLogger.hpp"
#include "SDmodule.hpp"

Clock clock;
SDmodule SDmod;

DataLogger::DataLogger()
{
  clock.initializeClock();
}

void DataLogger::writeData()
{
  //clock.dataReadTest();
  clock.refreshClock();
  Clock::ClockData clockDat = clock.getClockData();
  
  SDmod.setDate(clockDat.day, clockDat.month, clockDat.year);

}