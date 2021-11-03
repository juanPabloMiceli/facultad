#include <mutex>       // std::mutex
#include <thread>      // std::thread
#include <semaphore.h> // POSIX semaphores
#include <atomic>      // Atomic elements (std C++11)
#include <iostream>
#include <vector>
#include <list>

std::mutex m;

void fn(std::list<int> &l, int *ticketera) { 
    std::lock_guard<std::mutex> lk(m);
    l.push_back((*ticketera)++);
}

int main() {
    // std::array<std::thread, 10> threads
    // std::thread threads[10];
    // std::deque<std::thread> thread;
    std::list<int> l;
    std::vector<std::thread> threads(10);
    
    int ticketera = 0;
    for (std::thread &t : threads) { 
        t = std::thread(fn, std::ref(l), &ticketera);
    }

    for (std::thread &t : threads) { 
        t.join();
    }

    for (int &v : l) { 
        std::cout << v << std::endl;
    }
}


