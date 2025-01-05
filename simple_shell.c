#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * main - UNIX (only) command line interpreter
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
		if (feof(stdin))
			printf("\n");

		free(line);
		return (NULL);

	}

	if (line[line_length - 1] == '\n')
		line[line_length - 1] = '\0';

	if (line[0] == '\0')
	{
		free(line);
		return "";
	}

	return (line);
}

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
