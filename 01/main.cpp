#include <cstddef>
#include "allocator.h"

void Allocator::makeAllocator(size_t maxSize) {
    if(init != nullptr) {
        delete[] init;
    }
    mySize = maxSize;
    init = new char[mySize];
    offset = init;
}

char* Allocator::alloc(size_t size) {
    if(size > mySize - (offset - init)) {
        return nullptr;
    }
    offset += size;
    return offset - size;
}
    
void Allocator::reset() {
    offset = init;
}

