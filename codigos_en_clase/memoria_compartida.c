#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int main() {
    key_t key = 12345;  // Clave para la memoria compartida
    double *ap;          // Puntero a la memoria compartida
    int shmId;           // Identificador de la memoria compartida
    int status;
    pid_t pid;
    // Crear una memoria compartida (tamaño de un double)
    shmId = shmget(key, sizeof(double), 0666 | IPC_CREAT); 
    if (shmId <0) {
        perror("error al crear el shm");
        exit(-1);
    }

    // Asociar la memoria compartida al espacio de direcciones del proceso
    ap = shmat(shmId, 0, 0);
    pid = fork();
    if (pid<0){
        perror("error al crear el pip");
        exit(-1);
    }
    if (pid ==0) {
        *ap=3.1415926535;

        
    }else{
        wait(&status);
    }


    
    return 0;
}
