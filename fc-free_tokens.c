#include "simple_shell.h"

void free_tokens(char **tokens, size_t count)
{
	size_t i;
	for (i = 0; i < count; i++)
	{
		free(tokens[i]);
	}
	free(tokens);
}
