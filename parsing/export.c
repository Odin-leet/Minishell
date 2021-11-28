/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aali-mou <aali-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 09:26:22 by aali-mou          #+#    #+#             */
/*   Updated: 2021/11/28 02:02:02 by aali-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	checkforquotes(char **string)
{
	int		i;
	int		c;
	int		count;
	char	*tmp;

	i = -1;
	c = 0;
	if (*string)
	{
		count = returnquotescount(*string);
		tmp = malloc(sizeof(char) * (ft_strlen(*string) - count + 1));
		i = 0;
		while ((*string)[i] != '\0')
		{
			if (!((*string)[i] == '\'' || (*string)[i] == '\"'))
				tmp[c++] = (*string)[i];
			i++;
		}
		tmp[c] = '\0';
		free(*string);
		*string = tmp;
	}
}

int	checkifitscomp(char **string)
{
	int	i;

	i = 0;
	checkforquotes(string);
	if (i == 0 && (*string)[i] == '=')
		return (1);
	while ((*string)[i] != '\0' && (*string)[i] != '=')
	{
		if ((*string)[i] != '_' && (ft_isdigit((*string)[i]) == 0)
			&& (ft_isalpha2((*string)[i]) == 0))
			return (1);
		i++;
	}
	return (0);
}

int	exporthelper(t_vars *pl)
{
	int	i;

	i = 1;
	while (pl->collected_cmd[i] != NULL)
	{
		if (checkifthereisquotes(pl->collected_cmd[i]) == 1)
			return (0);
		if (checkifitscomp(&pl->collected_cmd[i]) == 1)
		{
			printf("error of export\n");
			return (0);
		}
		else
			addenv(pl, pl->collected_cmd[i]);
		i++;
	}
	return (1);
}

int	export(t_vars *pl)
{
	int	i;

	i = 1;
	if (pl->collected_cmd[1] == NULL)
	{
		i = 0;
		while (pl->env1[i])
		{
			printf("%s \n", pl->env1[i]);
			i++;
		}
	}
	else
	{
		if (exporthelper(pl) == 0)
			return (1);
	}
	return (0);
}

int	env(t_vars *pl)
{
	int	i;

	i = 0;
	if (pl->collected_cmd[1] != NULL)
	{
		printf("env: %s: No such file or directory\n", pl->collected_cmd[1]);
		return (1);
	}
	while (pl->envprinc[i] != NULL)
	{
		if (thereisequ(pl->envprinc[i]) != -1)
			printf("%s\n", pl->envprinc[i]);
		i++;
	}
	return (0);
}
