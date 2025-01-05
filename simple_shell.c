#include "simple_shell.h"

/**
 * main - UNIX (only) command line interpreter
 * Return: 0 or exit status
 */

int main(void)
{
	pid_t pid;
	int status;
	char *line;

	while (1)
	{
		printf("#cisfun$ ");

		line = get_line();
		if (line == NULL)
			break;
		if (strlen(line) == 0)
			continue;

		pid = fork();
		if (pid == -1)
		{
			perror("fork failed");
			free(line);
			continue;
		}

		if (pid == 0)
		{
			char *args[2];

			args[0] = line;
			args[1] = NULL;

			if (execve(line, args, NULL) == -1)
			{
				perror("./shell");
				free(line);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			waitpid(pid, &status, 0);
		}

		free(line);
	}

	return (0);
}
