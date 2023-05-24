/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:26:41 by hoigag            #+#    #+#             */
/*   Updated: 2022/11/02 14:30:35 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (src || dst)
	{
		i = 0;
		while (i < n)
		{
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	return (dst);
}

char	*ft_substr(char	*s, unsigned int start, size_t len)
{
	char	*substr;

	if (!s)
		return (NULL);
	if ((int)start > _strlen(s))
		return (_strdup(""));
	if ((int) (start + len) > _strlen(s))
		len = _strlen(s) - start;
	substr = malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	ft_memcpy(substr, s + start, len);
	substr[len] = '\0';
	return (substr);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		size;

	if (!s1)
		s1 = _strdup("");
	size = _strlen(s1) + _strlen(s2);
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, _strlen(s1));
	ft_memcpy(str + _strlen(s1), s2, _strlen(s2));
	str[size] = '\0';
	free(s1);
	return (str);
}

int has_new_line(char *s)
{
	int i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	return (s[i] == '\n');
}
