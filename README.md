# C - Simple Shell

## Overview:

The Simple Shell is a custom implementation of a Unix shell. It serves as a command-line interpreter that reads user input, parses it, and executes commands. This shell mimics the behavior of /bin/sh, including support for handling commands in interactive and non-interactive modes.


## Features:
- Interactive Mode: The shell displays a prompt (#cisfun$) and waits for user input.
- Non-Interactive Mode: Commands are executed from a pipeline or file input.
- Command Execution: Executes commands found in the PATH environment variable or absolute/relative paths.
- Whitespace Handling: Cleans multiple spaces and tabs in input commands.
- Error Messages: Displays errors consistent with /bin/sh.
- Exit Command: Users can terminate the shell with the exit command.

## How it works

The shell operates in a loop following these three main steps:
### 1 - Read:
- Reads the user's input using the getline() function.
- Cleans unnecessary whitespace and tabs.

### 2 - Parse:
- Tokenizes the input into an array of strings (argv[]), separating the command and arguments.

### 3 - Execute:
- Checks for the command in the PATH or as an absolute/relative path.
- Uses fork() and execve() to create a new process to execute the command.

##Files

| Filename | Description |
| -------- | ------- |
| simple_shell.c | Main program and entry point of the shell. |
| simple_shell.h | Header file with function prototypes and macros. |
| fc-get_line.c | Reads and cleans user input from stdin. |
| fc-parse_line.c | Tokenizes the input line into commands and arguments. |
| fc-exec_line.c | Executes the parsed command using execve(). |
| fc-free_tokens.c | Frees dynamically allocated memory for tokens. |


##Installation and Compilation

Clone the repository:
```
git clone https://github.com/<your-username>/simple_shell.git
cd simple_shell
```

Compile the source code:
```
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```
