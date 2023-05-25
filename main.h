#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

extern char **environ;

char **tokenize(char *line);
int get_last_exit(int action, int status);
int _strlen(char *str);
int _strncmp(char *str1, char *str2, int n);
char *_strdup(char *str);
void sigintHandler(int sig_num);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
char *_getenv(char *name);
char *make_path(char *path, char *cmd);
char *get_path(char *cmd);
int execute(char **tokens, char **argv, char **env, char *line);
void ffree(char **ptr);
int builtins(char **tokens, char **argv, char **env, char *line);
int _atoi(char *str);
void cut_string(char *str);
char *_itoa(int num);
void print_val(int val);
int _isnumber(char *str);

#endif /* _MAIN_H_ */
