#include <mutex>       // std::mutex
#include <thread>      // std::thread
#include <semaphore.h> // POSIX semaphores
#include <atomic>      // Atomic elements (std C++11)
#include <iostream>
#include <vector>

void fn(std::atomic<int> *i) { 
    for (size_t idx = 0; idx < 100000; idx++) {
        // int j = *i;
        // j = j + 1;
        // i = j;
        i->fetch_add(1);
    }

    std::cout << *i << std::endl;
}

int main() {
    // std::array<std::thread, 10> threads
    // std::thread threads[10];
    // std::deque<std::thread> thread;
    std::vector<std::thread> threads(10);
    std::atomic<int> i{0};

    // for (size_t i = 0; i < threads.size(); i++) 
    //     std::thread &t = threads[i]
    //     t...
    for (std::thread &t : threads) { 
        t = std::thread(fn, &i);
    }

    for (std::thread &t : threads) { 
        t.join();
    }

    std::cout << i << std::endl;
}


