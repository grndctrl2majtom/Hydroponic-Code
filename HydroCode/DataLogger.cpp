
//#include "Clock.hpp"
#include "DataLogger.hpp"
#include "SDmodule.hpp"

//Clock clock;
SDmodule SDmod;

DataLogger::DataLogger()
{
  //SDmod.ReportCard();
}

void DataLogger::writeData(String dataString)
{
  SDmod.recordData(dataString);

}