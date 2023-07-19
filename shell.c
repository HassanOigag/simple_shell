#include "shell.h"

/**
 * init_shell_struct - initializes the shell struct
 * @shell: the shell struct to be initilized
 * @argv: the value of argv
 * @env: the value of env
 * Return: void
*/

void init_shell_struct(t_shell *shell, char **argv, char **env)
{
	shell->argv = argv;
	shell->env = env;
	shell->error_counter = 0;
}

/**
 * main - starting point of the program
 * @argc: number of arguments
 * @argv: array of arguments
 * @env: array of environment variables
 * Return: 0 on success, 1 on failure
 */

int main(int __attribute__((unused))argc, char **argv, char **env)
{
	int status = 0;
	t_shell shell;

	init_shell_struct(&shell, argv, env);
	sigintHandler(0);
	while (1)
	{
		if (isatty(STDIN_FILENO))
			_putstr("$ ");
		shell.line = get_next_line(STDIN_FILENO);
		if (!shell.line)
		{
			if (isatty(STDIN_FILENO))
				_putchar('\n');
			free(shell.line);
			break;
		}
		if (shell.line[0] == '\n')
		{
			free(shell.line);
			continue;
		}
		cut_string(shell.line);
		shell.tokens = ft_split(shell.line, " \t\r\n");
		if (!shell.tokens)
		{
			free(shell.line);
			continue;
		}
		if (!shell.tokens[0])
		{
			free(shell.line);
			free_tokens(shell.tokens);
			continue;
		}
		status = execute(&shell);
		free(shell.line);
		free_tokens(shell.tokens);
	}
	return (status);
}
