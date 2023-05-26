#include "shell.h"

/**
 * main - the entry point
 * @argc: param
 * @argv: param
 * @env: envirenement
 * Return: int
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
			write(STDOUT_FILENO, "$ ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			break;
		}
		if (line[0] == '\n')
			continue;
		cut_string(line);
		tokens = ft_split(line, " \t\r\n");
		if (!tokens)
			continue;
		if (tokens[0] == NULL)
		{
			free(tokens);
			continue;
		}
		status = exec(tokens, argv, env, line);
		free(tokens);
	}
	free(line);
	return (status);
}
