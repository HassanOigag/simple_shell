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
* ft_putstr - prints a string
* @str: the string in hand
* Return: nothing
*/

void ft_putstr(char *str)
{
	int i = 0;

	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}
