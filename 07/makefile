CC = g++
FLAGS = -std=c++17 -Wall

all: test.o
	$(CC) $(FLAGS) test.o -o res

test: res
	./res

test.o: test.cpp
	$(CC) $(FLAGS) -c test.cpp

clean:
	rm *.o res
