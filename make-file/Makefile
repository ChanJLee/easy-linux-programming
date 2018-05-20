
CC = g++

CFLAGS = -DDEBUG -std=c++11

build: main.o
	$(CC) main.o -o main

main.o: main.cpp
	$(CC) $(CFLAGS) -c  main.cpp

clean:
	rm -rf *.o~