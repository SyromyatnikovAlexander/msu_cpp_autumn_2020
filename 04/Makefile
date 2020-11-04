CC = g++
FLAGS = -std=c++17 -Wall 

all: BigInt.o test.o
	$(CC) $(FLAGS) test.o BigInt.o -o res


test: res
	./res
	
BigInt.o: BigInt.cpp 
	$(CC) $(FLAGS) -c BigInt.cpp
	 
test.o: test.cpp
	$(CC) $(FLAGS) -c test.cpp
	 
clean:
	rm *.o res





