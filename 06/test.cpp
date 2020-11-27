#include <iostream>
#include <string>
#include <cassert>
#include "format.h"

void tooFewArgs() {
    std::string str;
    try {
        str = format("{0} + {0} = {1}", 1);
    }
    catch(const WrongArguments& err) {
        assert(std::string(err.what()) == "Too few arguments");
    }
}

void incorrectStringTest() {
    std::string str;
    try {
        str = format("{1} + {1} = {1}", 1, "two", true);
    }
    catch(const IncorrectString& err) {
        assert(std::string(err.what()) == "Nowhere to substitute argument");
    }
    try {
        str = format("{0} + {0} = {1}", 1, "two", true, 2);
    }
    catch(const IncorrectString& err) {
        assert(std::string(err.what()) == "Nowhere to substitute argument");
    }
}

void formattingTest() {
    std::string str;
    str = format("{0} + {0} = {1}", 1, "two");
    assert(str == "1 + 1 = two");
}

void noArgsTest() {
    std::string str;
    str = format("a string");
    assert(str == "a string");
}

int main() {
    std::cout << "Testing formatting" << std::endl;
    formattingTest();
    std::cout << "Testing zero arguments" << std::endl;
    noArgsTest();
    std::cout << "Testing incorrect string" << std::endl;
    incorrectStringTest();
    std::cout << "Testing wrong number of arguments" << std::endl;
    tooFewArgs();
    return 0;
}
