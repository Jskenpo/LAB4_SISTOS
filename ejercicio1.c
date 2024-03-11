#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t resource1_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t resource2_mutex = PTHREAD_MUTEX_INITIALIZER;

void *process1(void *arg) {
    while (1) {
        printf("Process 1 is attempting to acquire Resource 1...\n");
        pthread_mutex_lock(&resource1_mutex);
        printf("Process 1 has acquired Resource 1.\n");

        // Introduce un pequeño retraso para simular el procesamiento
        usleep(1000);

        printf("Process 1 is attempting to acquire Resource 2...\n");
        pthread_mutex_lock(&resource2_mutex);
        printf("Process 1 has acquired Resource 2.\n");

        // Realizar el trabajo con los recursos aquí

        pthread_mutex_unlock(&resource2_mutex);
        printf("Process 1 has released Resource 2.\n");

        pthread_mutex_unlock(&resource1_mutex);
        printf("Process 1 has released Resource 1.\n");
    }
    return NULL;
}

void *process2(void *arg) {
    while (1) {
        printf("Process 2 is attempting to acquire Resource 2...\n");
        pthread_mutex_lock(&resource2_mutex);
        printf("Process 2 has acquired Resource 2.\n");

        // Introduce un pequeño retraso para simular el procesamiento
        usleep(1000);

        printf("Process 2 is attempting to acquire Resource 1...\n");
        pthread_mutex_lock(&resource1_mutex);
        printf("Process 2 has acquired Resource 1.\n");

        // Realizar el trabajo con los recursos aquí

        pthread_mutex_unlock(&resource1_mutex);
        printf("Process 2 has released Resource 1.\n");

        pthread_mutex_unlock(&resource2_mutex);
        printf("Process 2 has released Resource 2.\n");
    }
    return NULL;
}

int main() {
    pthread_t tid1, tid2;

    // Crea los hilos para los procesos
    pthread_create(&tid1, NULL, process1, NULL);
    pthread_create(&tid2, NULL, process2, NULL);

    // Espera a que los hilos terminen (esto nunca debería ocurrir debido al bucle infinito)
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    return 0;
}

