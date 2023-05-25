#include "shell.h"

/**
 * tokenize - tokenizes
 * @line: string
 * Return: pointer
 */

char **tokenize(char *line)
{
	char **tokens = NULL;
	char *token = NULL;
	int i = 0, len = 0;

	len = _strlen(line);
	if (len == 0)
		return (NULL);
	tokens = malloc(sizeof(char *) * (len + 1));
	if (tokens == NULL)
	{
		perror("Fatal Error");
		return (NULL);
	}
	token = my_strtok(line, " \n\t\r");
	while (token != NULL)
	{
		tokens[i] = token;
		token = my_strtok(NULL, " \n\t\r");
		i++;
	}
	tokens[i] = NULL;
	return (tokens);
}
