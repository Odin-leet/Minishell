/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aali-mou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 21:20:29 by aali-mou          #+#    #+#             */
/*   Updated: 2019/10/28 22:24:06 by aali-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t		len_word(const char *s, char c)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (s[i] == c)
		i++;
	while (s[i] != c && s[i++])
		len++;
	return (len);
}



void				*free_pre(char **split, int k)
{
	while (k >= 0)
	{
		free(split[k]);
		k--;
	}
	free(split);
	split = NULL;
	return (NULL);
}

char				**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	**split;

	i = 0;
	k = 0;
	if (!s || !(split = (char **)malloc(sizeof(char *)
					* (count_word(s, c) + 1))))
		return (NULL);
	while (i < count_word(s, c))
	{
		if (!(split[i] = (char *)malloc(sizeof(char)
						* (len_word(&s[k], c) + 1))))
			return ((free_pre(split, k - 1)));
		j = 0;
		while (s[k] == c)
			k++;
		if(s[k])
		while (s[k] != c && s[k])
			split[i][j++] = s[k++];
		split[i][j] = '\0';
		i++;
	}
	split[i] = NULL;
	return (split);
}
