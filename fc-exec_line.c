#include "simple_shell.h"

char *get_path(const char *command);

/**
 * exec_line - Executes a command using execve
 * @args: Array of command and its arguments
 */

void exec_line(char **args)
{
	pid_t pid;
	char *command_path;

	if (!args || !args[0])
		return;

	command_path = get_path(args[0]);
	if (!command_path)
	{
		fprintf(stderr, "%s: Command not found\n", args[0]);
		return;
	}

	pid = fork();
	if (pid == -1)
	{
		free(command_path);
		return;
	}

	if (pid == 0)
	{
		if (execve(command_path, args, NULL) == -1)
		{
			perror("./shell");
			free(command_path);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(pid, NULL, 0);
	}

	free(command_path);
}

/**
 * get_path - Finds the full path of a command
 * @command: The command to locate
 * Return: Full path to the command, or NULL if not found
 */

char *get_path(const char *command)
{
	char *path_env = NULL, *path_copy, *dir, *full_path;
	size_t length;
	int i;

	if (!command)
		return (NULL);

	/* Check for absolute or relative paths */
	if (strchr(command, '/') || strchr(command, '.'))
	{
		if (access(command, X_OK) == 0)
			return (strdup(command));
		return (NULL);
	}

	/* Search for PATH variable in the environment */
	for (i = 0; environ[i]; i++)
	{
		if (strncmp(environ[i], "PATH=", 5) == 0)
		{
			path_env = environ[i] + 5;
			break;
		}
	}

	if (!path_env)
		return (NULL);

	/* Tokenize PATH and search for command */
	path_copy = strdup(path_env);
	if (!path_copy)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir)
	{
		length = strlen(dir) + strlen(command) + 2;
		full_path = malloc(length);
		if (!full_path)
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
