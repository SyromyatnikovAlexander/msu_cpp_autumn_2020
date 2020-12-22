#ifndef POOL_FROMCPP_H
#define POOL_FROMCPP_H

template<class T>
struct helper {
    template<class F, class... Args>
    void help(std::shared_ptr<std::promise<T>> prPointer, F& f, Args&... args) {
        prPointer->set_value(f(args...));
    }
};

template<>
struct helper<void> {
    template<class F, class... Args>
    void help(std::shared_ptr<std::promise<void>> prPointer, F& f, Args&... args) {
        f(args...);
        prPointer->set_value();
    }
};

ThreadPool::ThreadPool(size_t poolSize) {
    size = poolSize;
    
    for (size_t i = 0; i < size; ++i) {
        threads.emplace_back(std::thread([this, i](){
            while(!shutdown) {
                std::unique_lock<std::mutex> lock(m);
                if (tasks.empty()) {
                    if(shutdown) {
                        busy.notify_all();
                        return;
                    }
                    busy.wait(lock);
                } else {
                    std::function<void ()> task = tasks.front();
                    tasks.pop();
                    lock.unlock();
                    
                    task();
                }
            }
        }));
    }
}

ThreadPool::~ThreadPool() {    
    for(auto&& th : threads) {
        th.join();
    }
}

void ThreadPool::stop() {
    std::unique_lock<std::mutex> lock(m);
    shutdown = true;
    busy.notify_all();
}

template <class Func, class... Args>
auto ThreadPool::exec(Func&& func, Args... args) -> std::future<decltype(func(args...))> {
    auto prPointer = std::make_shared<std::promise<decltype(func(args...))>>();
    std::future<decltype(func(args...))> future = prPointer->get_future();
    helper<decltype(func(args...))> h;
    
    std::function<void ()> task = [&func, args..., prPointer, &h] () { h.help(prPointer, func, args...); };
    
    std::unique_lock<std::mutex> lock(m);
    tasks.push(task);
    busy.notify_all();
    return future;
}    

#endif
