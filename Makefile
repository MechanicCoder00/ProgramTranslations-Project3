CC	= g++
TARGET	= statSem
OBJS	= parser.o scanner.o statSem.o testTree.o main.o

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)

main.o: main.cpp
	$(CC) -std=c++11 -c main.cpp

testTree.o: testTree.cpp testTree.h
	$(CC) -std=c++11 -c testTree.cpp

statSem.o: statSem.cpp statSem.h
	$(CC) -std=c++11 -c statSem.cpp

scanner.o: scanner.cpp scanner.h
	$(CC) -std=c++11 -c scanner.cpp
	
parser.o: parser.cpp parser.h
	$(CC) -std=c++11 -c parser.cpp

.PHONY: clean
clean:
	/bin/rm -f *.o temp.fs19 $(TARGET)
