#include "main.h"

/**
 * tokenize - tokenizes a string
 * @line: string to tokenize
 * Return: pointer to an array of tokens
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
	token = strtok(line, " \n\t\r");
	while (token != NULL)
	{
		tokens[i] = token;
		token = strtok(NULL, " \n\t\r");
		i++;
	}
	tokens[i] = NULL;
	return (tokens);
}
