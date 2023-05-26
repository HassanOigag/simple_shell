#include "shell.h"

/**
 * make_path - creates a path to a command
 * @path: path to the command
 * @cmd: command to create the path to
 * Return: pointer to the path
 */

char *make_path(char *path, char *cmd)
{
	char *cmd_path = NULL;

	cmd_path = malloc(sizeof(char) * (_strlen(path) + _strlen(cmd) + 2));
	if (cmd_path == NULL)
		return (NULL);
	_strcpy(cmd_path, path);
	_strcat(cmd_path, "/");
	_strcat(cmd_path, cmd);
	return (cmd_path);
}

/**
 * get_path - gets the path of a command
 * @cmd: command to get the path of
 * Return: path of the command
 */

char *get_path(char *cmd)
{
	char *path = NULL, *path_copy = NULL, **tokens = NULL, *cmd_path = NULL;
	struct stat st;
	int i = 0;

	if (stat(cmd, &st) == 0)
		return (cmd);
	if (!cmd)
		return (NULL);
	if (cmd[0] == '/')
	{
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	path = _getenv("PATH");
	path_copy = _strdup(path);	
	tokens = ft_split(path_copy, ":");
	while (*tokens)
	{
		cmd_path = make_path(*tokens, cmd);
		if (stat(cmd_path, &st) == 0)
		{
			free(path_copy);
			i = 0;
			while (tokens[i])
			{
				free(tokens[i]);
				i++;
			}
			free(tokens);
			return (cmd_path);
		}
		free(cmd_path);
		tokens++;
	}
	free(path_copy);
	return (NULL);
}
