CC = g++
CCFLAG = -std=c++11

main: main.o
	$(CC) -o $@ $^

main.o: main.cpp
	$(CC) $(CCFLAG) -c $<

clean:
	-rm -rf *.o