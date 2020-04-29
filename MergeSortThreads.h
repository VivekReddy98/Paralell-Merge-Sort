#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>
#include <regex>
#include <fstream>
#include <time.h>

class TimeStamp {
  public:
    std::string content;
    time_t t;

    TimeStamp(std::string);
};


class TimeStampArray{
  public:
    std::vector<TimeStamp*> Array;

    TimeStampArray(std::string path);
    ~TimeStampArray();
};
