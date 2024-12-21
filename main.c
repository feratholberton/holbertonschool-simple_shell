#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>


int main()
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    while (1) {
        printf("$ ");
        nread = getline(&line, &len, stdin);
        
        if (nread == -1 || strcmp(line, "exit\n") == 0) {
            break;
        }

        // Eliminar el newline
        line[strcspn(line, "\n")] = 0;
        
        pid_t pid = fork();
        
        if (pid == -1) {
            perror("fork failed");
            continue;
        }
        
        if (pid == 0) { // Proceso hijo
            char *array[64]; // Tamaño máximo razonable para argumentos
            int i = 0;
            
            // Separar la línea en tokens
            char *token = strtok(line, " ");
            while (token != NULL && i < 63) {
                array[i++] = token;
                token = strtok(NULL, " ");
            }
            array[i] = NULL; // Importante: NULL al final para execvp
            
            // Ejecutar el comando
            if (execvp(array[0], array) == -1) {
                perror("execvp failed");
                exit(EXIT_FAILURE);
            }
        } else { // Proceso padre
            int status;
            waitpid(pid, &status, 0);
        }
    }

    free(line);
    return 0;
}
