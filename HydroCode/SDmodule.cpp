#include "SDmodule.hpp"

#include <SD.h>
#include <SPI.h>

// set up variables using the SD utility library functions:
  Sd2Card card;
  SdVolume volume;
  SdFile root;

SDmodule::SDmodule()
{
  if (!SD.begin(csPin)) 
  {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  Serial.println("card initialized.");
}

void SDmodule::ReportCard()
{
  Serial.print("\nInitializing SD card...");

  // we'll use the initialization code from the utility libraries
  // since we're just testing if the card is working!
  if (!card.init(SPI_HALF_SPEED, csPin)) {
    Serial.println("initialization failed. Things to check:");
    Serial.println("* is a card inserted?");
    Serial.println("* is your wiring correct?");
    Serial.println("* did you change the chipSelect pin to match your shield or module?");
    while (1);
  } else {
    Serial.println("Wiring is correct and a card is present.");
  }

  // print the type of card
  Serial.println();
  Serial.print("Card type:         ");
  switch (card.type()) {
    case SD_CARD_TYPE_SD1:
      Serial.println("SD1");
      break;
    case SD_CARD_TYPE_SD2:
      Serial.println("SD2");
      break;
    case SD_CARD_TYPE_SDHC:
      Serial.println("SDHC");
      break;
    default:
      Serial.println("Unknown");
  }

  // Now we will try to open the 'volume'/'partition' - it should be FAT16 or FAT32
  if (!volume.init(card)) {
    Serial.println("Could not find FAT16/FAT32 partition.\nMake sure you've formatted the card");
    while (1);
  }

  Serial.print("Clusters:          ");
  Serial.println(volume.clusterCount());
  Serial.print("Blocks x Cluster:  ");
  Serial.println(volume.blocksPerCluster());

  Serial.print("Total Blocks:      ");
  Serial.println(volume.blocksPerCluster() * volume.clusterCount());
  Serial.println();

  // print the type and size of the first FAT-type volume
  uint32_t volumesize;
  Serial.print("Volume type is:    FAT");
  Serial.println(volume.fatType(), DEC);

  volumesize = volume.blocksPerCluster();    // clusters are collections of blocks
  volumesize *= volume.clusterCount();       // we'll have a lot of clusters
  volumesize /= 2;                           // SD card blocks are always 512 bytes (2 blocks are 1KB)
  Serial.print("Volume size (Kb):  ");
  Serial.println(volumesize);
  Serial.print("Volume size (Mb):  ");
  volumesize /= 1024;
  Serial.println(volumesize);
  Serial.print("Volume size (Gb):  ");
  Serial.println((float)volumesize / 1024.0);

  Serial.println("\nFiles found on the card (name, date and size in bytes): ");
  root.openRoot(volume);

  // list all files in the card with date and size
  root.ls(LS_R | LS_DATE | LS_SIZE);
}

void SDmodule::setDate(int day,  int month, int year)
{
  fileDay = day;
  fileMonth = month;
  fileYear = year;
}


void SDmodule::recordData()
{
  createFile();
}

void SDmodule::createFile()
{
  String day = String(fileDay);
  String month = String(fileMonth);
  String year = String(fileYear);

  String fileBase = "HydroponicData";

  String fullfile = fileBase + "_" + day + "_" + month + "_" + year + ".csv";

  File dataFile = SD.open(fullfile, FILE_WRITE);
}

void SDmodule::TestWrite()
{

  if (!SD.begin(csPin)) 
  {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  Serial.println("card initialized.");

  String testMessage = "Hello! The file parse worked!";

  if (SD.exists("TestFile.txt"))
  {
    Serial.println("Deleting file");
    SD.remove("TestFile.txt");
  }

  File dataFile = SD.open("TestFile.txt", FILE_WRITE);

  // if the file is available, write to it:
  if(dataFile)
  {
    dataFile.println(testMessage);
    dataFile.close();
    Serial.println("print should've worked, the following was read from file:");
  }
  else
  {
    Serial.println("error opening file");
  }

  File myFile = SD.open("TestFile.txt");
  if (myFile) 
  {
    Serial.println("test.txt:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) 
    {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } 
  else 
  {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }

}

