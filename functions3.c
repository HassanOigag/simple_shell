#include "main.h"

/**
 * print_val - prints a value
 * @val: value to be printed
 * Return: void
 */

void print_val(int val)
{
	char *str = NULL;

	str = _itoa(val);
	write(STDOUT_FILENO, str, _strlen(str));
	write(STDOUT_FILENO, "\n", 1);
	free(str);
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
