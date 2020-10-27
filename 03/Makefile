CC = g++
FLAGS = -std=c++17 -Wall 

all: matrix.o test.o
	$(CC) $(FLAGS) test.o matrix.o -o res


test: res
	./res
	
parser.o: matrix.cpp 
	$(CC) $(FLAGS) -c matrix.cpp
	 
test.o: test.cpp
	$(CC) $(FLAGS) -c test.cpp
	 
clean:
	rm *.o res





