#include "shell.h"

/**
 *execute_command - executes a command
 *@cmd:  the command to be executed
 *@path: the path env variable
 *@env: envirenement
 *Return: void
 */

void execute_command(char *cmd, char __attribute__((unused))*path, char **env)
{
	char **words;

	int pid;
	/*char *full_path;*/

	words = ft_split(cmd, ' ');
	if (words[1])
	{
		write(2, "./shell: No such file or directory\n", 35);
		return;
	}
	/**if (words[0][0] == '/' && access(words[0], F_OK) != 0)
	{
		perror("./shell:");
		return;
	}
	else if (words[0][0] == '/' && access(words[0], F_OK) == 0)
		full_path = words[0];
	else
		full_path = is_file_in_path(path, words[0]);
	if (!full_path)
	{
		perror("./shell:");
		return;
	}*/
	pid = fork();
	if (pid == 0)
	{
		if (execve(words[0], words, env) == -1)
		{
			perror("./shell");
			free_words(words);
			exit(15);
		}
	}
	else if (pid < 0)
		perror("fork error");
	else
		wait(NULL);
}

/**
 * printenv - prints the env
 * @env: array of strings
 * Return: void
 */

void printenv(char **env)
{
	int i = 0;

	while (env[i])
	{
		ft_putstr(env[i]);
		write(1, "\n", 1);
		i++;
	}
}

/**
 * main - the entry point
 * @argc: param
 * @argv: param
 * @env: envirenement
 * Return: int
 */

int main(int argc, char **argv, char **env)
{
	char *line = NULL;
	char *path;
	(void) argc;
	(void) argv;

	path = getenv("PATH");
	while (1)
	{
		write(0, "$ ", 3);
		line = get_next_line(0);
		if (!line)
			return (0);
		remove_new_line(&line);
		if (strcmp(line, "exit") == 0)
		{
			ft_putstr("exit\n");
			return (0);
		}
		if (strcmp(line, "env") == 0)
			printenv(env);
		if (line[0])
			execute_command(line, _strdup(path), env);
		free(line);
	}
	if (line)
		free(line);
	return (0);
}
