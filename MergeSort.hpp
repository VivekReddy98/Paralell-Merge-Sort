#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>
#include <regex>
#include <fstream>
#include <time.h>
#include <exception>


class TimeStamp {
  public:
    std::string content;
    time_t t;

    TimeStamp(std::string);
    TimeStamp(std::string, time_t t);
};

class TimeStampArray{
  public:
    std::vector<TimeStamp*> Array;

    TimeStampArray(std::string path);
    ~TimeStampArray();
};

// MergeSort fucntions
void MergeSort(TimeStampArray *TSA, int low, int high);
void Merge(TimeStampArray *TSA, int low, int high, int mid);

// Debug Functions
void printTSA(TimeStampArray* TSA);
