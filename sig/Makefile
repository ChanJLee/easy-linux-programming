CC = g++
CCFLAG = -std=c++11

main.out: main.o
	$(CC) -o $@ $^

main.o: main.cpp
	$(CC) $(CCFLAG) -c $<

clean:
	-rm -rf *.out
	-rm -rf *.o