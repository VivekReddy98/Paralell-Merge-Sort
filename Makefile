serial:
	g++ -std=c++11 Utils.cpp MergeSortSerial.cpp -o MST_Serial.out

serial-debug:
	g++ -std=c++11 -DDEBUG Utils.cpp MergeSortSerial.cpp -o MST_Serial.out

paralell:
	g++ -std=c++11 Utils.cpp MergeSortThreads.cpp -lpthread -o MST.out

paralell-debug:
	g++ -std=c++11 -DDEBUG Utils.cpp MergeSortThreads.cpp -lpthread -o MST.out

clean:
	rm *.out
