#include "shell.h"

/**
 * count_words - counts the words in a string
 * @str: the string in hand
 * Return: int
 */

static int count_words(char *str)
{
	int words = 0;
	char *word;
	char *copy = _strdup(str);
	word = strtok(copy, " ");
	while (word)
	{
		words++;
		word = strtok(NULL, " ");
	}
	free(copy);
	return (words);
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
 * free_words - free the array of words
 * @words: The array to free
 * Return: void
 */

void free_words(char **words)
{
	int i = 0;

	while (words[i])
	{
		if (words[i])
		{
			free(words[i]);
			words[i] = NULL;
		}
		i++;
	}
	if (words)
		free(words);
	words = NULL;
}

/**
 * split - split a string into an array of words
 * @str: the string in hand
 * Return: char** array of words
 */

char **split(char *str)
{
	int i = 0;
	char *word;
	char *copy;
	int size;
	char **words;

	remove_new_line(&str);
	copy = _strdup(str);
	size = count_words(copy);
	free(copy);
	words = (char **) malloc(sizeof(char *) * (size + 1));
	if (!words)
		return (NULL);
	word = strtok(str, " ");
	while (word)
	{
		if (*word)
			words[i] = word;
		i++;
		word = strtok(NULL, " ");
	}
	words[size] = NULL;
	return (words);
}
