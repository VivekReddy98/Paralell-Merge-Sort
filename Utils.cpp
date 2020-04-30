#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include <regex>
#include <time.h>
#include <exception>

#include "MergeSortThreads.h"

TimeStamp::TimeStamp(std::string line){
    std::smatch match;
    std::regex rgx ("[0-9]{4}-[0-9]{2}-[0-9]{2}T[0-9]{2}:[0-9]{2}:[0-9]{2}-[0-9]{2}:[0-9]{2}");

    if (!std::regex_search(line, match, rgx)){
      std::cout << "Match Not Found" << std::endl;
    }

    std::string timestamp(match[0]);

    // std::cout << timestamp << std::endl;
    struct tm time_struct;

    if (strptime(timestamp.c_str(), "%Y-%m-%dT%H:%M:%S%z", &time_struct) == NULL){
        std::cout << "Unable to extract any useful info" << std::endl;
        throw 20;
    }

    time_struct.tm_isdst = -1;

    this->t = mktime(&time_struct);
    this->content = line;
    // std::cout << this->t << ": " << this->content << std::endl;
}

TimeStamp::TimeStamp(std::string content, time_t t){
   this->content = content;
   this->t = t;
}

TimeStampArray::TimeStampArray(std::string path){

  std::ifstream in(path);
  std::string str;
  TimeStamp* obj;
  while (std::getline(in, str)) {

      try{
        obj = new TimeStamp(str);
      }
      catch (int c){
        std::cout << "Unable to extract any useful info" << std::endl;
        break;
      }

      this->Array.push_back(obj);
  }
  in.close();
}

TimeStampArray::~TimeStampArray(){
    for (auto obj : this->Array){
       delete obj;
    }
}

void printTSA(TimeStampArray* TSA){
  for (auto obj : TSA->Array){
      std::cout << obj->t << ": " << obj->content << std::endl;
  }
}
