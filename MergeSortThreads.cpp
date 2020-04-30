#include <vector>
#include <unordered_map>
#include <regex>
#include <fstream>
#include <time.h>
#include <exception>

#include "ThreadPool/ThreadPool.h"
#include "MergeSort.hpp"

int min_elements;
int max_threads;

// A function to split array into two parts.
void MergeSort(TimeStampArray *TSA, int low, int high)
{
	int mid;
	if (low < high)
	{
		mid=(low+high)/2;
		// Split the data into two half.
		MergeSort(TSA, low, mid);
		MergeSort(TSA, mid+1, high);

		// Merge them to get sorted output.
		Merge(TSA, low, high, mid);
	}
}

// A function to merge the two half into a sorted data.
void Merge(TimeStampArray *TSA, int low, int high, int mid)
{
	// We have low to mid and mid+1 to high already sorted.
	int i, j;

  std::vector<TimeStamp*> tempArray;

	i = low;
	j = mid + 1;

  TimeStamp* obj;
	// Merge the two parts into temp[].
	while (i <= mid && j <= high)
	{
		if (TSA->Array.at(i)->t < TSA->Array.at(j)->t)
		{
      obj = new TimeStamp(TSA->Array.at(i)->content, TSA->Array.at(i)->t);
			tempArray.push_back(obj);
			i++;
		}
		else
		{
      obj = new TimeStamp(TSA->Array.at(j)->content, TSA->Array.at(j)->t);
			tempArray.push_back(obj);
			j++;
		}
	}

	// Insert all the remaining values from i to mid into temp[].
	while (i <= mid)
	{
    obj = new TimeStamp(TSA->Array.at(i)->content, TSA->Array.at(i)->t);
    tempArray.push_back(obj);
		i++;
	}

	// Insert all the remaining values from j to high into temp[].
	while (j <= high)
	{
    obj = new TimeStamp(TSA->Array.at(j)->content, TSA->Array.at(j)->t);
    tempArray.push_back(obj);
		j++;
	}

  // std::cout << "Merge Sort: " << low << ":" << high << std::endl;
	// Assign sorted data stored in temp[] to a[].
	for (i = low; i <= high; i++)
	{
    TSA->Array.at(i)->content = tempArray.at(i-low)->content;
		TSA->Array.at(i)->t = tempArray.at(i-low)->t;
	}

  //Clean up
  for (auto obj : tempArray){
     delete obj;
  }

}


int main (int argc, char **argv){
    if(argc != 2){
       std::runtime_error("Usage Executable filepath min_elements max_threads");
    }

    std::string file_path = argv[1];
    min_elements = stoi(argv[2]);
    max_threads = stoi(argv[3]);

    TimeStampArray* TSA = new TimeStampArray(file_path);

    ThreadPool pool(max_threads);

     try
     {
       MergeSort(TSA, 0, TSA->Array.size()-1);
     }
     catch (std::runtime_error& e)
     {
       std::cout << "Runtime Error: " << e.what() << std::endl;
     }

    // printTSA(TSA);

    delete TSA;
}
