#include "minishell.h"

size_t	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_isdigit(int c)
{
	unsigned char	k;

	k = (unsigned char)c;
	if (c <= 57 && c >= 48)
		return (1);
	else
		return (0);
}

int	ft_isalpha(int c)
{
	unsigned char	k;

	k = (unsigned char)c;
	if (c <= 90 && c >= 65)
		return (1);
	
	return (0);
}
