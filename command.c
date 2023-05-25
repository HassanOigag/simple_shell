#include "shell.h"

/**
 * writ - writes an error message
 * @tokens: array
 * @argv: array
 * Return: void
 */

void writ(char **tokens, char **argv)
{
	write(STDERR_FILENO, argv[0], _strlen(argv[0]));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, "1", 1);
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, tokens[0], _strlen(tokens[0]));
	write(STDERR_FILENO, ": not found\n", 12);
}

/**
 * exec - execs
 * @tokens: array
 * @argv: array of arguments
 * @env: array of environment
 * @line: line from getline
 * Return: 0 on success, 1 on failure
 */

int exec(char **tokens, char **argv, char **env, char *line)
{
	char *command = NULL;
	pid_t child_pid = 0;
	int status = 0;

	if (built(tokens, argv, env, line) == 0)
	{
		gl_Exit(1, 0);
		return (0);
	}
	command = g_pat(tokens[0]);
	if (command == NULL)
	{
		writ(tokens, argv);
		gl_Exit(1, 127);
		return (1);
	}
	if (!access(command, X_OK))
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			perror(argv[0]);
			free(command);
			return (1);
		}
		if (child_pid == 0)
		{
			if (execve(command, tokens, env) == -1)
			{
				perror(argv[0]);
				free(command);
				exit(1);
			}
		}
		else
			wait(&status);
		gl_Exit(1, 0);
	}
	return (status);
}

/**
 * gl_Exit - gets the last exit code
 * @action: 0 to get, 1 to set
 * @status: exit
 * Return: last exit code
 */

int gl_Exit(int action, int status)
{
	static int last_exit;

	if (action == 1)
		last_exit = status;
	return (last_exit);
}
