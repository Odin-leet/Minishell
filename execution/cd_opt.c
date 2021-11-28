/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_opt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashite <ashite@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 01:17:05 by ashite            #+#    #+#             */
/*   Updated: 2021/11/28 01:18:58 by ashite           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cdtier(t_vars *v)
{
	int		i;
	int		count;
	int		j;

	i = 0;
	j = 1;
	count = 0;
	while (v->collected_cmd[j][i])
	{
		while (v->collected_cmd[j][i])
		{
			if (v->collected_cmd[j][i] == '-' &&
			v->collected_cmd[j][i + 1] == '\0')
				return (cdback(v));
			else if (v->collected_cmd[j][i] == '-' &&
			v->collected_cmd[j][i + 1] == '-')
				return (cdhome(v));
			i++;
		}
		j++;
	}
	write(2, "bash: cd: -d: invalid option\ncd: usage: cd [-L|-P] [dir]\n", 58);
	return (cd_cleanup(v, 1));
}

int	cd_moja(t_vars *v)
{
	char	*dir;
	char	*tmp;
	int		ret;

	ret = 0;
	dir = v->home;
	if (v->collected_cmd[1][1] != '\0' && v->home)
	{
		tmp = ft_strtrim(v->collected_cmd[1], "~");
		dir = ft_strjoin(dir, tmp);
		free(tmp);
		ret = change_dir(v, dir);
		free(dir);
	}
	else
		ret = change_dir(v, dir);
	return (ret);
}
