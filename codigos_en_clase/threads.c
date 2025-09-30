#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <math.h>

void *function(void *datos) {
    int val = *(int *)datos;
    printf("Valor recibido en hilo: %d\n", val);
    return NULL;
}

int main() {
    pthread_t hilo;
    int dato = 1234;
    void *retval;

    int r = pthread_create(&hilo, NULL, function, (void *)&dato);
    if (r != 0) {
        fprintf(stderr, "Error creando el hilo\n");
        return 1;
    }

    // Esperar a que el hilo termine
    pthread_join(hilo, &retval);

    return 0;
}

//hacer este ejercicio para 4 o más núcleos
