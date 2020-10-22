#ifndef H_ALLOCATOR
#define H_ALLOCATOR

class Allocator {
private:
    char* init;
    char* offset;
    std::size_t mySize;

public:
    Allocator() {
        init = nullptr;
        offset = nullptr;
        mySize = 0;
    }
    void makeAllocator(std::size_t maxSize);
    char* alloc(std::size_t size);
    void reset();
    ~Allocator() {
        delete[] init;
    }
};

#endif
