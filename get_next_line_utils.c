#include "shell.h"

/**
 * _strcpy - copies a string
 * @dest: destination string
 * @src: source string
 * Return: pointer to the copied string
 */

char *_strcpy(char *dest, char *src)
{
	int i = 0;

	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/**
 * _memcpy - memory copy
 * @dst: destination
 * @src: source
 * @n: number of memory blocks to copy
 * Return: destination
 */

void	*_memcpy(void *dst, const void *src, size_t n)
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
 * ft_strjoin - joins two strings
 * @s1: the first string
 * @s2: the second  string
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
	_memcpy(str, s1, _strlen(s1));
	_memcpy(str + _strlen(s1), s2, _strlen(s2));
	str[size] = '\0';
	free(s1);
	return (str);
}

/**
 * _isnumber - checks if a string is a number
 * @str: string to check
 * Return: 0 if number, 1 if not
 */

int _isnumber(char *str)
{
	int i = 0;

	while (str[i] != '\0')
	{
		if ((str[i] < '0' || str[i] > '9') && str[i] != '-')
			return (1);
		i++;
	}
	return (0);
}

