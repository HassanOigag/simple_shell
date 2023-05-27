#include "shell.h"

/**
 * join - join two string
 * @s1: string one
 * @s2: string two
 * Return: the joined string
 */

char *join(char *s1, char *s2)
{
	int size = _strlen(s1) + _strlen(s2);
	char *str = malloc(sizeof(char) * (size + 1));
	int i = 0;
	int j = 0;

	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

/**
* is_file_in_path - checks if a file is in path
* @path: the path variable
* @file: the file in hand
* Return: returns the full path of the command else return NULL
*/

char *is_file_in_path(char *path, char *file)
{
	int i = 0;
	char *full_path;
	char **dirs;
	char *base;

	dirs = ft_split(path, ":");
	if (!dirs)
		return (NULL);
	while (dirs[i])
	{
		base = join(dirs[i], "/");
		full_path = join(base, file);
		free(base);
		if (access(full_path, F_OK) == 0)
		{
			free_tokens(dirs);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_tokens(dirs);
	return (NULL);
}

/**
* get_full_path - get the full path of a command
* @tokens: array of the command and args
* Return: the path of the command
*/

char *get_full_path(char **tokens)
{
	char *path = _getenv("PATH");
	char *full_path = NULL;

	if (tokens[0][0] == '.' && tokens[0][1] == '/'
			&& access(tokens[0], F_OK) == 0)
		full_path = _strdup(tokens[0]);
	else if (tokens[0][0] == '.'
			&& tokens[0][1] == '.' && tokens[0][1] == '.'
			&& access(tokens[0], F_OK) == 0)
		full_path = _strdup(tokens[0]);
	else if (tokens[0][0] == '/' && access(tokens[0], F_OK) == 0)
		full_path = _strdup(tokens[0]);
	else
		full_path = is_file_in_path(path, tokens[0]);
	return (full_path);
}

/**
* run_command - runs a command
* @tokens: the command array
* @argv: command line arguments
* @env: enviroment variables
* Return: int
*/

int run_command(char **tokens, char **argv, char **env)
{
	pid_t child_pid = 0;
	int status = 0;
	char *full_path;

	full_path = get_full_path(tokens);
	if (access(full_path, X_OK) == 0)
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			perror(argv[0]);
			free(full_path);
			return (1);
		}
		if (child_pid == 0)
		{
			if (execve(full_path, tokens, env) == -1)
			{
				perror(argv[0]);
				free(full_path);
				exit(127);
			}
		}
		else
			wait(&status);
		free(full_path);
	}
	return (status);
}

/**
* execute - executes the command
* @tokens: command array
* @argv: command line arguments
* @env: env variables
* @line: the line of the command
* Return: int
**/

int execute(char **tokens, char **argv, char **env, char *line)
{
	char *full_path = NULL;
	int status;

	if (builtins(tokens, argv, env, line) == 0)
	{
		get_last_exit(1, 0);
		return (0);
	}
	if (tokens[0][0] == '/' && access(tokens[0], F_OK) != 0)
	{
		writerr(tokens, argv);
		get_last_exit(1, 127);
		return (1);
	}
	full_path = get_full_path(tokens);
	if (!full_path || access(full_path, X_OK) != 0)
	{
		writerr(tokens, argv);
		if (full_path)
			free(full_path);
		get_last_exit(1, 127);
		return (1);
	}
	status = run_command(tokens, argv, env);
	get_last_exit(1, 0);
	return (status);
}


