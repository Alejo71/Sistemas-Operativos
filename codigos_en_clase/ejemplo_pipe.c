#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int pipefd[2];
    int r;
    pid_t pid;
    long int iteraciones = 10;
    double suma_pares = 0.0;
    double suma_impares = 0.0;
    double suma_recibida = 0.0; // <-- aquí guardaremos lo que manda el hijo

    r = pipe(pipefd);
    if (r < 0) {
        perror("error pipe:");
        exit(1);
    }

    pid = fork();
  
    if (pid == 0) { 
        // Proceso hijo
        close(pipefd[0]);
        for (int i = 0; i <= iteraciones; i++){   
            if (i % 2 == 0){
                suma_pares += i;
            }
        } 
        write(pipefd[1], &suma_pares, sizeof(double));
        printf("Hijo -> suma pares: %.0f\n", suma_pares);
        close(pipefd[1]); 
        exit(0);

    } else { 
        // Proceso padre
        close(pipefd[1]); 
        for (int i = 1; i <= iteraciones; i++){
            if (i % 2 == 1){
                suma_impares += i;
            }
        } 
        read(pipefd[0], &suma_recibida, sizeof(double));// aquí suma_pares se convierte en suma_recibida
        close(pipefd[0]);

        double total = suma_impares + suma_recibida;
        printf("Padre -> suma impares: %.0f\n", suma_impares);
        printf("Suma total: %.0f\n", total);
    }

    return 0;
}


