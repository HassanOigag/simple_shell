#include "shell.h"

/**
 * writerr - writes an error message to stderr
 * @tokens: array of tokens
 * @argv: array of arguments
 * Return: void
 */

void writerr(char **tokens, char **argv)
{
	write(STDERR_FILENO, argv[0], _strlen(argv[0]));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, tokens[0], _strlen(tokens[0]));
	write(STDERR_FILENO, ": not found\n", 12);
}

/**
 * execute - executes a command
 * @tokens: array of tokens
 * @argv: array of arguments
 * @env: array of environment variables
 * @line: line from getline
 * Return: 0 on success, 1 on failure
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

int execute(char **tokens, char **argv, char **env, char *line)
{
	pid_t child_pid = 0;
	int status = 0;
	char *full_path;
	char *path = _getenv("PATH");

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
	else if (tokens[0][0] == '.' && tokens[0][1] == '/'
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
	if (!full_path || access(full_path, X_OK) != 0)
	{
		writerr(tokens, argv);
		if (full_path)
			free(full_path);
		get_last_exit(1, 127);
		return (1);
	}
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
		get_last_exit(1, 0);
	}
	return (status);
}

/**
 * get_last_exit - gets the last exit code
 * @action: 0 to get, 1 to set
 * @status: exit code
 * Return: last exit code
 */

int get_last_exit(int action, int status)
{
	static int last_exit;

	if (action == 1)
		last_exit = status;
	return (last_exit);
}
