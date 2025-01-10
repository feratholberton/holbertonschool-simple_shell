#include "simple_shell.h"

/**
 * main - UNIX (only) command line interpreter
 * Return: 0 or exit status
 */
int main()
{
    char *line;
    char **args;

    while (1)
    {
        if (isatty(STDIN_FILENO))
            printf("#cisfun$ ");

        line = get_line();
        if (line == NULL)
            break;

        args = parse_line(line);
        if (args == NULL)
        {
            free(line);
            continue;
        }

        exec_line(args);

        free(line);
        free_tokens(args, 0);
    }

    return (0);
}

