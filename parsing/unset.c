/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aali-mou <aali-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 09:27:59 by aali-mou          #+#    #+#             */
/*   Updated: 2021/11/28 00:48:21 by aali-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <string.h>

int	unsetreturncount(char *string, char *tmp)
{
	int	j;
	int	count;

	j = 0;
	count = 0;
	if (strchr(string, '=') != NULL)
	{
		while (tmp[j])
		{
			if (tmp[j] == '=')
			{
				count = j;
				break ;
			}
			j++;
		}
	}
	else
		count = ft_strlen(tmp);
	return (count);
}

int	unsetcheckenv(int i, int count, char **env, int count2)
{
	int	j;

	j = 0;
	while (env[i][j] != '\0')
	{
		if (env[i][j] == '=')
		{
			count2 = j;
			break ;
		}
		j++;
		if (env[i][j] == '\0')
			count2 = j;
	}
	if (count2 > count)
		count2 = count;
	return (count2);
}

int	checkifthereisenv2(char **env, char *string)
{
	int		i;
	int		count;
	int		count2;
	int		j;
	char	*tmp;

	count2 = 0;
	tmp = NULL;
	i = 0;
	tmp = ft_strjoin("declare -x ", string);
	count = unsetreturncount(string, tmp);
	while (env[i] != NULL)
	{
		j = 0;
		count2 = unsetcheckenv(i, count, env, count2);
		if (strncmp(tmp, env[i], count) == 0)
		{
			free(tmp);
			return (1);
		}
		i++;
	}
	free(tmp);
	return (0);
}

int	unsetenv1returncount(char **env, char *tmp, int count, int i)
{
	int	j;

	i = -1;
	while (env[++i] != NULL)
	{
		j = 0;
		while (env[i][j] != '\0')
		{
			if (env[i][j] == '=')
			{
				count = j;
				break ;
			}
			j++;
			if (env[i][j] == '\0')
				count = j;
		}
		if (strncmp(tmp, env[i], count) == 0)
		{
			count = i;
			break ;
		}
	}
	return (count);
}

char	**unsettaballoc(char **env, char **tmp, int count)
{
	int	c;
	int	i;

	i = 0;
	c = 0;
	while (env[i] != NULL)
	{
		if (i == count)
			i++;
		else
		{
			tmp[c] = malloc(sizeof(char) * (ft_strlen(env[i]) + 1));
			c++;
			i++;
		}
	}
	return (tmp);
}
