#include "main.h"

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
	while (env[i] != NULL)
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
