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
	size_t len = 0;
	ssize_t read = 0;
	int status = 0;

	(void)argc;
	sigintHandler(0);
	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);
		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			break;
		}
		if (line[0] == '\n')
			continue;
		cut_string(line);
		tokens = tokenize(line);
		if (tokens == NULL)
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
