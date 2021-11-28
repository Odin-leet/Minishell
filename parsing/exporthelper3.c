/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exporthelper3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aali-mou <aali-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 01:48:32 by aali-mou          #+#    #+#             */
/*   Updated: 2021/11/28 02:18:58 by aali-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	freesomething(char *tmp, t_vars *pl)
{
	free(tmp);
	free_pre(pl->env1, 0);
	free_pre(pl->envprinc, 0);
}

void	addenvfinal(char **tmp1, char **tmp3, t_vars *pl, char *tmp)
{
	freesomething(tmp, pl);
	pl->env1 = tmp1;
	pl->envprinc = tmp3;
}

void	addenvhelperif( char **tmp3, char **tmp1, char *string, t_vars *pl)
{
	char	*tmp;
	int		c;

	c = thereisequ(string);
	tmp = NULL;
	tmp = traitement1(string, c);
	tmp1 = malloc(sizeof(char *) * (counttab(pl->env1) + 2));
	tmp3 = malloc(sizeof(char *) * (counttab(pl->envprinc) + 2));
	c = 0;
	while (pl->env1[c] != NULL)
	{
		tmp1[c] = malloc(sizeof(char *) * (ft_strlen(pl->env1[c]) + 1));
		c++;
	}
	c = 0;
	while (pl->envprinc[c] != NULL)
	{
		tmp3[c] = malloc(sizeof(char *) * (ft_strlen(pl->envprinc[c]) + 1));
		c++;
	}
	tmp1 = remplirtmp(tmp1, pl->env1, tmp, c);
	tmp3 = remplirtmp(tmp3, pl->envprinc, string, c);
	addenvfinal(tmp1, tmp3, pl, tmp);
}

void	addenvhelperelse( char **tmp3, char **tmp1, char *string, t_vars *pl)
{
	char	*tmp;
	int		c;

	tmp = NULL;
	tmp = traitement2(string);
	tmp1 = malloc(sizeof(char *) * (counttab(pl->env1) + 2));
	tmp3 = malloc(sizeof(char *) * (counttab(pl->envprinc) + 2));
	c = 0;
	while (pl->env1[c] != NULL)
	{
		tmp1[c] = malloc(sizeof(char *) * (ft_strlen(pl->env1[c]) + 1));
		c++;
	}
	c = 0;
	while (pl->envprinc[c] != NULL)
	{
		tmp3[c] = malloc(sizeof(char *) * (ft_strlen(pl->envprinc[c]) + 1));
		c++;
	}
	tmp1 = remplirtmp(tmp1, pl->env1, tmp, c);
	tmp3 = remplirtmp(tmp3, pl->envprinc, string, c);
	addenvfinal(tmp1, tmp3, pl, tmp);
}

char	**addenv2(char *string, t_vars *pl)
{
	int		c;
	char	**tmp1;
	char	**tmp3;
	size_t	j;

	tmp3 = NULL;
	tmp1 = NULL;
	j = 0;
	c = 0;
	c = thereisequ(string);
	if (c != -1)
	{
		addenvhelperif(tmp3, tmp1, string, pl);
	}
	else
		addenvhelperelse(tmp3, tmp1, string, pl);
	return (NULL);
}
