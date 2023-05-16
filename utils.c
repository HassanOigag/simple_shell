#include "shell.h"

/**
 * _strlen - calculates the length of the string
 * @str: the string in hand
 * Return: the size of the string
 */

int _strlen(char *str)
{
	int i = 0;

	while (str[i])
		i++;
	return (i);
}

/**
 * _strcmp - compares two strings
 *
 * @s1: the first string
 * @s2: the second string
 * Return: 0, 1 or -1 (equl, greater, lower)
 */

int _strcmp(char *s1, char *s2)
{
	int i = 0;

	while (s1[i] && s2[i] && (s1[i] == s2[i]))
		i++;
	return (s1[i] - s2[i]);
}

/**
 * _strdup - returns a copy of a string
 *
 * @s: the string to be copied
 * Return: a copy of the string
 */

char *_strdup(char *s)
{
	int size = _strlen(s) + 1;
	char *copy;
	int i = 0;

	copy = malloc(sizeof(char) * size);
	if (!copy)
		return (NULL);
	while (s[i])
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

/**
 * join - join two string together
 *
 * @s1: the first string
 * @s2: the second string
 * Return: char* the the combined string
 */

char *join(char *s1, char *s2)
{
	int size = strlen(s1) + strlen(s2);
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
	struct stat st;
	int i = 0;
	char *full_path;
	char **dirs;
	char *base;

	dirs = split(path, ":");
	if (!dirs)
		return (NULL);
	while (dirs[i])
	{
		base = join(dirs[i], "/");
		full_path = join(base, file);
		if (stat(full_path, &st) == 0)
			return (full_path);
		i++;
	}
	return (NULL);
}
