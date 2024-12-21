#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>


/**
 * main - Entry of the shell
 * @line: line from stdin
 * @len: len from line
 * Return: 0
 */

int main()
{
        int var, status, lenline = 0;
        char **array;
        char *line = NULL, var1, *var2, *tok;
        ssize_t len = 0, i = 0;
        pid_t pro, parent;

        pro = getpid();
        pro = fork();
        parent = getppid();
        if (pro == 0)
        {
                printf("soy el hijo(funcion fork)");

        }
        else
        {
                wait(&status);
                printf("soy el padre");
        }
        printf("$");
        while (var = getline(&line, &len, stdin) != -1)
        {
                printf("$");
                if (strcmp(line, "exit\n") == 0)
                {
                        if (pro == 0)
                        {
                                kill(pro, parent);
                                exit;

                        }
                        break;
                }
                tok = strtok(line, " ");
                array = malloc(lenline * sizeof(char*));
                if (array == NULL)
                        exit(007);
                array[i] = strdup(tok);
                printf("el primer token es:%s\n", tok);
                i++;
                var2 = line;
                lenline = strlen(var2);
                while (tok != NULL)
                {
                        tok = strtok(NULL, " ");
                        array[i] = tok;
                        printf("next token es:%s\n", array[i]);

                        i++;
                }
        }
        printf("%d\n", var);
        free(line);
        free(tok);
        free(array);
        kill(pro, parent);
        exit;
        return (0);
}
