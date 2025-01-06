#include "simple_shell.h"

char **get_tokens(char *line)
{
	char **tokens = NULL;
	char *token;
	size_t count = 0;
	size_t capacity = 10;
	char **new_tokens;

	tokens = malloc(capacity * sizeof(char *));
	if (tokens == NULL)
	{
		perror("malloc failed");
		return (NULL);
	}

	token = strtok(line, " ");
	while (token != NULL)
	{
		if (count >= capacity)
		{
			capacity *= 2;
			new_tokens = realloc(tokens, capacity * sizeof(char *));
			if (new_tokens == NULL)
			{
				perror("realloc failed");
				free(tokens);
				return (NULL);
			}
			tokens = new_tokens;
		}

		tokens[count] = strdup(token);
		if (tokens[count] == NULL)
		{
			perror("strdup failed");
			free_tokens(tokens, count);
			return (NULL);
		}

		count++;
		token = strtok(NULL, " ");
	}

	tokens[count] = NULL;
	return (tokens);
}
