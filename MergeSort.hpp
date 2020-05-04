#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>
#include <regex>
#include <fstream>
#include <time.h>
#include <exception>
#include <chrono>
#include <mutex>
#include <atomic>

extern int min_elements;
extern std::mutex thread_creation_mutex;
extern std::atomic<int> numFreeThreads;

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
    // Copy constructor
    TimeStampArray(const TimeStampArray* TSA);

    ~TimeStampArray();
};

// MergeSort fucntions Serial
void MergeSort(TimeStampArray *TSA, int low, int high);
void Merge(TimeStampArray *TSA, int low, int high, int mid);

// MergeSort fucntions Threaded
void MergeSortThreads(TimeStampArray *TSA, int low, int high);
void MergeThreads(TimeStampArray *TSA, int low, int high, int mid);

// Debug Functions
void printTSA(TimeStampArray* TSA);
