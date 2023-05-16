#include "shell.h"

/**
 * count_words - counts the words in a string
 * @str: the string in hand
 * @c: the delimiter
 * Return: int
 */

static int count_words(char *str, char *c)
{
	int words = 0;
	char *word;

	word = strtok(str, c);
	while (word)
	{
		words++;
		word = strtok(NULL, c);
	}
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
		free(words[i]);
		i++;
	}
	free(words);
}

/**
 * split - split a string into an array of words
 * @str: the string in hand
 * @c: the delimeter
 * Return: char** array of words
 */

char **split(char *str, char *c)
{
	int i = 0;
	char *word;
	char *copy;
	int size;
	char **words;

	remove_new_line(&str);
	copy = _strdup(str);
	size = count_words(copy, c);
	free(copy);
	words = (char **) malloc(sizeof(char *) * (size + 1));
	if (!words)
		return (NULL);
	word = strtok(str, c);
	while (word)
	{
		words[i] = word;
		i++;
		word = strtok(NULL, c);
	}
	free(word);
	words[size] = NULL;
	return (words);
}
