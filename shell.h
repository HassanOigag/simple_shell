#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

/* utils */
int _strlen(char *str);
int _strcmp(char *s1, char *s2);
char *_strdup(char *s);
char **split(char *str);
void free_words(char **words);
char *join(char *s1, char *s2);
char *is_file_in_path(char *file, char **dirs);

#endif