CC = g++
CCFLAG = -std=c++11

build: writer.out reader.out

writer.out: writer.o
	$(CC) -o $@ $^

writer.o: writer.cpp c.h
	$(CC) $(CCFLAG) -c $<


reader.out: reader.o
	$(CC) -o $@ $^

reader.o: reader.cpp c.h
	$(CC) $(CCFLAG) -c $<

clean:
	-rm -rf *.o
	-rm -rf *.out