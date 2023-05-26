#include "shell.h"

/**
 * m_pat - creates a path
 * @path: path
 * @cmd: command
 * Return: pointer
 */

char *m_pat(char *path, char *cmd)
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
 * g_pat - gets the path
 * @cmd: command
 * Return: path
 */

char *g_pat(char *cmd)
{
	char *path = NULL, *path_copy = NULL, **tokens = NULL, *cmd_path = NULL;
	struct stat st;

	if (stat(cmd, &st) == 0)
		return (cmd);
	if (cmd == NULL)
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
		cmd_path = m_pat(*tokens, cmd);
		if (stat(cmd_path, &st) == 0)
		{
			free(path_copy);
			return (cmd_path);
		}
		free(cmd_path);
		tokens++;
	}
	free(path_copy);
	return (NULL);
}
