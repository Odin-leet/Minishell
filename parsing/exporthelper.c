/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exporthelper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aali-mou <aali-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 01:41:15 by aali-mou          #+#    #+#             */
/*   Updated: 2021/11/28 01:41:42 by aali-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isalpha2(int c)
{
	unsigned char	k;

	k = (unsigned char)c;
	if (c <= 90 && c >= 65)
		return (1);
	else if (c >= 97 && c <= 122)
		return (1);
	else
		return (0);
}

int	returncount(char *string, char *tmp, int i, int j)
{	
	int	count;

	i = 0;
	count = 0;
	j = 0;
	if (strchr(string, '=') != NULL)
	{
		while (tmp[j])
		{
			if (tmp[j] == '=')
			{
				count = j;
				break ;
			}
			j++;
		}
	}
	else
		count = ft_strlen(tmp);
	return (count);
}

int	helpercount(char **env, int count2, int j, int i)
{
	while (env[i][j] != '\0')
	{
		if (env[i][j] == '=')
		{
			count2 = j;
			break ;
		}
		j++;
	}
	return (count2);
}

int	returnthereisenv(int count, int count2, char **env, char *tmp)
{
	int	i;
	int	j;
	int	count3;

	i = 0;
	j = 0;
	count3 = count;
	while (env[i] != NULL)
	{
		j = 0;
		count3 = count;
		helpercount(env, count2, j, i);
		if (env[i][j] == '\0')
			count2 = j;
		if (count2 > count)
			count3 = count2;
		if (strncmp(tmp, env[i], count3) == 0)
		{
			free(tmp);
			return (1);
		}
		i++;
	}
	return (0);
}

int	checkifthereisenv(char **env, char *string)
{
	int		i;
	int		count;
	int		count2;
	int		j;
	char	*tmp;

	count2 = 0;
	tmp = NULL;
	i = 0;
	tmp = ft_strjoin("declare -x ", string);
	j = 0;
	count = returncount(string, tmp, i, j);
	if (returnthereisenv(count, count2, env, tmp) == 1)
		return (1);
	free(tmp);
	return (0);
}
