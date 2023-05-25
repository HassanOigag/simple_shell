#include "main.h"


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
 * _strcat - concatenates two strings
 * @dest: destination string
 * @src: source string
 * Return: pointer to the concatenated string
 */

char *_strcat(char *dest, char *src)
{
	int i, j;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;

	while (src[j] != '\0')
	{
		dest[i] = src[j];
		j++;
		i++;
	}

	dest[i] = '\0';

	return (dest);
}

/**
 * ffree - frees a double pointer
 * @ptr: double pointer to be freed
 * Return: void
 */

void ffree(char **ptr)
{
	int i = 0;

	if (ptr == NULL)
		return;

	while (ptr[i] != NULL)
	{
		free(ptr[i]);
		i++;
	}

	free(ptr);
}

/**
 * cut_string - cuts a string when # is encountered
 * @str: string to be cut
 */

void cut_string(char *str)
{
	int i = 0;

	while (str[i] != '\0')
	{
		if (str[i] == '#')
		{
			str[i] = '\0';
			return;
		}
		i++;
	}
}

/**
 * _itoa - converts an integer to a string
 * @num: integer to be converted
 * Return: pointer to the converted string
 */

char *_itoa(int num)
{
	int i = 0, j = 0, k = 0, l = 0, m = 0;
	char *str = NULL;

	if (num == 0)
	{
		str = malloc(sizeof(char) * 2);
		if (str == NULL)
			return (NULL);
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	if (num < 0)
		l = 1;
	m = num;
	while (m != 0)
	{
		m /= 10;
		i++;
	}
	str = malloc(sizeof(char) * (i + 1 + l));
	if (str == NULL)
		return (NULL);
	if (l == 1)
		str[0] = '-';
	for (j = i - 1 + l; j >= l; j--)
	{
		k = num % 10;
		if (k < 0)
			k *= -1;
		str[j] = k + '0';
		num /= 10;
	}
	str[i + l] = '\0';
	return (str);
}
