#include "simple_shell.h"

/**
 * main - UNIX (only) command line interpreter
 * Return: 0 or exit status
 */

int main(void)
{
	char *line;
	char **args;
	size_t count = 0;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("#cisfun$ ");

		line = get_line();
		if (line == NULL)
			break;

		args = parse_line(line, &count);
		if (args == NULL)
		{
			free(line);
			continue;
		}

		exec_line(args);

		free(line);
		free_tokens(args, count);
	}

	return (0);
}

