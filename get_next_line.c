/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aali-mou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 21:07:40 by aali-mou          #+#    #+#             */
/*   Updated: 2021/10/05 13:33:25 by aali-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_calloc(size_t count, size_t size)
{
	char	*dest;
	size_t	i;

	if (!(dest = (char*)malloc(count * size)))
		return (0);
	i = 0;
	while (i < (count * size))
		dest[i++] = 0;
	return (dest);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char			*dest;
	char			*src;
	unsigned long	j;

	if (s == 0)
		return (0);
	if (start > ft_strlen(s))
		return (dest = ft_calloc(1, 1));
	else
	{
		j = 0;
		src = (char*)s;
		if (!(dest = (char*)malloc(len + 1)))
			return (0);
		while (*src && j < len)
		{
			dest[j] = src[start];
			j++;
			start++;
		}
		dest[j] = '\0';
	}
	return (dest);
}

int		res_handel(char **res, char **line, int n, char *buffer)
{
	char	*tmp;

	n = ft_strchr(*res, '\n') - *res;
	*line = ft_substr(*res, 0, n);
	tmp = *res;
	*res = ft_strdup(*res, n + 1);
	free(tmp);
	if (buffer)
		free(buffer);
	return (1);
}

int		handle_buffer(char *buffer, char **res, char **line, int fd)
{
	int		n;

	while ((n = read(fd, buffer, BUFFER_SIZE)) >= 0)
	{
		buffer[n] = '\0';
		if (n > 0)
		{
			*res = ft_strjoin(*res, buffer);
			if (ft_strchr(buffer, '\n') != NULL)
				return (res_handel(res, line, n, buffer));
		}
		else if (ft_strchr(*res, '\n') != NULL)
			return (res_handel(res, line, n, buffer));
		else
		{
			free(buffer);
			*line = ft_strdup(*res, 0);
			free(*res);
			*res = NULL;
			return (0);
		}
	}
	free(buffer);
	free(*res);
	return (-1);
}

int		get_next_line(int fd, char **line)
{
	char			*buffer;
	static	char	*res;

	if (fd < 0 || !line || BUFFER_SIZE < 0)
		return (-1);
	if (res == NULL)
		res = ft_strdup("", 0);
	else if (ft_strchr(res, '\n') != NULL)
		return (res_handel(&res, line, 0, NULL));
	if (!(buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	return (handle_buffer(buffer, &res, line, fd));
	return (-1);
}
