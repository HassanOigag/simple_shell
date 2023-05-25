#include "shell.h"

/**
 * _strspn - gets the length of a prefix substring
 * @str: string to be searched
 * @accept: string containing the characters to match
 * Return: number of bytes in the initial segment of str
 * which consist only of bytes from accept
 */

int _strspn(char *str, const char *accept)
{
    int i = 0, j = 0, count = 0;

    while (str[i] != '\0')
    {
        j = 0;
        while (accept[j] != '\0')
        {
            if (str[i] == accept[j])
            {
                count++;
                break;
            }
            j++;
        }
        if (accept[j] == '\0')
        {
            break;
        }
        i++;
    }

    return count;
}

/**
 * _strpbrk - searches a string for any of a set of bytes
 * @str: string to be searched
 * @accept: string containing the characters to match
 * Return: pointer to the byte in str that matches one of the bytes in accept
 * or NULL if no such byte is found
 */

char *_strpbrk(char *str, const char *accept)
{
    int i = 0, j = 0;

    while (str[i] != '\0')
    {
        j = 0;
        while (accept[j] != '\0')
        {
            if (str[i] == accept[j])
            {
                return (str + i);
            }
            j++;
        }
        i++;
    }

    return NULL;
}

/**
 * my_strtok - tokenizes a string
 * @str: string to tokenize
 * @delim: delimiter to tokenize by
 * Return: pointer to an array of tokens
 */

char *my_strtok(char *str, const char *delim)
{
    static char *lastToken = NULL;
    char *token;

    if (str == NULL)
    {
        str = lastToken;
    }

    if (str == NULL)
    {
        return NULL;
    }

    token = str;
    str += _strspn(str, delim);

    if (*str == '\0')
    {
        lastToken = NULL;
        return NULL;
    }

    token = str;
    str = _strpbrk(str, delim);

    if (str == NULL)
    {
        lastToken = NULL;
    }
    else
    {
        *str = '\0';
        lastToken = str + 1;
    }

    return token;
}