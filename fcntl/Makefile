build: clean main.o deamon.o 
	g++ main.o -std=c++11 -o main
	g++ deamon.o -std=c++11 -o deamon
	
main.o: main.cpp
	g++ -c -std=c++11 main.cpp

deamon.o: deamon.cpp
	g++ -c -std=c++11 deamon.cpp

clean:
	rm -rf *.o