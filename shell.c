#include "shell.h"

/**
 *execute_command - executes a command
 *@cmd:  the command to be executed
 *@path: the path env variable
 *Return: void
 */

void execute_command(char *cmd, char *path, char **env)
{
	char **words;
	int pid;
	char *full_path;

	words = split(cmd, " ");
	if (words[0][0] == '/' && access(words[0], F_OK) != 0)
	{
		printf("./shell: No such file or directory\n");
		return;
	}
	else if (words[0][0] == '/' && access(words[0], F_OK) == 0)
		full_path = words[0];
	else
		full_path = is_file_in_path(path, words[0]);
	if (!full_path)
	{
		printf("./shell: No such file or directory\n");
		return;
	}
	pid = fork();
	if (pid == 0)
	{
		if (execve(full_path, words, env) == -1)
		{
			printf("./shell: No such file or directory\n");
			exit(15);
		}
	}
	else if (pid < 0)
		printf("fork error\n");
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
	int	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}

/**
 * main - the entry point
 * Return: int
 */

int main(int __attribute__((unused))argc, char __attribute__((unused))**argv, char **env)
{
	char *line = NULL;
	char *path;

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
			printf("exit\n");
			return (0);
		}
		if (strcmp(line, "env") == 0)
			printenv(env);
		if (line[0])
			execute_command(line, _strdup(path), env);
		free(line);
	}
	return (0);
}
