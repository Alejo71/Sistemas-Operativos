#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int pipefd[2];
    int r;
    pid_t pid;
    long int iteraciones = 10000000;
    double pi = 0.0;
    double pi_rec;

    r = pipe(pipefd);
    if (r < 0) {
        perror("error pipe:");
        exit(1);
    }

    pid = fork();
  

    if (pid == 0) { 
        //Proceso hijo
        close(pipefd[0]);
        for (int i = 0; i < iteraciones; i++){
            pi += 4.0/(4.0*i+1.0);
        } 
        write(pipefd[1],&pi, sizeof(double));
        close(pipefd[1]); 
        exit(0);
    } else { 
        //Proceso padre
        close(pipefd[1]); 
        for (int i = 1; i < iteraciones; i++){
            pi -= 4.0/(4.0*i-1.0);
        } 
        read(pipefd[0], &pi_rec, sizeof(double));
        pi += pi_rec;
        printf("pi: %.10f\n", pi);
        close(pipefd[0]);
    }

    return 0;
}
