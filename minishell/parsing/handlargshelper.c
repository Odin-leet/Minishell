/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlargshelper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aali-mou <aali-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 02:25:11 by aali-mou          #+#    #+#             */
/*   Updated: 2021/11/28 02:32:16 by aali-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*elsefunctionhelper2(char *tmp, char *string, char **env, int i)
{
	i = 0;
	i = findenvi(env);
	if (i != -1)
		tmp = ft_strdup(env[i], 5);
	else
	{
		printf("bash: %s: No such file or directory \n", string);
		free(string);
		return (NULL);
	}
	return (tmp);
}

char	*elsefunction(char *string, char **env)
{
	int		i;
	char	*tmp;
	char	**tab;
	char	*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	i = 0;
	tmp = elsefunctionhelper2(tmp, string, env, i);
	if (tmp == NULL)
		return (0);
	tab = ft_split1(tmp, ':');
	i = 0;
	while (tab[i] != NULL)
	{
		tmp2 = elsefunctionhelper(string, tab, i, tmp);
		if (tmp2 != NULL)
			return (tmp2);
		i++;
	}
	free_pre(tab, 0);
	free(tmp);
	return (string);
}

char	*handleargshelper(char *string, int j, char *ptr, char *ptr2)
{
	int	i;

	i = 0;
	while (string[i] != '\0')
	{
		if (string[i] == '/')
			j = i;
		i++;
	}
	ptr = ft_substr(string, 0, j);
	ptr2 = ft_strdup(string, j + 1);
	if (checkforpath(ptr, ptr2) == NULL)
	{
		free(ptr);
		free(ptr2);
		return (string);
	}
	free(ptr2);
	free(ptr);
	return (string);
}

char	*handleargs(char *string, char **env)
{
	char	*ptr;
	char	*ptr2;
	int		j;

	j = 0;
	ptr = NULL;
	ptr2 = NULL;
	if (string)
	{
		if (builtins(string) == 1)
			return (string);
		else if (thereisslach(string) == 1)
			string = handleargshelper(string, j, ptr, ptr2);
		else
			string = elsefunction(string, env);
	}
	return (string);
}
