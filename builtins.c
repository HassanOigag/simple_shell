#include "shell.h"

/**
 * print_tokens - print tokens
 * @tokens: array of tokens
 * @i: index of the token to start printing from
 * Return: void
 */

void print_tokens(char **tokens, int i)
{
	int j = 0;

	while (tokens[i] != NULL)
	{
		j = 0;
		while (tokens[i][j] != '\0')
		{
			write(STDOUT_FILENO, &tokens[i][j], 1);
			j++;
		}
		if (tokens[i + 1] != NULL)
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
}


/**
 * print_env - prints the environment variables
 * @env: array of environment variables
 */

void print_env(char **env)
{
	int i = 0, j = 0;

	while (env[i] != NULL)
	{
		j = 0;
		while (env[i][j] != '\0')
		{
			write(STDOUT_FILENO, &env[i][j], 1);
			j++;
		}
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}

/**
 * handle_exit - handles the exit builtin
 * @tokens: array of tokens
 * @line: pointer to the line buffer
 * Return: 0 on success, 1 on failure
 */

int handle_exit(char **tokens, char *line)
{
	int status = 0;

	if (tokens[1] == NULL)
	{
		free(tokens);
		free(line);
		exit(get_last_exit(1, status));
	}
	if (_isnumber(tokens[1]) == 0)
	{
		status = _atoi(tokens[1]);
		if (status < 0)
		{
			free(tokens);
			free(line);
			exit(256 + status);
		}
		free(tokens);
		free(line);
		exit(get_last_exit(1, status));
	}
	else
	{
		write(STDERR_FILENO, "Illegal number: ", 16);
		write(STDERR_FILENO, tokens[1], _strlen(tokens[1]));
		write(STDERR_FILENO, "\n", 1);
		get_last_exit(1, 2);
		return (1);
	}
	return (0);
}

/**
 * builtins - checks if a command is a builtin
 * @tokens: array of tokens
 * @argv: array of arguments
 * @env: array of environment variables
 * @line: pointer to the line buffer
 * Return: 0 if builtin, 1 if not
 */

int builtins(char **tokens, char **argv, char **env, char *line)
{
	(void)argv;

	if (_strncmp(tokens[0], "exit", 4) == 0)
	{
		handle_exit(tokens, line);
		return (0);
	}
	if (_strncmp(tokens[0], "env", 3) == 0)
	{
		print_env(env);
		return (0);
	}
	return (1);
}
