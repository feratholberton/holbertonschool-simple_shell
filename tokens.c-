#include "main.h"

/**
 * tokenize_line - Splits a line into tokens
 * @line: The input line to tokenize
 * @nread: Length of the input line
 * Return: Array of tokens, or NULL on failure
 */
char **tokenize_line(char *line, ssize_t nread)
{
	char **array;
	char *token;
	int i;

	array = malloc(nread * sizeof(char *));
	if (array == NULL)
	{
		perror("malloc failed");
		return (NULL);
	}

	i = 0;
	token = strtok(line, " ");
	while (token != NULL)
	{
		array[i] = token;
		token = strtok(NULL, " ");
		i++;
	}
	array[i] = NULL;
	return (array);
}
