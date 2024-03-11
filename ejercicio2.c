#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_FILOSOFOS 5
#define IZQUIERDA (id_filosofo + NUM_FILOSOFOS - 1) % NUM_FILOSOFOS
#define DERECHA (id_filosofo + 1) % NUM_FILOSOFOS

pthread_t filosofos[NUM_FILOSOFOS];
sem_t tenedores[NUM_FILOSOFOS];
sem_t mutex;

void *filosofo(void *arg) {
    int id_filosofo = *((int *)arg);
    while (1) {
        printf("Filósofo %d está pensando.\n", id_filosofo);

        // Intenta adquirir los tenedores
        sem_wait(&mutex);
        sem_wait(&tenedores[IZQUIERDA]);
        sem_wait(&tenedores[DERECHA]);
        sem_post(&mutex);

        printf("Filósofo %d está comiendo.\n", id_filosofo);
        usleep(1000000); // Simula el tiempo que lleva comer

        // Libera los tenedores
        sem_post(&tenedores[IZQUIERDA]);
        sem_post(&tenedores[DERECHA]);
    }
    return NULL;
}

int main() {
    int i, id_filosofo[NUM_FILOSOFOS];

    // Inicializa los semáforos
    sem_init(&mutex, 0, 1);
    for (i = 0; i < NUM_FILOSOFOS; i++) {
        sem_init(&tenedores[i], 0, 1);
    }

    // Crea los hilos para cada filósofo
    for (i = 0; i < NUM_FILOSOFOS; i++) {
        id_filosofo[i] = i;
        pthread_create(&filosofos[i], NULL, filosofo, &id_filosofo[i]);
    }

    // Espera a que los hilos terminen (esto nunca debería ocurrir debido al bucle infinito)
    for (i = 0; i < NUM_FILOSOFOS; i++) {
        pthread_join(filosofos[i], NULL);
    }

    // Destruye los semáforos
    sem_destroy(&mutex);
    for (i = 0; i < NUM_FILOSOFOS; i++) {
        sem_destroy(&tenedores[i]);
    }

    return 0;
}

