/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handelenvtab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aali-mou <aali-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 09:26:55 by aali-mou          #+#    #+#             */
/*   Updated: 2021/11/27 09:26:56 by aali-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	thereisequ(char *env)
{
	int	i;

	i = 0;
	while (env[i] != '\0')
	{
		if (env[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

char	*traitement1helper(char *tmp1, char *tmp2, char *str2)
{
	char	*tmp3;

	tmp3 = tmp2;
	tmp2 = ft_strjoin(str2, tmp2);
	free(tmp3);
	tmp3 = tmp2;
	tmp2 = ft_strjoin(tmp2, str2);
	free(tmp3);
	tmp3 = tmp2;
	tmp2 = ft_strjoin(tmp1, tmp2);
	free(tmp3);
	free(tmp1);
	return (tmp2);
}

char	*traitement1(char *str, int j)
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;
	char	*str2;

	str2 = malloc(sizeof(char) * 2);
	str2[0] = '\"';
	str2[1] = '\0';
	tmp1 = ft_substr(str, 0, j + 1);
	tmp2 = ft_substr(str, j + 1, ft_strlen(str) - (j + 1));
	tmp3 = traitement1helper(tmp1, tmp2, str2);
	tmp2 = ft_strjoin("declare -x ", tmp3);
	free(tmp3);
	free(str2);
	return (tmp2);
}

char	*traitement2(char *str)
{
	char	*tmp;

	tmp = ft_strjoin("declare -x ", str);
	return (tmp);
}

char	**transferenv(char **tmp)
{
	int		i;
	int		j;
	char	**tmp1;

	i = 0;
	tmp1 = NULL;
	j = 0;
	while (tmp[i])
		i++;
	tmp1 = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (tmp[i] != NULL)
	{
		j = thereisequ(tmp[i]);
		if (j != -1)
			tmp1[i] = traitement1(tmp[i], j);
		else
			tmp1[i] = traitement2(tmp[i]);
		i++;
	}
	tmp1[i] = NULL;
	return (tmp1);
}

void	get_env1(char **env, t_vars *pl)
{
	int	i;
	int	j;

	i = 0;
	while (env[i] != NULL)
	{
		j = 0;
		while (env[i][j] != '\0')
		{
			pl->envprinc[i][j] = env[i][j];
			j++;
		}
		pl->envprinc[i][j] = '\0';
		i++;
	}
	pl->envprinc[i] = NULL;
	pl->env1 = transferenv(pl->envprinc);
}

void	get_env(t_vars *pl, char **env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[i] != NULL)
		i++;
	pl->envprinc = malloc(sizeof (char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		j = 0;
		j = ft_strlen(env[i]);
		pl->envprinc[i] = malloc(sizeof(char) * (j + 1));
		i++;
	}
	get_env1(env, pl);
}
