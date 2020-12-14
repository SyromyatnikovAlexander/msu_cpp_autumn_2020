#ifndef POOL_H
#define POOL_H

#include <cstddef>
#include <vector>
#include <thread>
#include <mutex>
#include <future>
#include <queue>
#include <memory>
#include <functional>



class ThreadPool {
    std::vector<std::thread> threads;
    std::queue<std::function<void ()>> tasks;
    std::condition_variable busy;
    size_t size;
    std::mutex m;
    bool shutdown = false;
    
public:
    explicit ThreadPool(size_t poolSize);
    ~ThreadPool();
    void stop();

    // pass arguments by value
    template <class Func, class... Args>
    auto exec(Func&& func, Args... args) -> std::future<decltype(func(args...))>;
    
};



#include "pool_fromcpp.h"

#endif
