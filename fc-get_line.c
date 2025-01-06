#include "simple_shell.h"

/**
 * get_line - Gets the line from the standard intput
 * Return: 0 or exit status
 */

char *get_line()
{
        char *line = NULL;
        size_t len = 0;
        ssize_t line_length;

        line_length = getline(&line, &len, stdin);

        if (line_length == -1)
        {
                free(line);
                return (NULL);
        }

        if (line[line_length - 1] == '\n')
                line[line_length - 1] = '\0';

        if (line[0] == '\0')
        {
                free(line);
                return strdup("");
        }

        return (line);
}
