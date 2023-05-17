#include "shell.h"

/**
 * free_words - free the array of words
 * @words: The array to free
 * Return: void
 */

void free_words(char **words)
{
	int i = 0;

	while (words[i])
	{
		free(words[i]);
		i++;
	}
	free(words);
}

/**
 * remove_new_line - removes the new line in the end
 *
 * @str: the string in hand
 * Return: void
 */

void remove_new_line(char **str)
{
	int last = _strlen(*str) - 1;

	if ((*str)[last] == '\n')
		(*str)[last] = '\0';
}



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
	int i = 0;
	char *full_path;
	char **dirs;
	char *base;

	dirs = split(path, ':');
	if (!dirs)
		return (NULL);
	while (dirs[i])
	{
		base = join(dirs[i], "/");
		full_path = join(base, file);
		if (access(full_path, F_OK) == 0)
			return (full_path);
		i++;
	}
	return (NULL);
}
