#ifndef MAIN_H
#define MAIN_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

char **tokenize_line(char *line, ssize_t nread);
void execute_command(char **array);

#endif
