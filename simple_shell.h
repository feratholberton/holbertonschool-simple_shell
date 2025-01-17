#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

extern char **environ;

char *get_line();
char **parse_line(char *line, size_t *count);
void exec_line(char **args);
void free_tokens(char **tokens, size_t count);

#endif
