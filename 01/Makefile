
CC = g++
FLAGS = -std=c++17 -Wall 

all: main.o


test: main.o test.o
	$(CC) $(FLAGS) test.o main.o -o test
	
main.o: main.cpp 
	$(CC) $(FLAGS) -c main.cpp
	 
test.o: test.cpp
	$(CC) $(FLAGS) -c test.cpp
	 
clean:
	rm *.o result





