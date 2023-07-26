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
 * void
 */

void print_env(void)
{
	int i = 0;
	char **env = environ;

	while (env[i])
	{
		_putstr(env[i]);
		_putchar('\n');
		i++;
	}
}

/**
 * handle_exit - handles the exit builtin
 * @shell: the shell variable
 * Return: 0 on success, 1 on failure
 */

int handle_exit(t_shell *shell)
{
	if (!shell->tokens[1])
	{
		free_tokens(shell->tokens);
		free(shell->line);
		exit(shell->status);
	}
	if (_isnumber(shell->tokens[1]))
	{
		shell->status = _atoi(shell->tokens[1]);
		free_tokens(shell->tokens);
		free(shell->line);
		exit(shell->status);
	}
	else
	{
		char *err_str;

		shell->error_counter++;
		err_str = _itoa(shell->error_counter);
		write(STDERR_FILENO, shell->argv[0], _strlen(shell->argv[0]));
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, err_str, _strlen(err_str));
		write(STDERR_FILENO, ": ", 2);
		free(err_str);
		write(STDERR_FILENO, "exit: ", 6);
		write(STDERR_FILENO, "Illegal number: ", 16);
		write(STDERR_FILENO, shell->tokens[1], _strlen(shell->tokens[1]));
		write(STDERR_FILENO, "\n", 1);
		shell->status = 2;
		return (2);
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

	if (_strncmp(shell->tokens[0], "echo", 4) == 0
		&& _strncmp(shell->tokens[0], "$?", 2))
	{
		printf("%d\n", shell->status);
		return (0);
	}
	if (_strncmp(shell->tokens[0], "exit", 4) == 0)
	{
		handle_exit(shell);
		return (0);
	}
	if (_strncmp(shell->tokens[0], "env", 3) == 0)
	{
		print_env();
		return (0);
	}

	return (1);
}
