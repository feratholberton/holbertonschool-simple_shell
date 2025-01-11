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
### -1 Read:
        - Reads the user's input using the getline() function.
        - Cleans unnecessary whitespace and tabs.

### -2 Parse:
        - Tokenizes the input into an array of strings (argv[]), separating the command and arguments.

### -3 Execute:
        - Checks for the command in the PATH or as an absolute/relative path.
        - Uses fork() and execve() to create a new process to execute the command.    
