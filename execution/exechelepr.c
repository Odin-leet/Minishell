/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exechelepr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aali-mou <aali-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 17:26:22 by aali-mou          #+#    #+#             */
/*   Updated: 2021/11/27 17:42:45 by aali-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	quotescount(int *i, int count, char *string, char c)
{
	if (string[*i] == c)
	{
		count++;
		(*i)++;
		if (string[*i] == c)
		{
			(*i)++;
			count++;
		}
		else
		{
			while (string[*i] != c && string[*i])
				(*i)++;
			if (string[*i] == c)
			{
				count++;
				(*i)++;
			}
		}
	}
	return (count);
}

int	checkforquotes2(char *string)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (string[i] != '\0')
	{
		count = quotescount(&i, count, string, '\"');
		count = quotescount(&i, count, string, '\'');
		i++;
	}
	return (count);
}

char	*db_quotesreplace(char *tmp, char *string, int *c, int *i)
{
	if (string[*i] == '\"')
	{
		(*i)++;
		if (string[*i] == '\"')
			(*i)++;
		else
		{
			while (string[*i] != '\"' && string[*i])
				tmp[(*c)++] = string[(*i)++];
			if (string[(*i)] == '\"')
					(*i)++;
		}
	}
	return (tmp);
}

char	*sgl_quotesreplace(char *tmp, char *string, int *c, int *i)
{
	if (string[*i] == '\'')
	{
		(*i)++;
		if (string[*i] == '\'')
			(*i)++;
		else
		{
			while (string[*i] != '\'' && string[*i])
				tmp[(*c)++] = string[(*i)++];
			if (string[(*i)] == '\'')
					(*i)++;
		}
	}
	return (tmp);
}

char	*changecollectedcmd(char *string, int count)
{
	char	*tmp;
	int		i;
	int		c;

	i = 0;
	c = 0;
	tmp = NULL;
	tmp = malloc(sizeof(char) * (ft_strlen(string) - count + 1));
	while (string[i] != '\0')
	{
		tmp = db_quotesreplace(tmp, string, &c, &i);
		tmp = sgl_quotesreplace(tmp, string, &c, &i);
		if (string[i] != '\0')
		{
			tmp[c] = string[i];
			c++;
			i++;
		}
	}
	tmp[c] = '\0';
	free(string);
	return (tmp);
}
