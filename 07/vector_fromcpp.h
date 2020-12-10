#ifndef VECTOR_FROMCPP_H
#define VECTOR_FROMCPP_H


template<class T>
T * MyAllocator<T>::allocate(size_t size) {
    T * tmp = new T[size * sizeof(T)];
    mySize = size;
    return tmp;
}

template<class T>
void MyAllocator<T>::deallocate(T* ptr, size_t size) {
    delete[] ptr;
    ptr = nullptr;
    mySize = 0;
}

template<class T>
size_t MyAllocator<T>::maxSize() const noexcept {
    return mySize;
}

template<class T, class A>
void MyVector<T, A>::setCapacity(size_t capacity) {
    if(capacity == myCapacity) {
        return;
    }
    if(capacity == 0) {
        myAllocator.deallocate(myValues, myCapacity);
        myValues = nullptr;
        mySize = 0;
        myCapacity = 0;
        return;
    }
    value_type *tmp = myAllocator.allocate(capacity);
    if(mySize > capacity) {
        mySize = capacity;
    }
    for(size_t i = 0; i < mySize; i++) {
        tmp[i] = std::move(myValues[i]);
    }
    if(myCapacity > 0) {
        myAllocator.deallocate(myValues, myCapacity);
    }
    myValues = tmp;
    myCapacity = capacity;
}

template<class T, class A>
MyVector<T, A>::MyVector(size_t count) {
    if(count == 0) {
        return;
    }
    myCapacity = count;
    mySize = 0;
    myValues = myAllocator.allocate(myCapacity);
}

template<class T, class A>
MyVector<T, A>::MyVector(size_t count, const T& defaultValue) {
    if(count == 0) {
        return;
    }
    myCapacity = count;
    mySize = myCapacity;
    myValues = myAllocator.allocate(myCapacity); 
    for(size_t i = 0; i < mySize; i++) {
        myValues[i] = defaultValue;
    }
}

template<class T, class A>
MyVector<T, A>::MyVector(const MyVector& other) {
    if(other.mySize == 0) {
        return;
    }
    mySize = other.mySize;
    myCapacity = mySize;
    myValues = myAllocator.allocate(myCapacity); 
    for(size_t i = 0; i < mySize; i++) {
        myValues[i] = other.myValues[i];
    }
}

template<class T, class A>
MyVector<T, A>::MyVector(MyVector&& other) {
    if(other.mySize == 0) {
        return;
    }
    myCapacity = other.myCapacity;
    mySize = other.mySize;
    myValues = other.myValues;
    other.mySize = 0;
    other.myCapacity = 0;
    other.myValues = nullptr;
}

template<class T, class A>
MyVector<T, A>::~MyVector() {
    myAllocator.deallocate(myValues, myCapacity);
}

template<class T, class A>
MyVector<T, A>& MyVector<T, A>::operator=(const MyVector& other) {
    if(&other == this) {
        return *this;
    }
    if(other.mySize <= myCapacity) {
        mySize = other.mySize;        
    } else {
        value_type *tmp = myAllocator.allocate(other.mySize);
        if(myCapacity > 0) {
            myAllocator.deallocate(myValues, myCapacity);
        }
        myCapacity = other.mySize;
        mySize = myCapacity;
        myValues = tmp;
    }
    for(size_t i = 0; i < mySize; i++) {
        myValues[i] = other.myValues[i];
    }
    return *this;
}

template<class T, class A>
MyVector<T, A>& MyVector<T, A>::operator=(MyVector&& other) {
    if(&other == this) {
        return *this;
    }
    myCapacity = other.myCapacity;
    mySize = other.mySize;
    if(myCapacity > 0) {
        myAllocator.deallocate(myValues, myCapacity);
    }
    myValues = other.myValues;
    other.mySize = 0;
    other.myCapacity = 0;
    other.myValues = nullptr;
    return *this;
}

template<class T, class A>
bool MyVector<T, A>::operator==(const MyVector& other) const {
    if(mySize != other.mySize) {
        return false;
    }
    for(size_t i = 0; i < mySize; i++) {
        if(myValues[i] != other.myValues[i]) {
            return false;
        }
    }
    return true; 
}

template<class T, class A>
bool MyVector<T, A>::operator!=(const MyVector& other) const {
    return !(*this == other);
}

template<class T, class A>
size_t MyVector<T, A>::capacity() const noexcept {
    return myCapacity;
}

template<class T, class A>
size_t MyVector<T, A>::size() const noexcept {
    return mySize;
}

template<class T, class A>
bool MyVector<T, A>::empty() const noexcept {
    return mySize == 0;
}

template<class T, class A>
void MyVector<T, A>::clear() {
    mySize = 0;
}

template<class T, class A>
void MyVector<T, A>::resize(size_t count) {
    if(count <= myCapacity) {
        mySize = count;
        return;
    }
    setCapacity(count);
    mySize = count;
}

template<class T, class A>
void MyVector<T, A>::push_back(const T& value) {
    if(myCapacity == 0) {
        setCapacity(1);
    }
    if(mySize == myCapacity) {
        setCapacity(myCapacity * 2);
    }
    mySize++;
    myValues[mySize - 1] = value;
}

template<class T, class A>
void MyVector<T, A>::push_back(T&& value) {
    if(myCapacity == 0) {
        setCapacity(1);
    }
    if(mySize == myCapacity) {
        setCapacity(myCapacity * 2);
    }
    mySize++;
    myValues[mySize - 1] = std::move(value);
}

template<class T, class A>
T MyVector<T, A>::pop_back() {
    if(mySize == 0) {
        throw std::out_of_range("No elements in vector");
    }
    mySize--;
    return myValues[mySize];
}

template<class T, class A>
void MyVector<T, A>::reserve(size_t capacity) {
    if(myCapacity < capacity) {
        setCapacity(capacity);
    }
}

template<class T, class A>
template<class... ArgsT>
void MyVector<T, A>::emplace_back(ArgsT&&... args) {
    value_type tmp(args...);
    (*this).push_back(tmp);
}

template<class T, class A>
T MyVector<T, A>::operator[](size_t pos) const {
    if(pos >= mySize) {
        throw std::out_of_range("Index out of range");
    }
    return myValues[pos];
}

template<class T, class A>
T& MyVector<T, A>::operator[](size_t pos) {
    if(pos >= mySize) {
        throw std::out_of_range("Index out of range");
    }
    return myValues[pos];
}

template<class T, class A>
MyIterator<T, MyVector<T, A>> MyVector<T, A>::begin() {
    return MyIterator<T, MyVector>(0, *this);
}

template<class T, class A>
MyIterator<T, MyVector<T, A>> MyVector<T, A>::end() {
    return MyIterator<T, MyVector>(mySize, *this);
}

template<class T, class A>
MyRIterator<T, MyVector<T, A>> MyVector<T, A>::rbegin() {
    return MyRIterator<T, MyVector>(mySize, *this);
}

template<class T, class A>
MyRIterator<T, MyVector<T, A>> MyVector<T, A>::rend() {
    return MyRIterator<T, MyVector>(0, *this);
}

template<class T, class Container>
MyIterator<T, Container>::MyIterator(MyIterator&& other) { 
    current = other.current;
    vec = std::move(other.vec);
}

template<class T, class Container>
void MyIterator<T, Container>::operator++() {
    current++;
}
    
template<class T, class Container>
T MyIterator<T, Container>::operator*() const {
    return vec[current];
}
    
template<class T, class Container>
bool MyIterator<T, Container>::operator==(const MyIterator& other) const {
    return vec == other.vec && current == other.current;
}

template<class T, class Container>
bool MyIterator<T, Container>::operator!=(const MyIterator& other) const {
    return vec != other.vec || current != other.current;
}

template<class T, class Container>
MyIterator<T, Container>& MyIterator<T, Container>::operator=(MyIterator&& other) {
    if(this == &other) {
        return *this;
    }
    current = other.current;
    vec = std::move(other.vec);
    return *this;
}

template<class T, class Container>
MyIterator<T, Container>& MyIterator<T, Container>::operator=(const MyIterator& other) { 
    if(this == &other) {
        return *this;
    }
    current = other.current;
    vec = other.vec;
    return *this;
}

#endif
