#include "shell.h"

/**
 * pr_to - print tokens
 * @tokens: array
 * @i: index of the token
 * Return: void
 */

void pr_to(char **tokens, int start)
{
	int i, j;

	for (i = start; tokens[i] != NULL; i++)
	{
		for (j = 0; tokens[i][j] != '\0'; j++)
			write(STDOUT_FILENO, &tokens[i][j], 1);
		if (tokens[i + 1] != NULL)
			write(STDOUT_FILENO, " ", 1);
	}
}

/**
 * ha_ec - handles echo
 * @tokens: array of tokens
 * Return: 0 on success, 1 on failure
 */

int ha_ec(char **tokens)
{
	char *value = NULL;
	int i = 1, flag = 0;

	if (tokens[1] == NULL)
	{
		write(STDOUT_FILENO, "\n", 1);
		return (0);
	}
	if (_strncmp(tokens[1], "$$", 2) == 0)
	{
		p_valeur(getpid());
		flag = 1;
		i++;
	}
	if (_strncmp(tokens[1], "$?", 2) == 0)
	{
		p_valeur(gl_Exit(0, 0));
		flag = 1;
		i++;
	}
	if (_strncmp(tokens[1], "$", 1) == 0)
	{
		value = ft_getenv(tokens[1] + 1);
		if (value != NULL)
		{
			write(STDOUT_FILENO, value, _strlen(value));
			write(STDOUT_FILENO, "\n", 1);
		}
		flag = 1;
		i++;
	}
	pr_to(tokens, i);
	if (flag == 0)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}

/**
 * pr_env - prints the environment variables
 * @env: array of environment
 */

void pr_env(char **env)
{
	int i, j;

	for (i = 0; env[i] != NULL; i++)
	{
		for (j = 0; env[i][j] != '\0'; j++)
			write(STDOUT_FILENO, &env[i][j], 1);
		write(STDOUT_FILENO, "\n", 1);
	}
}

/**
 * ha_exi - handles exit
 * @tokens: array of tokens
 * @line: pointer to the line buffer
 * Return: 0 on success, 1 on failure
 */

int ha_exi(char **tokens, char *line)
{
	int status = 0;

	if (tokens[1] == NULL)
	{
		free(tokens);
		free(line);
		exit(gl_Exit(1, status));
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
		exit(gl_Exit(1, status));
	}
	else
	{
		write(STDERR_FILENO, "Illegal number: ", 16);
		write(STDERR_FILENO, tokens[1], _strlen(tokens[1]));
		write(STDERR_FILENO, "\n", 1);
		gl_Exit(1, 2);
		return (1);
	}
	return (0);
}

/**
 * built - checks if a command is a builtin
 * @tokens: array
 * @argv: array of arguments
 * @env: array of environment
 * @line: pointer to the line
 * Return: 0 if builtin, 1 if not
 */

int built(char **tokens, char **argv, char **env, char *line)
{
	(void)argv;

	if (_strncmp(tokens[0], "exit", 4) == 0)
	{
		ha_exi(tokens, line);
		return (0);
	}
	if (_strncmp(tokens[0], "env", 3) == 0)
	{
		pr_env(env);
		return (0);
	}
	if (_strncmp(tokens[0], "echo", 4) == 0)
	{
		ha_ec(tokens);
		return (0);
	}
	return (1);
}
