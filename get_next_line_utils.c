#include "shell.h"

/**
* ft_memcpy - copies memory from one block to another
* @dst: the destination
* @src:  the source
* @n: the number to copy
* Return: destionation
*/

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (src || dst)
	{
		i = 0;
		while (i < n)
		{
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	return (dst);
}

/**
* ft_substr - returns a part of a string
* @s: the string in hand
* @start: where to start the new string
* @len: the len to cpy
* Return: the new string
*/

char	*ft_substr(char	*s, unsigned int start, size_t len)
{
	char	*substr;

	if (!s)
		return (NULL);
	if ((int)start > _strlen(s))
		return (_strdup(""));
	if ((int) (start + len) > _strlen(s))
		len = _strlen(s) - start;
	substr = malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	ft_memcpy(substr, s + start, len);
	substr[len] = '\0';
	return (substr);
}

/**
* ft_strjoin - joins two stings together
* @s1: the first string
* @s2: the second string
* Return: the joined string
*/

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		size;

	if (!s1)
		s1 = _strdup("");
	size = _strlen(s1) + _strlen(s2);
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, _strlen(s1));
	ft_memcpy(str + _strlen(s1), s2, _strlen(s2));
	str[size] = '\0';
	free(s1);
	return (str);
}

/**
* has_new_line - checks if there is new line
* @s: the stirng in hand
* Return: int
*/

int has_new_line(char *s)
{
	int i = 0;

	while (s[i] && s[i] != '\n')
		i++;
	return (s[i] == '\n');
}