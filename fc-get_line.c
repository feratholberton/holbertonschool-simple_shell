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
	int all_spaces;
	size_t i;

        line_length = getline(&line, &len, stdin);

        if (line_length == -1)
        {
                free(line);
                return (NULL);
        }

        if (line[line_length - 1] == '\n')
                line[line_length - 1] = '\0';

	all_spaces = 1;
	for (i = 0; line[i] != '\0'; i++)
	{
		if (line[i] != ' ')
		{
			all_spaces = 0;
			break;
		}
	}

	if (all_spaces)
	{
                free(line);
                return strdup("");
	}

        return (line);
}
