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
