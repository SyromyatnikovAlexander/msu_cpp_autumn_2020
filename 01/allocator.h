#ifndef H_ALLOCATOR
#define H_ALLOCATOR

class Allocator {
private:
    char* init;
    char* offset;
    size_t mySize;

public:
    Allocator() {
        init = nullptr;
        offset = nullptr;
        mySize = 0;
    }
    void makeAllocator(size_t maxSize);
    char* alloc(size_t size);
    void reset();
    ~Allocator() {
        delete[] init;
    }
};

#endif
