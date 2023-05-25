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

extern char **environ;

char **tokenize(char *line);
int gl_Exit(int action, int status);
int _strlen(char *str);
int _strncmp(char *str1, char *str2, int n);
char *_strdup(char *str);
void sigintHandler(int sig_num);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
char *ft_getenv(char *name);
char *m_pat(char *path, char *cmd);
char *g_pat(char *cmd);
int exec(char **tokens, char **argv, char **env, char *line);
void ffree(char **ptr);
void p_free(char *ptr);
int built(char **tokens, char **argv, char **env, char *line);
int _atoi(char *str);
void cut_string(char *str);
char *_itoa(int num);
void p_valeur(int val);
int _isnumber(char *str);
char *get_next_line(int fd);
char *ft_substr(char *s, unsigned int start, size_t len);
char *ft_strjoin(char *s1, char *s2);
int has_new_line(char *s);
int _strspn(char *str, const char *accept);
char *_strpbrk(char *str, const char *accept);
char *my_strtok(char *str, const char *delim);





#endif
