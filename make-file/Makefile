
CC = g++

CFLAGS = -DDEBUG -std=c++11
export LOCAL_PATH := $(shell pwd)

build: main.o utils.a
	$(CC) -o main $^

main.o: main.cpp utils/utils.h
	$(CC) $(CFLAGS) -c  $<

utils.a:
	($(MAKE) -C utils)

clean:
	-rm -rf *.o
	-rm -rf *.a