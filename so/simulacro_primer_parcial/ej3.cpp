#include <mutex>       // std::mutex
#include <thread>      // std::thread
#include <semaphore.h> // POSIX semaphores
#include <atomic>      // Atomic elements (std C++11)
#include <iostream>
#include <vector>
#include <list>

using namespace std::chrono;

void fn_a(int *i, sem_t *producir_a, sem_t *semaforo_main) { 
    while (true) { 
        sem_wait(producir_a);
        (*i)++;
        std::this_thread::sleep_for(seconds{1});
        sem_post(semaforo_main);
    }
}

void fn_b(int *i, sem_t *consume_b, sem_t *semaforo_main) { 
    while (true) { 
        sem_wait(consume_b);
        std::cout << *i << std::endl;
        sem_post(semaforo_main);
    }
}

int main() {
    sem_t producir_a, consume_b, semaforo_main;
    sem_init(&producir_a, 0, 0);
    sem_init(&consume_b, 0, 0);
    sem_init(&semaforo_main, 0, 0);
    
    int i = 0;
    std::thread thread_a = std::thread(fn_a, &i, &producir_a, &semaforo_main);
    std::thread thread_b = std::thread(fn_b, &i, &consume_b, &semaforo_main);

    while (true) { 
        sem_post(&producir_a);
        sem_wait(&semaforo_main);
        sem_post(&consume_b);
        sem_wait(&semaforo_main);
    }

    // nunca termina
    thread_a.join();
    thread_b.join();

}


