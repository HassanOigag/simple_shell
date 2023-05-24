#include "shell.h"

/**
* ft_strncmp - compares two strings
* @s1: the frist string
* @s2: the second string
* @n: numbers of char to compare
* Return: int
*/

static int    ft_strncmp(const char *s1, const char *s2, size_t n)
{
    size_t    i;

    i = 0;
    if (!n)
        return (0);
    while ((s2[i] || s1[i]) && i < n - 1 && s1[i] == s2[i])
        i++;
    return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

/**
* ft_getenv - gets the env variable
* @name: the env name
* @env: env
* Return: char *
*/

char    *ft_getenv(char *name, char **env)
{
    char    **values;
    char    *value;
    int        name_len;
    int        i;

    value = NULL;
    values = NULL;
    name_len = _strlen(name);
    i = 0;
    while (env[i])
    {
        if (ft_strncmp(env[i], name, name_len) == 0
            && env[i][name_len] == '=')
        {
            values = ft_split(env[i], '=');
            value = _strdup(values[1]);
            free_words(values);
            break ;
        }
        i++;
    }
    return (value);
}
