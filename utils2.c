#include "shell.h"

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

void free_tokens(char **ptr)
{
	int i = 0;

	while (ptr[i])
	{
		if (ptr[i])
			free(ptr[i]);
		i++;
	}
	if (ptr)
		free(ptr);
}

/**
 * cut_string - cuts a string when # is encountered
 * @str: string to be cut
 */

void cut_string(char *str)
{
	int i = 0;

	while (str[i])
	{
		if (str[i] == '#')
		{
			str[i] = '\0';
			return;
		}
		i++;
	}
}


int	ft_nbrlen(int n)
{
	int	counter;

	counter = 0;
	if (n <= 0)
		counter++;
	while (n)
	{
		counter++;
		n /= 10;
	}
	return (counter);
}

/**
 * _itoa - converts an integer to a string
 * @num: integer to be converted
 * Return: pointer to the converted string
 */

char	*_itoa(int n)
{
	char		*str;
	int			i;
	long int	nb;

	nb = (long int) n;
	i = ft_nbrlen(nb);
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	str[i] = '\0';
	i--;
	if (nb == 0)
		str[0] = nb + 48;
	if (nb < 0)
	{
		str[0] = '-';
		nb = -nb;
	}
	while (nb)
	{
		str[i] = (nb % 10) + 48;
		nb /= 10;
		i--;
	}
	return (str);
}