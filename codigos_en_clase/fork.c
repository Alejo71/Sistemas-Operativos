#include <stdio.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <math.h>
//función fork para separar en proceso padre y proceso hijo
int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork falló");
        return 1;
    }

    if (pid == 0) {
        // Código del proceso hijo, porque PID hijo = 0
        printf("Soy el hijo (PID=%d)\n", getpid());
        for (long i = 0; i < 400000000; i++) {
            sin(i); 
        }
        printf("Hijo terminó\n");
    } else {
        // Código del proceso padre
        printf("Soy el padre (PID=%d), mi hijo es %d\n", getpid(), pid);
        for (long i = 0; i < 400000000; i++) {
            cos(i); // Otra función pesada
        }
        printf("Padre terminó\n");
    }
    return 0;
}

