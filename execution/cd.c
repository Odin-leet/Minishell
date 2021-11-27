/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashite <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 11:25:30 by ashite            #+#    #+#             */
/*   Updated: 2021/11/05 11:25:35 by ashite           ###   ########.fr       */
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

int cd_cleanup(t_vars *v, int ret)
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

int	change_dir(t_vars *v, char* dir)
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
			return (cd_cleanup(v,0));
		}
		write(2, "No such file or directory\n", 27);
		return (cd_cleanup(v,1));
	}
	else
	{
		write(2, "No such file or directory\n", 27);
		return (cd_cleanup(v,1));
	}
}

int cdback(t_vars *v)
{
	if (v->oldpwd)
		return (change_dir(v,v->oldpwd));
	else
	{
		write(2, "Minishell: cd: OLDPWD not set\n", 31);
		return (cd_cleanup(v,1));
	}
}

int cdhome(t_vars *v)
{
	if (v->home)
		return (change_dir(v,v->home));
	else
	{
		write(2, "Minishell: cd: HOME not set\n", 29);
		return (cd_cleanup(v,1));
	}
}

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
			if (v->collected_cmd[j][i] == '-' && v->collected_cmd[j][i + 1] == '\0')
				return (cdback(v));
			else if(v->collected_cmd[j][i] == '-' && v->collected_cmd[j][i + 1] == '-')
				return (cdhome(v));
			i++;
		}
		j++;
	}
	write(2, "bash: cd: -d: invalid option\ncd: usage: cd [-L|-P] [dir]\n", 58);
	return (cd_cleanup(v, 1));
}

void	cd_init(t_vars *v)
{
	v->home = exportenv(v, "HOME");
	v->oldpwd = exportenv(v, "OLDPWD");
	v->curr = exportenv(v, "PWD");
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

int	cd_extention(t_vars *v, char **cwd)
{
	char	*tmp;
	int		i;

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
