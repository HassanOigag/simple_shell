#include "shell.h"

/**
 * _putchar - prints a character
 * @c: the character to print
 * Return: void
 */

void _putchar(int c)
{
	write(STDOUT_FILENO, &c, 1);
}

/**
 * _putstr - prints a string
 * @str: the string to print
 * Return: void
 */

void _putstr(char *str)
{
	int i = 0;

	while (str[i])
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 * print_env - prints the environment variables
 * @env: array of environment variables
 */

void print_env(char **env)
{
	int i = 0;

	while (env[i] != NULL)
	{
		_putstr(env[i]);
		_putchar('\n');
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
 * @shell: the shell struct
 * Return: 0 if builtin, 1 if not
 */

int builtins(t_shell *shell)
{

	if (_strncmp(shell->tokens[0], "exit", 4) == 0)
	{
		handle_exit(shell->tokens, shell->line);
		return (0);
	}
	if (_strncmp(shell->tokens[0], "env", 3) == 0)
	{
		print_env(shell->env);
		return (0);
	}
	return (1);
}
