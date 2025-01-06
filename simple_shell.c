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
	char **args;

	while (1)
	{
		printf("#cisfun$ ");

		line = get_line();
		if (line == NULL)
			break;

		if (strlen(line) == 0)
			continue;

		args = get_tokens(line);
		if (args == NULL)
		{
			free(line);
			continue;
		}

		pid = fork();
		if (pid == -1)
		{
			perror("fork failed");
			free(line);
			free_tokens(args, 0);
			continue;
		}

		if (pid == 0)
		{
			if (execve(args[0], args, NULL) == -1)
			{
				perror("./shell");
				free(line);
				free_tokens(args, 0);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			waitpid(pid, &status, 0);
		}

		free(line);
		free_tokens(args, 0);
	}

	return (0);
}
