#include "simple_shell.h"

extern char **environ;

char *get_path(const char *command)
{
	char *path_env = NULL, *path_copy, *dir, *full_path;
	size_t length;
	int i;

	if (!command)
		return (NULL);

	if (strchr(command, '/'))
	{
		if (access(command, X_OK) == 0)
			return (strdup(command));

		return (NULL);
	}

	for (i = 0; environ[i]; i++)
	{
		if (strncmp(environ[i], "PATH=", 5) == 0)
		{
			path_env = environ[i] + 5;
			break;
		}
	}

	if (!path_env)
		/**path_env = "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin";*/
		return (NULL);

	path_copy = strdup(path_env);
	if (!path_copy)
		return NULL;

	dir = strtok(path_copy, ":");
	while (dir)
	{
		length = strlen(dir) + strlen(command) + 2;
		full_path = malloc(length);
		if(!full_path)
		{
			free(path_copy);
			return (NULL);
		}

		snprintf(full_path, length, "%s/%s", dir, command);
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}

		free(full_path);
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}
