#include "main.h"

/**
 * execute_command - Executes a command with its arguments
 * @array: Array of command and arguments
 * Return: void
 */

void execute_command(char **array)
{
	if (execvp(array[0], array) == -1)
	{
		perror("execvp failed");
		free(array);
		exit(EXIT_FAILURE);
	}
}
