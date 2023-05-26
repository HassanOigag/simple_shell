#include "shell.h"

/**
* _strchr - searches for a character
* @s: the string
* @c: the character
* Return: returns a pointer to the character
*/
char *_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

/**
* _strncpy - copies a string
* @dest: destination
* @src: source
* @n: number of char
* Return: dest
*/

char *_strncpy(char *dest, const char *src, size_t n)
{
	size_t i;

	for (i = 0; i < n && src[i]; i++)
		dest[i] = src[i];

	for (; i < n; i++)
		dest[i] = '\0';

	return (dest);
}

/**
 * count_words - counts the words in string
 * @s: the string in hand
 * @delimiters: the set of characters to split by
 * Return: int
 */

int count_words(char *s, char *delimiters)
{
	int counter = 0;
	int found = 0;
	int i = 0;

	while (s[i] != '\0')
	{
		if (_strchr(delimiters, s[i]) != NULL)
			found = 0;
		else if (found == 0)
		{
			found = 1;
			counter++;
		}
		i++;
	}
	return (counter);
}

/**
 * wordlen - counts the length of a word
 * @s: the string in hand
 * @delimiters: the set of characters to split by
 * Return: int
 */
static int wordlen(char *s, char *delimiters)
{
	int i = 0;

	while (s[i] && !_strchr(delimiters, s[i]))
		i++;
	return (i);
}

/**
 * ft_split - split the string into words
 * @s: the string in hand
 * @delimiters: the set of characters to split by
 * Return: an array of strings
 */
char **ft_split(char *s, char *delimiters)
{
	int counter = 0;
	char **words;
	char *word;

	counter = 0;
	words = (char **)malloc(sizeof(char *) * (count_words(s, delimiters) + 1));
	if (!words)
		return (NULL);

	while (*s)
	{
		while (*s && _strchr(delimiters, *s))
			s++;
		if (*s && !_strchr(delimiters, *s))
		{
			int word_length = wordlen(s, delimiters);

			word = (char *)malloc(sizeof(char) * (word_length + 1));
			if (!word)
			{
				free_tokens(words);
				return (NULL);
			}
			_strncpy(word, s, word_length);
			word[word_length] = '\0';
			words[counter] = word;
			counter++;
			s += word_length;
		}
	}
	words[counter] = (NULL);
	return (words);
}
