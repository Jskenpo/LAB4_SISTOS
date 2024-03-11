#include <stdio.h>
#include <stdbool.h>

// Número de procesos y recursos
#define NUM_PROCESOS 5
#define NUM_RECURSOS 3

// Disponibilidad de recursos
int recursos_disponibles[NUM_RECURSOS] = {10, 5, 7};

// Matrices de asignación y necesidad
int asignacion[NUM_PROCESOS][NUM_RECURSOS] = {
    {0, 1, 0},
    {2, 0, 0},
    {3, 0, 2},
    {2, 1, 1},
    {0, 0, 2}
};

int maximo[NUM_PROCESOS][NUM_RECURSOS] = {
    {7, 5, 3},
    {3, 2, 2},
    {9, 0, 2},
    {2, 2, 2},
    {4, 3, 3}
};

int necesidad[NUM_PROCESOS][NUM_RECURSOS];

// Marcador de procesos terminados
bool terminado[NUM_PROCESOS] = {false};

// Función para verificar si un proceso puede ejecutarse de manera segura
bool chequear_ejecucion_segura(int proceso) {
    // Verifica si los recursos necesarios están disponibles
    for (int i = 0; i < NUM_RECURSOS; i++) {
        if (necesidad[proceso][i] > recursos_disponibles[i])
            return false;
    }
    return true;
}

// Función para ejecutar un proceso de manera segura
void ejecutar_proceso(int proceso) {
    printf("Proceso %d ejecutado con éxito.\n", proceso);
    // Libera los recursos asignados al proceso
    for (int i = 0; i < NUM_RECURSOS; i++) {
        recursos_disponibles[i] += asignacion[proceso][i];
    }
    // Marca el proceso como terminado
    terminado[proceso] = true;
}

// Algoritmo del banquero
void banquero() {
    // Calcula la necesidad de recursos
    for (int i = 0; i < NUM_PROCESOS; i++) {
        for (int j = 0; j < NUM_RECURSOS; j++) {
            necesidad[i][j] = maximo[i][j] - asignacion[i][j];
        }
    }

    // Ejecuta los procesos de manera segura hasta que todos estén terminados
    bool finalizado;
    do {
        finalizado = true;
        for (int i = 0; i < NUM_PROCESOS; i++) {
            if (!terminado[i] && chequear_ejecucion_segura(i)) {
                ejecutar_proceso(i);
                finalizado = false;
            }
        }
    } while (!finalizado);

    // Verifica si todos los procesos han terminado
    for (int i = 0; i < NUM_PROCESOS; i++) {
        if (!terminado[i]) {
            printf("No se puede ejecutar de manera segura debido a la posibilidad de deadlock.\n");
            return;
        }
    }

    printf("Todos los procesos se ejecutaron de manera segura y sin deadlock.\n");
}

int main() {
    banquero();
    return 0;
}
