#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 5
#endif

/* utils */
int _strlen(char *str);
int _strcmp(char *s1, char *s2);
char *_strdup(char *s);
char **ft_split(char *str, char c);
void free_words(char **words);
char *join(char *s1, char *s2);
void remove_new_line(char **line);
char *is_file_in_path(char *path, char *file);
char *get_next_line(int fd);
void *ft_memcpy(void *dst, const void *src, size_t n);
char *ft_strjoin(char *s1, char *s2);
char *ft_substr(char *s, unsigned int start, size_t len);
int has_new_line(char *s);
char *ft_strtrim(char *s1, char const *set);
void ft_putstr(char *s);

#endif
