#include "shell.h"

/**
* read_to_stash - reads from an fd and stores in stash
* @fd: the file descriptor
* @stash: the file to store
* Return: read string
*/

char	*read_to_stash(int fd, char *stash)
{
	int		r;
	char	*buffer;

	r = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (0);
	while (r > 0)
	{
		r = read(fd, buffer, BUFFER_SIZE);
		if (r == -1)
			break;
		buffer[r] = '\0';
		stash = ft_strjoin(stash, buffer);
		if (has_new_line(buffer))
			break;
	}
	free(buffer);
	return (stash);
}

/**
* get_line_from_stash - gets the line from stash
* @stash: the stash
* Return: returns the line
*/

char	*get_line_from_stash(char *stash)
{
	int		i;
	char	*line;

	if (!stash[0])
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	line = ft_substr(stash, 0, i + 1);
	return (line);
}

/**
* get_new_stash - remove the line from stash
* @stash: the stash
* Return: returns the new stash
*/

char	*get_new_stash(char *stash)
{
	int		i;
	char	*new_stash;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	new_stash = ft_substr(stash, i + 1, _strlen(stash) - i + 1);
	free(stash);
	return (new_stash);
}

/**
* get_next_line - reads line by line from a file descriptor
* @fd: the file descriptor
* Return: the line
*/

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || fd == 1 || fd == 2 || BUFFER_SIZE <= 0)
		return (0);
	stash = read_to_stash(fd, stash);
	if (!stash)
		return (NULL);
	line = get_line_from_stash(stash);
	stash = get_new_stash(stash);
	return (line);
}
