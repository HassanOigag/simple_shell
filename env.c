#include "shell.h"

/**
 * _getenv - gets an environment variable
 * @name: name of the environment variable
 * Return: pointer to the environment variable
 */

char *_getenv(char *name)
{
	char **env = NULL, *var = NULL, *value = NULL;
	int i = 0, j = 0, len = 0;

	env = environ;
	while (env[i])
	{
		var = env[i];
		len = _strlen(name);
		for (j = 0; j < len; j++)
		{
			if (name[j] != var[j])
				break;
		}
		if (j == len && var[j] == '=')
		{
			value = var + len + 1;
			break;
		}
		i++;
	}
	return (value);
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

/**
 * writerr - writes an error message to stderr
 * @tokens: array of tokens
 * @argv: array of arguments
 * @error_counter: number of the error
 * Return: void
 */

void writerr(char **tokens, char **argv, int *error_counter)
{
	char *err_str;

	(*error_counter)++;
	err_str = _itoa(*error_counter);
	write(STDERR_FILENO, argv[0], _strlen(argv[0]));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, err_str, _strlen(err_str));
	write(STDERR_FILENO, ": ", 2);
	free(err_str);
	write(STDERR_FILENO, tokens[0], _strlen(tokens[0]));
	write(STDERR_FILENO, ": not found\n", 12);
}
