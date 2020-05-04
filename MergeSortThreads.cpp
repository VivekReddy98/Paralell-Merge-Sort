#include <vector>
#include <unordered_map>
#include <regex>
#include <fstream>
#include <time.h>
#include <functional>
#include <exception>
#include <atomic>
#include <thread>
#include <mutex>
#include <chrono>
#include <unistd.h>

#include "MergeSort.hpp"

int min_elements;

std::mutex thread_creation_mutex;

std::atomic<int> numFreeThreads;

// A function to split array into two parts.
void MergeSortThreads(TimeStampArray *TSA, int low, int high)
{
  // std::cout << low << ":" << high << std::endl;
	int mid;
	if (low < high)
	{
		// Split the data into two half.
    mid=(low+high)/2;

    if (high-low+1 >= min_elements || numFreeThreads.load() == 0){

				std::vector<std::thread> TPool;

				{ // Scope for the Critical Section
				std::lock_guard<std::mutex> lock(thread_creation_mutex);
					if (numFreeThreads.load() > 2){
							std::thread t1(std::bind(MergeSortThreads, TSA, low, mid));
							std::thread t2(std::bind(MergeSortThreads, TSA, mid+1, high));
							TPool.push_back(std::move(t1));
							TPool.push_back(std::move(t2));
							numFreeThreads.fetch_sub(2);
					}
					else if (numFreeThreads.load() > 1){
						  std::thread t1(std::bind(MergeSortThreads, TSA, low, mid));
							TPool.push_back(std::move(t1));
							numFreeThreads.fetch_sub(1);
					}
			  }

				if (TPool.size() == 1) MergeSortThreads(TSA, mid+1, high);
				else if (TPool.size() == 0){
					MergeSortThreads(TSA, low, mid);
		  		MergeSortThreads(TSA, mid+1, high);
				}

			// Iterate over the thread vector
			for (std::thread& th : TPool)
			{
				// If thread Object is Joinable then Join that thread.
				if (th.joinable())
					th.join();
				else
					printf("Thread is not joinable, Dangling thread WARNING");
			}
		}
    else{
      MergeSortThreads(TSA, low, mid);
  		MergeSortThreads(TSA, mid+1, high);
    }

		// Merge them to get sorted output.
		MergeThreads(TSA, low, high, mid);
	}
  // return 1;
}

// A function to merge the two half into a sorted data.
void MergeThreads(TimeStampArray *TSA, int low, int high, int mid)
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
    min_elements = std::stoi(argv[2]);
    int max_threads = std::stoi(argv[3]);

		auto start = std::chrono::steady_clock::now();

    TimeStampArray* TSA = new TimeStampArray(file_path);

		auto end = std::chrono::steady_clock::now();

		std::cout << "Time to Load Data : "
							<< std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
							<< " ms" << std::endl;

		numFreeThreads.store(max_threads);

		start = std::chrono::steady_clock::now();
    try
    {
     MergeSortThreads(TSA, 0, TSA->Array.size()-1);
    }
    catch (std::runtime_error& e)
    {
     std::cout << "Runtime Error: " << e.what() << std::endl;
    }
		end = std::chrono::steady_clock::now();

		std::cout << "Time to Sort Data : "
							<< std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
							<< " ms" << std::endl;

#ifdef DEBUG
    printTSA(TSA);
#endif

    delete TSA;
}
