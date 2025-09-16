#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int pipefd[2];       
    char buffer[11];
    int r;
    pid_t pid;

    // Crear el pipe
    r = pipe(pipefd);
    if (r < 0) {
        perror("error pipe");
        exit(1);
    }

    pid = fork();
    if (pid < 0) {
        perror("error fork");
        exit(1);
    }

    if (pid == 0) {   
        close(pipefd[0]);                       
        write(pipefd[1], "Hola mundo", 10);            
        close(pipefd[1]);                       
        exit(0);
    } else {         
        close(pipefd[1]);                       
        r = read(pipefd[0], buffer, 10);         
        buffer[r] = '\0';                       
        printf("%s\n", buffer);                 
        close(pipefd[0]);                       
        exit(0);
    }
}
