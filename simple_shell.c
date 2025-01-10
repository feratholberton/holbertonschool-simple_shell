#include "simple_shell.h"

/**
 * main - UNIX (only) command line interpreter
 * Return: 0 or exit status
 */

int main()
{
	pid_t pid;
	int status;
	char *line, *command_path;
	char **args;
	size_t count;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("#cisfun$ ");

		line = get_line();
		if (line == NULL)
		{
			free(line);
			break;
		}

		if (strlen(line) == 0)
		{
			free(line);
			continue;
		}

		args = get_tokens(line, &count);
		if (args == NULL)
		{
			free(line);
			continue;
		}

		command_path = get_path(args[0]);
		if (!command_path)
		{
			fprintf(stderr, "%s: Command not found\n", args[0]);
			free(line);
			free_tokens(args, count);
			continue;
		}

		pid = fork();
		if (pid == -1)
		{
			perror("fork failed");
			free(line);
			free_tokens(args, count);
			free(command_path);
			continue;
		}

		if (pid == 0)
		{
			if (execve(command_path, args, NULL) == -1)
			{
				perror("./shell");
				free_tokens(args, count);
				free(line);
				free(command_path);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			waitpid(pid, &status, 0);
		}

		free(line);
		free_tokens(args, count);
		free(command_path);
	}

	return (0);
}
