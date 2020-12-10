#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>


template<class T>
class MyAllocator {
    T * pointer = nullptr;
    size_t mySize = 0;
    
public:

    MyAllocator() { }
    T * allocate(size_t size);
    void deallocate(T* ptr, size_t size);
    size_t maxSize() const noexcept;

};


template<class T, class Container>
class MyIterator {
    size_t current = 0;
    Container vec;
    
public:
    MyIterator() { }
    MyIterator(size_t cur, Container& myVec) : current(cur), vec(myVec) { }
    MyIterator(const MyIterator& other) : current(other.current), vec(other.vec) { }
    MyIterator(MyIterator&& other);
    MyIterator& operator=(const MyIterator& other);
    MyIterator& operator=(MyIterator&& other);
    ~MyIterator() { }
    void operator++();
    T operator*() const;
    bool operator==(const MyIterator& other) const;
    bool operator!=(const MyIterator& other) const;

};

template<class T, class Container>
class MyRIterator : public MyIterator<T, Container> {
    size_t current;
    
public:
    MyRIterator(size_t cur, Container& myVec) { }
    MyRIterator(const MyRIterator& other) { }
    MyRIterator(MyRIterator&& other) { }
    void operator++() {
        current--;
    }

};


template<class T, class A = MyAllocator<T>>
class MyVector {
    using value_type = T;
    using Allocator = A;
    
    value_type *myValues =  nullptr;
    size_t mySize = 0;
    size_t myCapacity = 0;
    Allocator myAllocator;
    
    void setCapacity(size_t capacity);
public:

    MyVector() { };
    MyVector(size_t count);
    MyVector(size_t count, const value_type& defaultValue);
    MyVector(const MyVector& other);
    MyVector(MyVector&& other);
    ~MyVector();
    MyVector& operator=(const MyVector& other);
    MyVector& operator=(MyVector&& other);
    bool operator==(const MyVector& other) const;
    bool operator!=(const MyVector& other) const;
    size_t capacity() const noexcept;
    size_t size() const noexcept;
    bool empty() const noexcept;
    void clear();
    void resize(size_t count);
    void push_back(const value_type& value);
    void push_back(value_type&& value);
    value_type pop_back();
    void reserve(size_t capacity);
    template<class... ArgsT>
    void emplace_back(ArgsT&&... args);
    value_type operator[](size_t pos) const;
    value_type& operator[](size_t pos);
    MyIterator<T, MyVector> begin();
    MyIterator<T, MyVector> end();
    MyRIterator<T, MyVector> rbegin();
    MyRIterator<T, MyVector> rend();
};

#include "vector_fromcpp.h"

#endif
