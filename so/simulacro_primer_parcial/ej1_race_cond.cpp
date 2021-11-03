#include <mutex>       // std::mutex
#include <thread>      // std::thread
#include <semaphore.h> // POSIX semaphores
#include <atomic>      // Atomic elements (std C++11)
#include <iostream>
#include <vector>
#include <functional>

void fn(int &sum) { 
    for (int i = 0; i < 100000; i++) {
        sum += 1;
    }
    
    printf("Hola mi suma es: %d\n", sum);
}

int main() {
    std::vector<std::thread> threads(10);
    // alternativa std::thread threads[10];
    // alternativa std::vector<std::thread *> threads;
    // alternativa std::array<std::thread, 10> threads;
    int suma = 0;
    for (auto &t : threads) { 
        t = std::thread(fn, std::ref(suma)); 
    }

    for (auto &t : threads) { 
        t.join();
    }

    printf("Suma total: %d\n", suma);

    return 0;
}

