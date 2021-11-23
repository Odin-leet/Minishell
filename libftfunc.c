#include "minishell.h"

char	*ft_calloc(size_t count, size_t size)
{
	char	*dest;
	size_t	i;

	dest = malloc(count * size);
	if (!(dest))
		return (0);
	i = 0;
	while (i < (count * size))
		dest[i++] = 0;
	return (dest);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char			*dest;
	unsigned long	i;
	unsigned long	j;
	size_t			res_len;

	res_len = 0;
	if (!(res_len) && s1)
		res_len = ft_strlen(s1);
	j = 0;
	dest = malloc(res_len + ft_strlen(s2) + 1);
	if (!(dest))
		return (0);
	i = -1;
	if (s1 == 0 && s2 == 0)
		return (0);
	while (++i < res_len)
		dest[i] = s1[i];
	res_len = ft_strlen(s2);
	while (j < res_len)
		dest[i++] = s2[j++];
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(char *s, size_t i)
{
	int		n;
	int		k;
	int		j;
	char	*dest;

	k = 0;
	j = i;
	while (s[j] != '\0')
	{
		j++;
	}
	k = j;
	n = 0;
	dest = malloc(sizeof(char) * (k + 1));
	while (s[i] != '\0')
	{
		dest[n] = s[i];
		n++;
		i++;
	}
	dest[n] = '\0';
	return (dest);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	j;
	unsigned long	k;

	k = 1;
	j = 0;
	if (n == 0)
		return (0);
	while ((s1[j] != '\0' && s2[j] != '\0') && (k < n))
	{
		if (s1[j] == s2[j])
		{
			j++;
		}
		k++;
	}
	return ((unsigned char)s1[j] - (unsigned char)s2[j]);
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
		src = (char *)s;
		dest = (char *) malloc(len + 1);
		if (!(dest))
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
