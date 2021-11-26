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

	str = ft_strjoin(s, join);
	replaceenv(v, str);
	free(str);
	str = NULL;
}

int	befree(t_vars *v, int status, int i)
{
	if (status == 0)
	{
		if (v->home != NULL)
			free(v->home);
		if (v->oldpwd != NULL)
			free(v->oldpwd);
		if (v->curr != NULL)
			free(v->curr);
		v->home = NULL;
		v->oldpwd = NULL;
		v->curr = NULL;
	}
	if (status == 1)
	{
		printf("bash: cd: OLDPWD not set\n");
		return (1);
	}
	if (status == 2)
	{
		printf("bash: cd: -d: invalid option\ncd: usage: cd [-L|-P] [dir]\n");
		return (1);
	}
	else if (status < 0)
		printf("No such file or directory\n");
	return (i);
}

int	cdtier(t_vars *v)
{
	int	i;
	int	ret;

	i = 0;
	while (v->collected_cmd[1][i])
	{
		if (v->collected_cmd[1][i] != '-' && \
			v->collected_cmd[1][i] != '\0')
			return (befree(v, 2, 1));
		i++;
	}
	if (!v->oldpwd)
		return (befree(v, 1, 1));
	ret = chdir(v->oldpwd);
	setevars("PWD=", v->oldpwd, v);
	setevars("OLDPWD=", v->curr, v);
	return (befree(v, 0, 0));
}

void	cd_init(t_vars *v)
{
	v->home = exportenv(v, "HOME");
	v->oldpwd = exportenv(v, "OLDPWD");
	v->curr = exportenv(v, "PWD");
}

void	cd_moja(t_vars *v, char **tmp, char **cwd)
{
	char	*str;

	str = ft_strtrim(v->collected_cmd[1], "~");
	*tmp = ft_strjoin(v->home, str);
	free(str);
	if (*tmp[0] != '/')
		strcat(*cwd, "/");
	strcat(*cwd, *tmp);
	free(*tmp);
}

int	cd_extention(t_vars *v, char **cwd)
{
	char	*tmp;
	int		i;

	tmp = v->collected_cmd[1];
	if (tmp[0] == '-')
		return (cdtier(v));
	else if (tmp[0] == '~')
		cd_moja(v, &tmp, cwd);
	else
	{
		getcwd(*cwd, PATH_MAX);
		if (v->collected_cmd[1][0] != '/')
			strcat(*cwd, "/");
		strcat(*cwd, tmp);
	}	
	i = 2;
	while (v->collected_cmd[i])
	{
		strcat(*cwd, " ");
		strcat(*cwd, v->collected_cmd[i++]);
	}
	return (0);
}

int	cd(t_vars *v)
{
	char	*cwd;
	int		ret;

	cwd = ft_calloc(1, sizeof(char) * PATH_MAX);
	cd_init(v);
	if (!v->collected_cmd[1])
		cwd = strcat(cwd, v->home);
	else if (v->collected_cmd[1])
	{
		//ret = 100;
		ret = cd_extention(v, &cwd);
	//printf("%d\n", cwd);
		if (ret != 0)
			return (ret);
	}
	ret = chdir(cwd);
	if (ret == 0)
	{
		setevars("OLDPWD=", v->curr, v);
		setevars("PWD=", cwd, v);
		free(cwd);
		cwd = NULL;
		return (befree(v, 0, 0));
	}
	free(cwd);
	return (befree(v, 0, 1));
}
