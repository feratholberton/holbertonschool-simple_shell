# C - Simple Shell

## Description:
 
This function implements a basic command line shell. It repeatedly:
 
1. Displays a prompt (`#cisfun$`) if the input is from a terminal.
2. Gets the **line** from the user input.
3. Gets **tokens** from the **line**.
4. Resolves the command path using the `PATH` environment variable.
5. Creates a child process using `fork()` to execute the command with `execve`.
6. Waits for the child process to finish execution.
 
 ## Features:
 - Executes commands with or without arguments.
 - Supports relative and absolute paths.
 - Handles empty input and invalid commands gracefully.
 - Runs interactively (with a prompt) or non-interactively (from a script or pipe).

 Edge cases:
 - Exits on `Ctrl+D` (end-of-file condition).
 - Prints "Command not found" for non-existent commands.
 - Handles memory allocation errors during tokenization or path resolution.
 
 **Return**: Always 0 on successful shell exit.

## How it works

### Infinite loop
```c
while (1)
```
- Runs the shell in an infinite loop, waiting for user input.
- Exits the loop on Ctrl+D (handled by get_line returning NULL).

### Prompt Display
```c
if (isatty(STDIN_FILENO))
	printf("#cisfun$ ");
```
- Displays the prompt only when the shell is running interactively.

### Input Handling
```c
line = get_line();

if (line == NULL)
	break;

if (strlen(line) == 0)
{
	free(line);
	continue;
}
```
- Reads a line of input using get_line.
- Exits the shell if Ctrl+D is pressed (get_line returns NULL).
- Ignores empty input (e.g., pressing Enter) by freeing the line and continuing the loop.

### Get tokens
```c
args = get_tokens(line, &count);

if (args == NULL)
{
	free(line);
	continue;
}
```
- Splits the input line into tokens (command and arguments).
- If tokenization fails, frees the input line and restarts the loop.

### Get PATH
```c
command_path = get_path(args[0]);

if (!command_path)
{
	fprintf(stderr, "%s: Command not found\n", args[0]);
	free(line);
	free_tokens(args, count);
	continue;
}
```
- Resolves the full path of the command using get_path.
- If the command is not found, prints an error and skips execution.

### Process Creation
```c
pid = fork();

if (pid == -1)
{
	perror("fork failed");
	free(line);
	free_tokens(args, count);
	free(command_path);
	continue;
}
```
- Uses fork() to create a new process.
- Prints an error and skips execution if fork fails.

### Child Process Execution
```c
if (pid == 0)
{
	if (execve(command_path, args, NULL) == -1)
	{
		perror("./shell");
		free_tokens(args, count);
		free(line);
		free(command_path);
		exit(EXIT_FAILURE);
	}
}
```
- The child process (pid == 0) uses execve to execute the resolved command.
- Frees allocated memory and exits on failure.

### Parent Process Handling
```c
else
{
    waitpid(pid, &status, 0);
}
```
- The parent process waits for the child to complete before continuing.

### Memory Cleanup
```c
free(line);
free_tokens(args, count);
free(command_path);
```
- Ensures all dynamically allocated memory is freed after each command execution.
