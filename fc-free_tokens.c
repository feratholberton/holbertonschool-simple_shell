#include "simple_shell.h"

/**
 * free_tokens - freed given tokens
 * @tokens: tokens
 * @count: count
 */

void free_tokens(char **tokens, size_t count)
{
	size_t i;

	if (!tokens)
		return;

	for (i = 0; i < count; i++)
	{
		free(tokens[i]);
	}
	free(tokens);
}
