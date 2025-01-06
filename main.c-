#include "main.h"

/**
 * main - Simple shell implementation
 * Return: 0 on success
 */
int main(void)
{
	char *line = NULL, **array;
	ssize_t nread;
	size_t len = 0;
	pid_t pid;
	int status;

	while (1)
	{
		printf("$ ");
		nread = getline(&line, &len, stdin);
		if (nread == -1 || strcmp(line, "exit\n") == 0)
			break;

		if (nread == 1)
			continue;

		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		pid = fork();
		if (pid == -1)
		{
			perror("fork failed");
			continue;
		}
		if (pid == 0)
		{
			array = tokenize_line(line, nread);
			if (array == NULL)
				exit(EXIT_FAILURE);
			execute_command(array);
			exit(EXIT_SUCCESS);
		}
		else
		{
			waitpid(pid, &status, 0);
		}
	}
	free(line);
	return (0);
}
