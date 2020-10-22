#include <cstddef>
#include <cassert>
#include "allocator.h"
#include <iostream>

void allocTest() {
    Allocator allocator;
    allocator.makeAllocator(20 * sizeof(char));
    char * tmpPointer1 = allocator.alloc(sizeof(char));
    tmpPointer1[0] = 'a';
    tmpPointer1[1] = 'b';
    char * tmpPointer2 = allocator.alloc(sizeof(char));
    tmpPointer2[0] = 'c';
    std::cout << "Testing alloc" << std::endl;
    assert(tmpPointer1[0] == 'a' && tmpPointer1[1] == 'c');
}

void resetTest() {
    Allocator allocator;
    allocator.makeAllocator(20 * sizeof(char));
    char* tmpPointer1 = allocator.alloc(5 * sizeof(char));
    allocator.reset();
    char* tmpPointer2 = allocator.alloc(5 * sizeof(char));
    std::cout << "Testing reset" << std::endl;
    assert(tmpPointer1 == tmpPointer2);
}

void invalidAllocTest() {
    Allocator allocator;
    allocator.makeAllocator(20 * sizeof(char));
    allocator.alloc(10 * sizeof(char));
    char * tmpPointer = allocator.alloc(11 * sizeof(char));
    std::cout << "Testing alloc for invalid allocation request" << std::endl;
    assert(tmpPointer == nullptr);
}

void memTest() {
    Allocator allocator;
    allocator.makeAllocator(20 * sizeof(char));
    allocator.makeAllocator(20 * sizeof(char));
    allocator.makeAllocator(20 * sizeof(char));
}

int main() {
    allocTest();
    resetTest();
    invalidAllocTest();
    memTest();
	
    return 0;
}
