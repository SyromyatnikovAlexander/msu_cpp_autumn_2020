#include <iostream>
#include <cstddef>
#include <exception>
#include <stdexcept>
#include "matrix.h"
#include <cassert>


void dimensionsTest() {
    Matrix m(3, 4);
    assert(m.getRows() == 3);
    assert(m.getColumns() == 4);
}

void multTest() {
    int init[] = {1, 2, 3, 4, 5, 6};
    int initx2[] = {2, 4, 6, 8, 10, 12};
    Matrix m(2, 3, init);
    Matrix correct(2, 3, initx2);
    m *= 2;
    assert(m == correct);
}

void elementTest() {
    int init[] = {1, 2, 3, 4, 5, 6};
    int init2[] = {1, 2, 3, 4, -10, 6};
    Matrix m(2, 3, init);
    Matrix correct(2, 3, init2);
    m[1][1] = -10;
    assert(m == correct);
}

void addTest() {
    int init[] = {1, 2, 3, 4, 5, 6};
    int init2[] = {1, 1, 1, -4, 5, 10};
    int res[] = {2, 3, 4, 0, 10, 16};
    Matrix m(2, 3, init);
    Matrix m1(2, 3, init2);
    Matrix correct(2, 3, res);
    assert((m + m1) == correct);
}

void outOfRangeTest() {
    int init[] = {1, 2, 3, 4, 5, 6};
    Matrix m(2, 3, init);
    std::string exc;
    try {
        m[2][1] = 10;
    }
    catch(std::exception& err) {
        exc = err.what();
    }
    assert(exc == "Index out of range");
    exc = "";
    Matrix m1(3, 2, init);
    try{
        m1[1][2] = 10;
    }
    catch(std::exception& err) {
        exc = err.what();
    }
    assert(exc == "Index out of range");
}

void IncompatibleTest() {
    int init[] = {1, 2, 3, 4, 5, 6};
    int init2[] = {1, 1, 1, -4, 5, 10};
    Matrix m(2, 3, init);
    Matrix m1(3, 2, init2);
    std::string exc;
    try {
        m = m + m1;
    }
    catch(std::exception& err) {
        exc = err.what();
    }
    assert(exc == "Incompatible dimensions");
}


int main() {
    std::cout << "Testing dimensions initialization" << std::endl;
    dimensionsTest();
    std::cout << "Testing multiplication" << std::endl;
    multTest();
    std::cout << "Testing element call" << std::endl;
    elementTest();
    std::cout << "Testing indexes out of range" << std::endl;
    outOfRangeTest();
    std::cout << "Testing addition" << std::endl;
    addTest();
    std::cout << "Testing incorrect addition" << std::endl;
    IncompatibleTest();
    return 0;
}
