#include <iostream>
#include <cstddef>
#include <string>
#include <cassert>
#include <fstream>
#include "BigInt.h"

void initTest() {
    BigInt num1("123");
    BigInt num2(123);
    assert(num1 == num2);
    BigInt num3(321);
    num1 = num3;
    assert(num1 == 321);
    num2 = std::move(num3);
    assert(num2 == 321);
}

void addTest() {
    BigInt num1(789);
    BigInt num2(123);
    assert(num1 + num2 == 912);
    assert(num1 + 1 == 790);
    assert(1 + num1 == 790);
    assert((num1 += 1) == 790);
    assert((num1 += num2) == 913);
    assert(num2 - num1 == -790);
    assert(-num2 == -123);
    assert(num1 - 1 == 912);
    assert(1 - num1 == -912);
    num1 = BigInt(0);
    assert(num2 + num1 == num2);
    assert(-num1 == num1);
}

void multTest() {
    BigInt num1("789");
    BigInt num2(123);
    assert(num1 * num2 == 123 * 789);
    assert(num1 * (-num2) == -123 * 789);
    num1 *= -1;
    assert(num1 == -789);
    num1 *= num1;
    assert(num1 == 789 * 789);
    num2 = BigInt(0);
    assert(num1 * num2 == 0);
}

void ineqTest() {
    BigInt num1(123);
    BigInt num2 = num1 + 1;
    assert(num1 != num2);
    assert(num1 < num2);
    assert(num1 > -num2);
    assert(num1 >= 123 && num1 <= 123);
    assert(BigInt(0) >= 0);
}

void streamTest() {
    std::fstream file;
    file.open("file.txt", std::ios::out);
    BigInt num("14345547080");
    file << num;
    file.close();
    file.open("file.txt", std::ios::in);
    std::string str;
    std::getline(file, str);
    BigInt num1(str);
    assert(num == num1);
    file.close();
}
    

int main() {
    std::cout << "Testing initialization and copying" << std::endl;
    initTest();
    std::cout << "Testing addition and subtraction" << std::endl;
    addTest();
    std::cout << "Testing multiplication" << std::endl;
    multTest();
    std::cout << "Testing inequalities" << std::endl;
    ineqTest();
    std::cout << "Testing writing into stream" << std::endl;
    streamTest();
    return 0;
}
