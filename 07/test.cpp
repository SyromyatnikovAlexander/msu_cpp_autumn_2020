#include <iostream>
#include <cstddef>
#include "vector.h"
#include <cassert>

void initTest(){
    MyVector<int> vec(5);
    assert(vec.size() == 0);
    assert(vec.empty());
    assert(vec.capacity() == 5);
    MyVector<int> vec2(4, 10);
    vec = vec2;
    assert(vec.size() == 4);
    vec2.clear();
    assert(vec2.empty());
    assert(vec2.capacity() == 4);
    vec2 = std::move(vec);
    assert(vec2.capacity() == 5);
    assert(vec.empty());
    vec2.reserve(10);
    assert(vec2.capacity() == 10);
    vec2.resize(2);
    assert(vec2.size() == 2);
}

void push_backTest() {
    MyVector<int> vec(2);
    int a = 1;
    vec.push_back(a);
    vec.push_back(2);
    vec.push_back(3);
    assert(vec.size() == 3);
    assert(vec[2] == 3);
    assert(vec[0] == 1);
}

void pop_backTest() {
    MyVector<int> vec(3, 1);
    assert(vec.pop_back() == 1);
    assert(vec.size() == 2);
}

void elemTest() {
    MyVector<int> vec(2);
    vec.push_back(4);
    vec[0] = 5;
    assert(vec[0] == 5);
    const MyVector<int> vec2 = vec;
    assert(vec2[0] == 5);
}

void emplace_backTest() {
    MyVector<MyVector<int>> superVec;
    superVec.emplace_back(3, 4);
    MyVector<int> vec = superVec[0];
    assert(vec.size() == 3);
    assert(vec[2] == 4);
}
    
void iteratorTest() {
    MyVector<int> vec(4, 2);
    int i = 0;
    for(MyIterator<int, MyVector<int>> iter = vec.begin(); iter != vec.end(); ++iter) {
        assert(*iter == 2);
        i++;
    }
    assert(i = 3);
    for(MyRIterator<int, MyVector<int>> riter = vec.rbegin(); riter != vec.rend(); ++riter) {
        assert(*riter == 2);
    }
}

void outOfRangeTest() {
    MyVector<int> vec(4, 2);
    try{
        vec[4] *= 2;
    }
    catch(const std::out_of_range& err) {
        assert(err.what() == std::string("Index out of range"));
    }
}
    
    

int main() {
    std::cout << "Testing vector initialization" << std::endl;
    initTest();
    std::cout << "Testing push_back" << std::endl;
    push_backTest();
    std::cout << "Testing pop_back" << std::endl;
    pop_backTest();
    std::cout << "Testing element access" << std::endl;
    elemTest();
    std::cout << "Testing emplace_back" << std::endl;
    emplace_backTest();
    std::cout << "Testing iterators" << std::endl;
    iteratorTest();
    std::cout << "Testing index out of range" << std::endl;
    outOfRangeTest(); 
    return 0;
}
