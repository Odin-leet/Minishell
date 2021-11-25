/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashite <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 14:49:34 by ashite            #+#    #+#             */
/*   Updated: 2019/10/21 13:13:54 by ashite           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	trim_top(char *s, char *set)
{
	int	i;
	int	j;

	i = 0;
	while (s[i] != '\0')
	{
		j = 0;
		while (set[j] != '\0')
		{
			if (set[j] == s[i])
				break ;
			j++;
		}
		if (set[j] == '\0')
			return (i);
		i++;
	}
	return (0);
}

static int	trim_bot(char *s, char *set, int n)
{
	int	i;
	int	j;

	i = n;
	while (i > 0)
	{
		j = 0;
		while (set[j] != 0)
		{
			if (set[j] == s[i])
				break ;
			j++;
		}
		if (set[j] == '\0')
			return (i);
		i--;
	}
	return (0);
}

char	*ft_strtrim(char *s1, char const *set)
{
	char	*s;
	int		x;
	int		top;
	int		bot;

	if (!s1)
		return (0);
	x = 0;
	while (s1[x] != '\0')
		x++;
	top = trim_top((char *)s1, (char *)set);
	bot = trim_bot((char *)s1, (char *)set, x - 1) + 1;
	if (bot == 1)
		bot = 0;
	s = ft_substr(s1, top, bot - top);
	return (s);
}
