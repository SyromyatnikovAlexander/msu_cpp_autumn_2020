#include <iostream>
#include <cstddef>
#include <cassert>
#include "pool.h"

struct A { };

void foo(const A& a) { }

void voidReturnTest() { 
    ThreadPool pool(4);
    auto task1 = pool.exec(foo, A());
    task1.get();
    int a = 5;
    auto task2 = pool.exec([&a] () { a *= 2; });
    task2.get();
    assert(a == 10);
    pool.stop();
}

void functionalityTest() {
    ThreadPool pool(4);
    auto task1 = pool.exec([]() { return 1; });
    auto task2 = pool.exec([]() { return 2; });
    auto task3 = pool.exec([]() { return 3; });
    auto task4 = pool.exec([]() { return 4; });
    auto task5 = pool.exec([]() { return 5; });
    assert(task1.get() == 1 && task2.get() == 2 && task3.get() == 3 && task4.get() == 4 && task5.get() == 5);
    pool.stop();
}

void fewArgsTest() {
    ThreadPool pool(1);
    auto task = pool.exec([](int x, int y) -> int { return x * y; }, 4, 5);
    assert(task.get() == 20);
    pool.stop();
}

int main() {
    std::cout << "Testing functionality with multiple tasks" << std::endl;
    functionalityTest();
    std::cout << "Testing function returning void" << std::endl;
    voidReturnTest();
    std::cout << "Testing function with multiple arguments" << std::endl;
    fewArgsTest();
    
    return 0;
}
