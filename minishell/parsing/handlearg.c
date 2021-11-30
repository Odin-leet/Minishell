/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlearg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aali-mou <aali-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 09:27:02 by aali-mou          #+#    #+#             */
/*   Updated: 2021/11/28 02:25:08 by aali-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtins(char *string)
{
	if (ft_strncmp(string, "echo", ft_strlen(string)) == 0)
		return (1);
	if (ft_strncmp(string, "cd", ft_strlen(string)) == 0)
		return (1);
	if (ft_strncmp(string, "pwd", ft_strlen(string)) == 0)
		return (1);
	if (ft_strncmp(string, "unset", ft_strlen(string)) == 0)
		return (1);
	if (ft_strncmp(string, "env", ft_strlen(string)) == 0)
		return (1);
	if (ft_strncmp(string, "exit", ft_strlen(string)) == 0)
		return (1);
	if (ft_strncmp(string, "export", ft_strlen(string)) == 0)
		return (1);
	return (0);
}

char	*checkforpath(char *string, char *str)
{
	DIR				*dir;
	struct dirent	*sd;

	dir = opendir(string);
	if (dir == NULL)
	{
		printf("there is no file\n");
		return (0);
	}
	sd = readdir(dir);
	while (sd != NULL && str[0] != '\0')
	{
		if (strncmp(sd->d_name, str, ft_strlen(sd->d_name)) == 0)
		{
			(void)closedir(dir);
			return (string);
		}
		sd = readdir(dir);
	}
	(void)closedir(dir);
	return (NULL);
}

int	thereisslach(char *string)
{
	int	i;

	i = 0;
	while (string[i] != '\0')
	{
		if (string[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

char	*elsefunctionhelper(char *string, char **tab, int i, char *tmp)
{
	char	*tmp3;
	char	*tmp2;

	tmp3 = NULL;
	tmp2 = NULL;
	tmp2 = checkforpath(tab[i], string);
	if (tmp2 != NULL)
	{
		tmp3 = tab[i];
		tab[i] = ft_strjoin(tab[i], "/");
		free(tmp3);
		tmp3 = ft_strjoin(tab[i], string);
		free_pre(tab, 0);
		free(tmp);
		free(string);
		return (tmp3);
	}
	if (!(tmp2))
		free(tmp2);
	return (NULL);
}

int	findenvi(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (i);
		i++;
	}
	return (-1);
}
