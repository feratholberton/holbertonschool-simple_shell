#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * main - UNIX (only) command line interpreter
 * Return: 0 or exit status
 */

int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t n_chars_read;
	pid_t pid;
	int status;

	while (1)
	{
		printf("Type something human: ");

		n_chars_read = getline(&line, &len, stdin);
		if (n_chars_read == -1)
		{
			if (feof(stdin))
				printf("\n");
			break;
		}

		if (line[n_chars_read - 1] == '\n')
			line[n_chars_read - 1] = '\0';

		if (strlen(line) == 0)
			continue;

		pid = fork();
		if (pid == -1)
		{
			perror("fork failed");
			continue;
		}

		if (pid == 0)
		{
			char *args[2];
			args[0] = line;
			args[1] = NULL;

			if (execve(line, args, NULL) == - 1)
			{
				perror("Execution FAILED");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			waitpid(pid, &status, 0);
		}
	}

	free(line);
	return 0;
}
