/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exporthelper2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aali-mou <aali-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 01:44:35 by aali-mou          #+#    #+#             */
/*   Updated: 2021/11/28 02:18:46 by aali-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <string.h>

void	replaceeenv2(t_vars *pl, char *tmp, int i, int c)
{
	int	j;

	j = 0;
	c = 0;
	i = 0;
	while (pl->env1 && pl->env1[i])
	{
		j = ft_strlen(pl->env1[i]);
		c = 0;
		while (pl->env1[i][c])
		{
			if (pl->env1[i][c] == '=')
				j = c;
			c++;
		}
		if (strncmp(tmp, pl->env1[i], j) == 0)
		{
			free(pl->env1[i]);
			pl->env1[i] = NULL;
			pl->env1[i] = tmp;
		}
		i++;
	}
}

void	replaceeenv1(t_vars *pl, char *string1, int i, int c)
{
	int	j;

	i = 0;
	c = 0;
	j = 0;
	while (pl->envprinc[i])
	{
		j = ft_strlen(pl->envprinc[i]);
		c = 0;
		while (pl->envprinc[i][c] != '\0')
		{
			if (pl->envprinc[i][c] == '=')
				j = c;
			c++;
		}
		if (strncmp(string1, pl->envprinc[i], j) == 0)
		{
			(free(pl->envprinc[i]));
			pl->envprinc[i] = NULL;
			pl->envprinc[i] = string1;
		}
		i++;
	}
}

void	replaceenv(t_vars *pl, char *string)
{
	int		i;
	char	*tmp;
	int		j;
	int		c;
	char	*string1;

	c = 0;
	j = 0;
	i = 0;
	string1 = strdup(string);
	c = thereisequ(string);
	tmp = traitement1(string1, c);
	replaceeenv2(pl, tmp, i, c);
	replaceeenv1(pl, string1, i, c);
}

int	counttab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char	**remplirtmp(char **tmp1, char **env, char *string, int c)
{
	size_t	j;

	c = 0;
	j = 0;
	while (env[c])
	{
		j = 0;
		while (env[c][j])
		{
			tmp1[c][j] = env[c][j];
			j++;
		}
		tmp1[c][j] = '\0';
		c++;
	}
	tmp1[c] = malloc(sizeof(char ) * (ft_strlen(string)+ 1));
	j = 0;
	while (j < ft_strlen(string))
	{
		tmp1[c][j] = string[j];
		j++;
	}
	tmp1[c][j] = '\0';
	tmp1[++c] = NULL;
	return (tmp1);
}
