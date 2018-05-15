build: clean main.o lock.o deamon.o
	g++ lock.o main.o -std=c++11 -o main
	g++ lock.o deamon.o -std=c++11 -o deamon

main.o: lock.h main.cpp
	g++ -c -std=c++11 main.cpp

lock.o: lock.h lock.cpp
	g++ -c -std=c++11 lock.cpp

deamon.o: lock.h deamon.cpp
	g++ -c -std=c++11 deamon.cpp

clean:
	rm -rf *.o