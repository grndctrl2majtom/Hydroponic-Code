// SDmodulle class contains functions relative to the SD card logging for the hydroponic system

class SDmodule
{
  public:
    SDmodule();

    void ReportCard();

    void setDate(int day, int month, int year);
    void recordData();

    // Test functions
    void TestWrite();

  private:
    const int csPin = 53; // comunicatin pin for uno  
    
    int fileDay;
    int fileMonth;
    int fileYear;

    void createFile();
};