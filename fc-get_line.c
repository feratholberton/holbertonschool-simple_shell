#include "simple_shell.h"

/**
 * get_line - Gets the line from the standard intput
 * Return: 0 or exit status
 */
char *remove_new_line(char *line, ssize_t chars_read);
char *remove_tabs(char *line);
char *remove_multiple_spaces(char *line);

char *get_line()
{
	char *line = NULL;
	size_t length = 0;
	ssize_t chars_read;

	chars_read = getline(&line, &length, stdin);

	if (chars_read == -1)
	{
		free(line);
		return NULL;
	}

	if (strcmp(line, "exit\n") == 0)
        {
		free(line);
		return (NULL);
        }

	line = remove_new_line(line, chars_read);

	line = remove_tabs(line);

	line = remove_multiple_spaces(line);

	return line;
}

char *remove_new_line(char *line, ssize_t chars_read)
{
	if (line[chars_read - 1] == '\n')
	 	line[chars_read - 1] = '\0';

	return line;
}

char *remove_tabs(char *line)
{
	size_t i;

	for (i = 0; line[i] != '\0'; i++)
	{
		if (line[i] == '\t')
			line[i] = ' ';
	}

	return line;
}

char *remove_multiple_spaces(char *line)
{
	size_t i, j = 0;
	int inside_word = 0;

	for (i = 0; line[i] != '\0'; i++)
	{
		if (line[i] != ' ')
		{
			line[j++] = line[i];
			inside_word = 1;
		}
		else if (inside_word)
		{
			line[j++] = ' ';
			inside_word = 0;
		}
	}

	if (j > 0 && line[j - 1] == ' ')
		j--;

	line[j] = '\0';
	return line;
}
