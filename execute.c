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
	{
		if (!path)
		{
			free(full_path);
			return (NULL);
		}
		full_path = is_file_in_path(path, tokens[0]);
	}
	return (full_path);
}

/**
* run_command - runs a command
* @shell: the shell variable
* Return: int
*/

int run_command(t_shell *shell)
{
	pid_t child_pid = 0;
	char *full_path;

	full_path = get_full_path(shell->tokens);
	if (access(full_path, X_OK) == 0)
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			perror(shell->argv[0]);
			free(full_path);
			return (1);
		}
		if (child_pid == 0)
		{
			if (execve(full_path, shell->tokens, shell->env) == -1)
			{
				perror(shell->argv[0]);
				free(full_path);
				exit(127);
			}
		}
		else
		{
			wait(&shell->status);
		}
		free(full_path);
	}
	return (shell->status % 255);
}

/**
* execute - executes the command
* @shell: the shell struct
* Return: int
**/


int	execute(t_shell *shell)
{
	char *full_path = NULL;

	if (builtins(shell) == 0)
		return (shell->status);
	if (shell->tokens[0][0] == '/' && access(shell->tokens[0], F_OK) != 0)
	{
		writerr(shell->tokens, shell->argv, &shell->error_counter);
		return (get_last_exit(1, 127));
	}
	full_path = get_full_path(shell->tokens);
	if (!full_path || access(full_path, X_OK) != 0)
	{
		writerr(shell->tokens, shell->argv, &shell->error_counter);
		if (full_path)
			free(full_path);
		return (get_last_exit(1, 127));
	}
	free(full_path);
	shell->status = run_command(shell);
	return (shell->status % 255);
}


