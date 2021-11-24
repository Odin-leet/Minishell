#include "minishell.h"

static int	calc_words(char *s, char c)
{
	int		count;
	int		i;
	int		j;

	i = 0;
	j = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		while (s[i] != c && s[i] != '\0')
		{
			i++;
			j = 1;
		}
		while (s[i] == c && s[i] != '\0')
			i++;
		if (j == 1)
			count++;
	}
	return (count);
}

static int	calc_char(char *s, char c)
{
	int		i;

	i = 0;
	while (s[i] == c && s[i] != '\0')
		s++;
	while (s[i] != c && s[i] != '\0')
		i++;
	return (i);
}

static char	**ft_free(char **str, int i)
{
	int	j;

	j = 0;
	while (j <= i)
	{
		free(str[j]);
		j++;
	}
	free(str);
	return (str);
}

char	**ft_split1(char const *s, char c)
{
	int		i;
	int		j;
	char	**str;

	i = 0;
	if (!s)
		return (0);
	str = (char **)malloc(sizeof(char *) * (calc_words((char *)s, c) + 1));
	if (str == NULL)
		return (str);
	while (i < calc_words((char *)s, c))
	{
		j = 0;
		str[i] = (char *)malloc(sizeof(char) * (calc_char((char *)s, c) + 1));
		if (!str[i])
			return (ft_free(str, i));
		while (s[0] == c && s[0] != '\0')
			s++;
		while (s[0] != c && s[0] != '\0')
			str[i][j++] = *s++;
		str[i++][j] = '\0';
	}
	str[i] = 0;
	return (str);
}
