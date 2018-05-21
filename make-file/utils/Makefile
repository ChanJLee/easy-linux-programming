AR = ar
CC = g++
CCFLAGS = -std=c++11
ARFLAGS = rcs

build: utils.o str_utils.o
	$(AR) $(ARFLAGS) utils.a $^
	mv utils.a $(LOCAL_PATH)/utils.a

utils.o: utils.cpp utils.h
	$(CC) $(CCFLAGS) -c $<

str_utils.o: str_utils.cpp str_utils.h utils.h
	$(CC) $(CCFLAGS) -c $<

clean:
	-rm -rf *.a
	-rm -rf *.gch
	-rm -rf *.o

# $@          --代表目标文件(target)
# $^          --代表所有的依赖文件(components)
# $<          --代表第一个依赖文件(components中最左边的那个)。