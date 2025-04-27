#include "SDmodule.hpp"

#include <SPI.h>

  Clock clock;

// set up variables using the SD utility library functions:
  Sd2Card card;
  SdVolume volume;
  SdFile root;

SDmodule::SDmodule()
{
}

void SDmodule::recordData(String dataString)
{
  checkForCard();
  //clock.dataReadTest();
  clock.initializeClock();
  clock.refreshClock();
  //clock.dataReadTest();
  clockDat = clock.getClockData();
  
  createFiles();
  writeLine(dataString);

  //TestWrite();
  //while(1);
}

void SDmodule::checkForCard()
{
  if (!SD.begin(csPin)) 
  {
    Serial.println("Card failed, or not present: Insert card to continue logging");
    // don't do anything until card inserted:
    while (!SD.begin(csPin));
    delay(50);
    Serial.println("card initialized.");
  }
}

void SDmodule::createFiles()
{
  String day = String(clockDat.day);
  String month = String(clockDat.month);
  String year = String(clockDat.year);

  if(clockDat.day < 10)
  {
    day = "0" + day;
  }
  if(clockDat.month)
  {
    month = "0" + month;
  }

  //String fileBase = "Data.csv";

  String folderBase = year + month + day;
  String dataFilename = "LogDat.csv";
  String fileDir = "/" + folderBase + "/" + dataFilename;
  //File dataFile = SD.open(fullFile, FILE_WRITE);
  //dataFile = SD.open(fileBase, FILE_WRITE); // file

  if(!SD.exists(folderBase))
  {
    Serial.print("Folder does not exist, reating Folder ");
    Serial.println(folderBase);
    SD.mkdir(folderBase);
  }

  if(!SD.exists(fileDir))
  {
    Serial.print("File does not exists, creating ");
    Serial.println(fileDir);
    Serial.println();
    String headerline = "Time, TestVar";
    dataFile = SD.open(fileDir, FILE_WRITE); // file
    delay(5);
    
    dataFile.println(headerline);
  }
  else
  {
    dataFile = SD.open(fileDir, FILE_WRITE); // file
    delay(5);
  }
  
  // if the file is available, write to it:
  if(!dataFile)
  {
    Serial.print("error opening file ");
    Serial.println(fileDir);
  }
}

void SDmodule::writeLine(String dataString)
{
  String second = String(clockDat.second);
  String minute = String(clockDat.minute);
  String hour = String(clockDat.hour);

  if(clockDat.second < 10)
  {
    second = "0" + second;
  }
  if(clockDat.minute < 10)
  {
    minute = "0" + minute;
  }
  if(clockDat.hour < 10)
  {
    hour = "0" + hour;
  }

  String timeString = second + ":" + minute + ":" + hour;

  String dataLine = timeString + ", " + dataString;

  dataFile.println(dataLine);
  dataFile.close();
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

  dataFile = SD.open("TestFile.txt", FILE_WRITE);

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