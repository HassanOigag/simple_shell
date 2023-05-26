#include "shell.h"

/**
 * main - starting point of the program
 * @argc: number of arguments
 * @argv: array of arguments
 * @env: array of environment variables
 * Return: 0 on success, 1 on failure
 */

int main(int argc, char **argv, char **env)
{
	char *line = NULL, **tokens = NULL;
	int status = 0;

	(void)argc;
	sigintHandler(0);
	while (1)
	{
		if (isatty(STDIN_FILENO))
			_putstr("$ ");
		line = get_next_line(STDIN_FILENO);
		if (!line)
		{
			if (isatty(STDIN_FILENO))
				_putchar('\n');
			free(line);
			break;
		}
		if (line[0] == '\n')
		{
			free(line);
			continue;
		}
		cut_string(line);
		tokens = ft_split(line, " \t\r\n");
		if (!tokens)
		{
			free(line);
			continue;
		}
		if (!tokens[0])
		{
			free(line);
			free_tokens(tokens);
			continue;
		}
		status = execute(tokens, argv, env, line);
		free(line);
		free_tokens(tokens);
	}
	return (status);
}
