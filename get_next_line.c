#include "shell.h"

/**
* ft_substr - finds a substring
* @s: the string in hand
* @start: where to start substring
* @len: the length of the substring
* Return: the substring
*/

char	*ft_substr(char *s, int start, int len)
{
	char	*substr;

	if (!s)
		return (NULL);
	if (start > _strlen(s))
		return (_strdup(""));
	if (start + len > _strlen(s))
		len = _strlen(s) - start;
	substr = malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	_memcpy(substr, s + start, len);
	substr[len] = '\0';
	return (substr);
}

/**
* read_to_stash - reads from fd to a static var
* @fd: the fd to read from
* @stash: the static var to store in
* Return: text read from fd
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
		if (_strchr(buffer, '\n'))
			break;
	}
	free(buffer);
	return (stash);
}

/**
* get_line_from_stash - gets the line ftom stash
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
* get_new_stash - gets the after the line
* @stash: the stash
* Return: return the rest after the line
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
* get_next_line - read a line from fd
* @fd: the file descriptor
* Return: the line read
*/

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	stash = read_to_stash(fd, stash);
	if (!stash)
		return (NULL);
	line = get_line_from_stash(stash);
	stash = get_new_stash(stash);
	return (line);
}
