#include "simple_shell.h"

char **get_tokens(char *line, size_t *count)
{
	char **tokens = NULL;
	char *token;
	size_t capacity = 10;
	char **new_tokens;

	*count = 0;

	tokens = malloc(capacity * sizeof(char *));
	if (!tokens)
	{
		perror("malloc failed");
		return (NULL);
	}

	token = strtok(line, " ");
	while (token != NULL)
	{
		if (*count >= capacity)
		{
			capacity *= 2;
			new_tokens = realloc(tokens, capacity * sizeof(char *));
			if (!new_tokens)
			{
				perror("realloc failed");
				free_tokens(tokens, *count);
				return (NULL);
			}
			tokens = new_tokens;
		}

		tokens[*count] = strdup(token);
		if (!tokens[*count])
		{
			perror("strdup failed");
			free_tokens(tokens, *count);
			return (NULL);
		}

		(*count)++;
		token = strtok(NULL, " ");
	}

	tokens[*count] = NULL;
	return (tokens);
}
