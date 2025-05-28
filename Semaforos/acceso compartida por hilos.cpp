#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <vector>

constexpr int NUM_HILOS = 5;
constexpr int NUM_ITERACIONES = 1000;

int variable_compartida = 0;
sem_t semaforo;

void* funcion_hilo(void* arg) {
    for (int i = 0; i < NUM_ITERACIONES; ++i) {
        sem_wait(&semaforo);
        ++variable_compartida;
        sem_post(&semaforo);
    }
    return nullptr;
}

int main() {
    pthread_t hilos[NUM_HILOS];
    sem_init(&semaforo, 0, 1);

    for (int i = 0; i < NUM_HILOS; ++i) {
        if (pthread_create(&hilos[i], nullptr, funcion_hilo, nullptr) != 0) {
            std::cerr << "Error al crear hilo " << i << std::endl;
            return 1;
        }
    }

    for (int i = 0; i < NUM_HILOS; ++i) {
        pthread_join(hilos[i], nullptr);
    }

    sem_destroy(&semaforo);

    std::cout << "Valor final de la variable compartida: " << variable_compartida << std::endl;
    return 0;
}