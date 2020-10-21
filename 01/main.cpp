#include <new>
#include "allocator.h"


void Allocator::makeAllocator(std::size_t maxSize) {
    if(init != nullptr) {
        delete[] init;
    }
    mySize = maxSize;
    //maybe check size for negat cases
    init = new char[mySize];
    offset = init;
}


char* Allocator::alloc(std::size_t size) {
    if(size > mySize - (offset - init)) {
        return nullptr;
    }
    offset += size;
    return offset - size;
}


void Allocator::reset() {
    offset = init;
}
