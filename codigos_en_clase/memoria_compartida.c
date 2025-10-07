#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    key_t key = 12345; // Clave para la memoria compartida
    double *ap;        // Puntero a la memoria compartida
    int shmId;         // Identificador de la memoria compartida
    int status;
    pid_t pid;
    // Crear una memoria compartida (tamaño de un double)
    shmId = shmget(key, sizeof(double), 0666 | IPC_CREAT);
    if (shmId < 0)
    {
        perror("error al crear el shm");
        exit(-1);
    }

    // Asociar la memoria compartida al espacio de direcciones del proceso
    ap = shmat(shmId, NULL, 0);
    if (ap == (void *) -1) {
        perror("error al adjuntar shm");
        /* Intentar eliminar la memoria compartida antes de salir */
        shmctl(shmId, IPC_RMID, NULL);
        exit(EXIT_FAILURE);
    }
    pid = fork();
    if (pid < 0)
    {
        perror("error al crear el pip");
        exit(-1);
    }
    if (pid == 0)
    {
        *ap = 3.1415926535;
        /* Desasociarse antes de terminar el hijo */
        shmdt(ap);
    }
    else
    {
        wait(&status);
        /* Leer y mostrar el valor escrito por el hijo */
        printf("Padre: valor en memoria compartida = %f\n", *ap);

        /* Desasociar y eliminar la memoria compartida */
        shmdt(ap);
        shmctl(shmId, IPC_RMID, NULL);
    }

    return 0;
}
