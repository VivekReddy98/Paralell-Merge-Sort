# Paralell-Merge-Sort
Merge Sort using Threads in C++

## Build Configurations

### Serial

       make serial
       ./MST.out {file-path}

       make serial-debug (For Printing the output to console)

### Multi-threaded

       make paralell
       ./MST.out {file-path} {min-elements} {max-threads}

       make paralell-debug (For Printing the output to console)

## Parameters
       
       min-elements: The number of elements for which a new thread is created. 
              Eg: if this is set to one, a new thread is created for every sub partition.
       max-threads: The maximum number of threads which can be created apart from the main thread.

## Data Sources Used:
       
       Time Stamp Datafiles used in HW2.
       Code to extract and compare can be found in Utils.cpp under classes TimeStamp() & TimeStampArray()

## Folder Structure
     
     /
     ├── MergeSort.hpp : Header file containing function & Class declarations
     ├── MergeSortSerial.cpp: Serial Merge Sort Code
     ├── MergeSortThreads.cpp: Paralell Merge Sort Code
     ├── Utils.cpp: Utility functions.
     ├── datafiles/ : Folder containing data files 

