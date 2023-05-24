#include "shell.h"

/**
* count_words - countes the words in string
* @s: the string in hand
* @c: the character to split by
* Return: int
*/

static int	count_words(char *s, char c)
{
	int		counter;
	int	i;
	int		found;

	found = 0;
	counter = 0;
	i = 0;
	while (i <= _strlen(s))
	{
		if ((s[i] == c || s[i] == '\0') && found)
		{
			counter++;
			found = 0;
		}
		if (s[i] != c && !found)
			found = 1;
		i++;
	}
	return (counter);
}

/**
* wordlen - counts the length of a word
* @s: the string in hand
* @c: the end of the word
* Return: int
*/

static int	wordlen(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

/**
* ft_split - split the string into words
* @s: the stirng in hand
* @c: the char to split by
* Return: an array of strings
*/

char	**ft_split(char *s, char c)
{
	int			counter;
	char		**words;

	counter = 0;
	words = (char **) malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!words)
		return (NULL);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			words[counter] = ft_substr(s, 0, wordlen(s, c));
			counter++;
			while (*s && *s != c)
				s++;
		}
	}
	words[counter] = 0;
	return (words);
}
