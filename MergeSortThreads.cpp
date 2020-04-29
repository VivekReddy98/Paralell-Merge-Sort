#include <vector>
#include <unordered_map>
#include <regex>
#include <fstream>
#include <time.h>

#include "MergeSortThreads.h"

int main (int argc, char **argv){
    if(argc != 2){
       std::runtime_error("Usage Executable filepath");
    }

    std::string file_path = argv[1];

    TimeStampArray* Array = new TimeStampArray(file_path);
}
