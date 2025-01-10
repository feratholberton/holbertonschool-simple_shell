#include "simple_shell.h"

/**
 * get_line - Reads user input from stdin, removes unnecessary spaces and tabs
 * Return: The cleaned input string or NULL if EOF or error
 */
char *remove_new_line(char *line, ssize_t chars_read);
char *clean_whitespace(char *line);

char *get_line()
{
    char *line = NULL;
    size_t length = 0;
    ssize_t chars_read;

    chars_read = getline(&line, &length, stdin);

    if (chars_read == -1)
    {
        free(line);
        return NULL;
    }

    /* Clean the line by removing newlines, tabs, and extra spaces */
    line = remove_new_line(line, chars_read);
    line = clean_whitespace(line);

    /* Handle special case for 'exit' */
    if (strcmp(line, "exit") == 0)
    {
        free(line);
        return NULL;
    }

    return line;
}

char *remove_new_line(char *line, ssize_t chars_read)
{
    if (line[chars_read - 1] == '\n')
        line[chars_read - 1] = '\0';

    return line;
}

char *clean_whitespace(char *line)
{
    size_t i = 0, j = 0;
    int inside_word = 0;

    while (line[i] != '\0')
    {
        /* Convert tabs to spaces */
        if (line[i] == '\t')
            line[i] = ' ';

        /* Eliminate multiple spaces */
        if (line[i] != ' ')
        {
            line[j++] = line[i];
            inside_word = 1;
        }
        else if (inside_word)
        {
            line[j++] = ' ';
            inside_word = 0;
        }

        i++;
    }

    /* Remove trailing space */
    if (j > 0 && line[j - 1] == ' ')
        j--;

    line[j] = '\0';
    return line;
}
