all:
	g++ -std=c++11 Utils.cpp MergeSortThreads.cpp -o MST.out

clean:
	rm *.out
