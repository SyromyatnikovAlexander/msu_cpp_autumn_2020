CC = g++
FLAGS = -std=c++17 -Wall 

all: parser.o test.o
	$(CC) $(FLAGS) test.o parser.o -o res


test: res
	./res
	
parser.o: parser.cpp 
	$(CC) $(FLAGS) -c parser.cpp
	 
test.o: test.cpp
	$(CC) $(FLAGS) -c test.cpp
	 
clean:
	rm *.o res





