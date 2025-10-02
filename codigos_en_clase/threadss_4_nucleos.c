#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

#define NUM_HILOS 4       // Número de hilos

void *function(void *datos) {
    int id = *(int *)datos;

    double resultado = 0.0;

    // Realizar cálculos trigonométricos pesados
    for (int i = 0; i < 10000000; i++) {
        resultado += sin(i * 0.00001) + cos(i * 0.00001);
    }

    printf("Hilo %d terminó con resultado = %.5f\n", id, resultado);
    return NULL;
}

int main() {
    pthread_t hilos[NUM_HILOS];
    int datos[NUM_HILOS];

    // Crear los hilos
    for (int i = 0; i < NUM_HILOS; i++) {
        datos[i] = i + 1; // ID del hilo
        int r = pthread_create(&hilos[i], NULL, function, &datos[i]);
        if (r != 0) {
            fprintf(stderr, "Error creando el hilo %d\n", i);
            return 1;
        }
    }

    // Esperar a que terminen los hilos
    for (int i = 0; i < NUM_HILOS; i++) {
        pthread_join(hilos[i], NULL);
    }

    printf("Todos los hilos han terminado.\n");
    return 0;
}
