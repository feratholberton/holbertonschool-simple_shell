#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

char *get_line();
char **get_tokens(char *, size_t *);
void free_tokens(char **, size_t);
char *get_path(const char *);

#endif
