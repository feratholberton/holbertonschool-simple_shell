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

## Helper functions

### get_line()

Gets a line from the standard input (stdin).
	
This function reads a line of input from the user, trims the newline character (if present), and checks if the input is entirely spaces. It dynamically allocates memory for the line, which must be freed by the caller.

Return:
- A pointer to the dynamically allocated string containing the input line, with the newline character removed.
- If the input is all spaces, an empty string is returned (dynamically allocated).
- If EOF (Ctrl+D) or an error occurs, NULL is returned.

#### Initialization
```c
char *line = NULL;
size_t len = 0;
ssize_t line_length;
int all_spaces;
size_t i;
```
- `line`: A pointer to hold the input string.
- `len`: Holds the allocated size for getline.
- `line_length`: Stores the number of characters read by getline.
- `all_spaces`: Flag to determine if the input contains only spaces.
- `i`: Loop index to iterate through the input string.

#### Read Input
```c
line_length = getline(&line, &len, stdin);
```
- Gets a line from the user input.
- Allocates memory dynamically for line if it’s NULL.

#### Handle EOF or Error
```c
if (line_length == -1)
{
	free(line);
	return (NULL);
}
```
- If getline fails (EOF or error), frees any allocated memory and returns NULL.

#### Remove Trailing Newline
```c
if (line[line_length - 1] == '\n')
	line[line_length - 1] = '\0';
```
- Replaces the trailing newline character with a null terminator (\0), effectively trimming it.

#### Check for All Spaces
```c
all_spaces = 1;
for (i = 0; line[i] != '\0'; i++)
{
	if (line[i] != ' ')
	{
		all_spaces = 0;
		break;
	}
}
```
- Iterates through the string to determine if it consists entirely of spaces.
- If a non-space character is found, sets all_spaces to 0 and exits the loop early.

### Handle All-Spaces Input
```c
if (all_spaces)
{
	free(line);
	return strdup("");
}
```
- If the input contains only spaces, frees the allocated memory for line.
- Returns an empty string (dynamically allocated with strdup) for consistent behavior.

#### Return Valid Input
```c
return (line);
```
- Returns the trimmed input string for further processing.
