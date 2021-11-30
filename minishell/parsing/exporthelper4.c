/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exporthelper4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aali-mou <aali-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 01:52:09 by aali-mou          #+#    #+#             */
/*   Updated: 2021/11/28 01:54:20 by aali-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**addenv(t_vars *pl, char *string)
{
	int	i;
	int	c;

	i = 0;
	c = checkifthereisenv(pl->env1, string);
	if (c == 1)
	{
		while (string[i])
		{
			if (string[i] == '=')
			{
				replaceenv(pl, string);
				c = -1;
			}
			i++;
		}
	}
	else
	{
		i = 0;
		addenv2(string, pl);
	}
	return (NULL);
}

int	errorexport2(void)
{
	printf("bash: export: quotes error \n");
	return (1);
}

int	errorexport(char *string)
{
	printf("bash: export: %s : not a valid identifier\n", string);
	return (1);
}

int	checkifthereisquotes(char *string)
{
	int	i;
	int	db_q;
	int	sgl_q;

	i = 0;
	db_q = 0;
	sgl_q = 0;
	while (string[i] != '\0')
	{
		if (string[i] == '\"' && sgl_q == 0)
			db_q++;
		if (string[i] == '\'' && db_q == 0)
			sgl_q++;
		if (string[i] == '\"' && ((sgl_q % 2) != 0))
			return (errorexport(string));
		if (string[i] == '\'' && ((db_q % 2) != 0))
			return (errorexport(string));
		i++;
	}
	if (sgl_q % 2 != 0 || db_q % 2 != 0)
		return (errorexport2());
	return (0);
}

int	returnquotescount(char *string)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (string && string[i] != '\0')
	{
		if (string[i] == '\"')
			count++;
		if (string[i] == '\'')
			count++;
		i++;
	}
	return (count);
}
