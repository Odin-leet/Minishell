/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashite <ashite@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 01:18:23 by ashite            #+#    #+#             */
/*   Updated: 2021/11/28 01:19:02 by ashite           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	setevars(char *s, char *join, t_vars *v)
{
	char	*str;

	if (s)
		str = ft_strjoin(s, join);
	else
		str = join;
	replaceenv(v, str);
	free(str);
	str = NULL;
}

int	cd_cleanup(t_vars *v, int ret)
{
	if (v->oldpwd)
		free(v->oldpwd);
	if (v->home)
		free(v->home);
	if (v->curr)
		free(v->curr);
	v->oldpwd = NULL;
	v->home = NULL;
	v->curr = NULL;
	return (ret);
}

int	change_dir(t_vars *v, char *dir)
{
	int	ret;

	if (dir)
	{
		ret = chdir(dir);
		if (ret == 0)
		{
			setevars("PWD=", dir, v);
			if (v->curr)
				setevars("OLDPWD=", v->curr, v);
			return (cd_cleanup(v, 0));
		}
		write(2, "No such file or directory\n", 27);
		return (cd_cleanup(v, 1));
	}
	else
	{
		write(2, "No such file or directory\n", 27);
		return (cd_cleanup(v, 1));
	}
}

int	cdback(t_vars *v)
{
	if (v->oldpwd)
		return (change_dir(v, v->oldpwd));
	else
	{
		write(2, "Minishell: cd: OLDPWD not set\n", 31);
		return (cd_cleanup(v, 1));
	}
}

int	cdhome(t_vars *v)
{
	if (v->home)
		return (change_dir(v, v->home));
	else
	{
		write(2, "Minishell: cd: HOME not set\n", 29);
		return (cd_cleanup(v, 1));
	}
}
