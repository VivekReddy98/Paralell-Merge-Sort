serial:
	g++ -std=c++11 Utils.cpp MergeSortSerial.cpp -o MST.out

paralell:
	g++ -std=c++11 Utils.cpp MergeSortThreads.cpp -I include/ -lpthread -o MST.out

clean:
	rm *.out/
