#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define BUFFER_SIZE 5

/**
 * struct s_shell - shell struct
 * @argv: arguments
 * @env: environement
 * @line: the command line
 * @tokens: command tokens
 * @error_counter: number of the error
 * @status: the status code
 * Description: shell struct
*/

typedef struct s_shell
{
char **argv;
char **env;
char *line;
char **tokens;
int status;
int error_counter;
}   t_shell;

extern char **environ;

int get_last_exit(int action, int status);
char	*ft_strjoin(char *s1, char *s2);
void	*_memcpy(void *dst, const void *src, size_t n);
char	*get_next_line(int fd);
char **ft_split(char *s, char *delimiters);
char	*ft_substr(char *s, int start, int len);
char *_strchr(const char *s, int c);
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
int execute(t_shell *shell);
void free_tokens(char **ptr);
int builtins(t_shell *shell);
int _atoi(char *str);
void cut_string(char *str);
char *_itoa(int num);
int _isnumber(char *str);
void _putchar(int c);
void _putstr(char *str);
void writerr(char **tokens, char **argv, int *error_counter);

#endif
