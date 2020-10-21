#include <new>
#include "allocator.h"

/*class Allocator {
private:
    char* init;
    char* offset;
    std::size_t mySize;

public:
    void makeAllocator(std::size_t maxSize) {
        mySize = maxSize;
        //maybe check size for negat cases
        init = new char[mySize];
        offset = init;
    }
    
    char* alloc(std::size_t size) {
        if(size > mySize - (offset - init)) {
            return nullptr;
        }
        offset += size;
        return offset - size;
    }
    
    void reset() {
        offset = init;
    }
    
    ~Allocator() {
        delete[] init;
    }
         
};*/

/*Allocator::Allocator() {
    init = nullptr;
    offset = nullptr;
    mySize = 0;
}*/

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

/*Allocator::~Allocator() {
    delete[] init;
}*/

/*int main() {
    Allocator a;
    a.makeAllocator(40 * sizeof(char));
    a.makeAllocator(40 * sizeof(char));
    a.makeAllocator(40 * sizeof(char));
    a.alloc(20);
    return 0;
}
*/

