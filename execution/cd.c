/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashite <ashite@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 11:25:30 by ashite            #+#    #+#             */
/*   Updated: 2021/11/28 01:18:08 by ashite           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd_init(t_vars *v)
{
	v->home = exportenv(v, "HOME");
	v->oldpwd = exportenv(v, "OLDPWD");
	v->curr = exportenv(v, "PWD");
}

int	cd_extention(t_vars *v, char **cwd)
{
	char	*tmp;
	int		i;

	checkforquotes(&v->collected_cmd[1]);
	tmp = v->collected_cmd[1];
	if (tmp[0] == '-')
		return (cdtier(v));
	else if (tmp[0] == '~')
		return (cd_moja(v));
	else if (v->collected_cmd[1][0] == '/')
		return (change_dir(v, v->collected_cmd[1]));
	else
	{
		getcwd(*cwd, PATH_MAX);
		strcat(*cwd, "/");
		strcat(*cwd, tmp);
		i = 2;
		while (v->collected_cmd[i])
		{
			strcat(*cwd, " ");
			checkforquotes(&v->collected_cmd[i]);
			strcat(*cwd, v->collected_cmd[i++]);
		}
		return (change_dir(v, *cwd));
	}
}

int	cd(t_vars *v)
{
	char	*cwd;
	int		ret;

	cwd = ft_calloc(1, sizeof(char) * PATH_MAX);
	cd_init(v);
	if (!v->collected_cmd[1])
		ret = cdhome(v);
	else
		ret = cd_extention(v, &cwd);
	free(cwd);
	return (ret);
}
