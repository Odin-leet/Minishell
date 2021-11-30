/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsethelper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aali-mou <aali-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 00:45:04 by aali-mou          #+#    #+#             */
/*   Updated: 2021/11/28 00:46:15 by aali-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	unset(t_vars *pl)
{
	int	i;

	i = 1;
	while (pl->collected_cmd[i])
	{
		if (checkifitscomp1(pl->collected_cmd[i]) == 1)
		{
			printf("bash: unset: `%s': not a valid identifier\n",
				pl->collected_cmd[i]);
			return (1);
		}
		else if (checkifthereisenv2(pl->env1, pl->collected_cmd[i]) == 1)
		{
			unsetenv1(pl, pl->collected_cmd[i]);
		}
		i++;
	}
	return (0);
}

int	checkifitscomp1(char *string)
{
	int	i;

	i = 0;
	if (i == 0 && string[i] != '_' && (ft_isalpha2(string[i]) == 0))
		return (1);
	while (string[i] != '\0')
	{
		if (string[i] != '_' && (ft_isdigit(string[i]) == 0)
			&& (ft_isalpha2(string[i]) == 0))
			return (1);
		i++;
	}
	return (0);
}	

char	**remplirtableunset(char **env, char **tmp, int count, int i)
{
	int	c;
	int	j;

	c = 0;
	j = 0;
	while (env[i] != NULL)
	{
		j = 0;
		if (i == count)
			i++;
		else
		{
			while (env[i][j] != '\0')
			{
				tmp[c][j] = env[i][j];
				j++;
			}
			tmp[c][j] = '\0';
			i++;
			c++;
		}
	}
	tmp[c] = NULL;
	return (tmp);
}

void	unsetenv1(t_vars *pl, char *string)
{
	char	**tmp1;
	char	**tmp2;
	char	*tmp;
	int		count;
	int		i;

	i = 0;
	count = 0;
	tmp2 = malloc(sizeof(char *) * (counttab(pl->env1)));
	tmp1 = malloc(sizeof(char *) * (counttab(pl->envprinc)));
	tmp = ft_strjoin("declare -x ", string);
	count = unsetenv1returncount(pl->env1, tmp, count, i);
	tmp2 = unsettaballoc(pl->env1, tmp2, count);
	i = 0;
	tmp2 = remplirtableunset(pl->env1, tmp2, count, i);
	i = 0;
	count = unsetenv1returncount(pl->envprinc, string, count, i);
	tmp1 = unsettaballoc(pl->envprinc, tmp1, count);
	i = 0;
	tmp1 = remplirtableunset(pl->envprinc, tmp1, count, i);
	free_pre(pl->env1, 0);
	free_pre(pl->envprinc, 0);
	free(tmp);
	pl->env1 = tmp2;
	pl->envprinc = tmp1;
}
