#include "shell.h"

/**
 *execute_command - executes a command
 *@cmd:  the command to be executed
 *@path: the path env variable
 *Return: void
 */

void execute_command(char *cmd, char *path)
{
	char **words;
	int pid;
	char *full_path;

	words = split(cmd, " ");
	if (access(words[0], F_OK) == 0)
		full_path = words[0];
	else
		full_path = is_file_in_path(path, words[0]);
	if (!full_path)
	{
		printf("./shell: command not found\n");
		return;
	}
	pid = fork();
	if (pid == 0)
	{
		if (execve(full_path, words, NULL) == -1)
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
 * main - the entry point
 * Return: int
 */

int main(void)
{
	char *line = NULL;
	size_t n = 0;
	ssize_t read;
	char *path;

	path = getenv("PATH");
	while (1)
	{
		printf("$ ");
		read = getline(&line, &n, stdin);
		if (read < 0)
			return (0);
		remove_new_line(&line);
		if (line[0])
			execute_command(line, _strdup(path));
	}
	free(line);
	return (0);
}
