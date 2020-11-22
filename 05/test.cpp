#include <iostream>
#include <sstream>
#include <cstddef>
#include <cstdint>
#include <cassert>
#include "serializer.h"

struct Data {
    uint64_t a;
    bool b;
    uint64_t c;
    
    template<class Serializer>
    Error serialize(Serializer& serializer) {
        return serializer(a, b, c);
    }
    
    template<class Deserializer>
    Error deserialize(Deserializer& deserializer) {
        return deserializer(a, b, c);
    }
};

void functionalityTest() {
    Data x {1, true, 2};
    Data y {0, false, 0};
    std::stringstream stream;
    
    Serializer serializer(stream);
    serializer.save(x);
    
    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);
    
    assert(err == Error::NoError);
    assert(x.a == y.a);
    assert(x.b == y.b);
    assert(x.c == y.c);
}

void serializingTest() {
    Data x {123, true, 2};
    std::stringstream stream;
    
    Serializer serializer(stream);
    serializer.save(x);
    std::string res;
    res = stream.str();
    assert(res == "123 true 2");
}

void corruptedTest() {
    Data y {1, true, 2};
    std::stringstream stream;
    stream << "23 false abc";
    Deserializer deserializer(stream);
    Error err = deserializer.load(y);
    assert(err == Error::CorruptedArchive);
    
    stream.str("");
    err = deserializer.load(y);
    assert(err == Error::CorruptedArchive);
}
    

int main() {
    std::cout << "Testing functionality" << std::endl;
    functionalityTest(); 
    std::cout << "Testing resulting string" << std::endl;
    serializingTest();
    std::cout << "Testing Corrupted Archive" << std::endl;
    corruptedTest();   
    return 0;
}
