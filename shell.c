#include "shell.h"

/**
 * @execute_command - executes a command
 * 
 * @cmd:  the command to be executed
 * Return: void
 */

void execute_command(char *cmd)
{
    char **words;
    int pid;

    words = split(cmd);
    pid = fork();
    if (pid == 0)
    {
        if (words[1])
        {
            printf("./shell: No such file or directory\n");
            exit(15);
        }
        if (execve(words[0], words, NULL) == -1)
        {
            printf("./shell: No such file or directory\n");
            exit(15);
        }
        free_words(words);
    }
    else if (pid < 0)
        printf("fork error\n");
    else
        wait(NULL);
}

/**
 * @main - the entry point
 * 
 * Return int 
 */

int main()
{
    char *line = NULL;
    size_t n = 0;
    ssize_t read;

    while (1)
    {
        printf("HHshell$ ");
        read = getline(&line, &n, stdin);
        if (!line || !line[0])
            return 0;
        execute_command(line);
    }

    free(line);
    return 0;
}