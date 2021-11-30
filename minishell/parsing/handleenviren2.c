/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleenviren2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aali-mou <aali-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 02:17:04 by aali-mou          #+#    #+#             */
/*   Updated: 2021/11/28 02:56:28 by aali-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*handleenvir1(char *string, int i, int start, char **env)
{
	char	*tmp2;
	int		end;
	char	*tmp;
	char	*tmp3;

	tmp2 = NULL;
	tmp = NULL;
	if (start != 0)
		tmp = ft_substr(string, 0, start);
	end = 0;
	tmp2 = checkingforendofaenv(string, tmp2, &i, &end);
	if ((end != 0 && string[end - 1] == '?')
		|| (end == 0 && string[i - 1] == '?'))
	{
		tmp3 = string;
		string = handleenvir2(ft_itoa(g_gl.status), tmp, tmp2);
		free(tmp3);
	}
	else
	{
	string = replaceenv2(string, start, end, env);
	string = handleenvir2(string, tmp, tmp2);
	}
	return (string);
}

char	*handlstring_izero(char *string, int start, char **env, int *i)
{
	char	*str;

	str = handleenvir1(string, *i, start, env);
	*i = 0;
	return (str);
}

char	*handleenvir(char *string, char **env)
{
	int	i;
	int	start;

	start = 0;
	i = 0;
	while (string && string[i] != '\0')
	{
		if (string[i] == '\'')
			return (string);
		if (string[i] == '$' && string[i + 1] != '\0' )
		{
			if (i != 0)
				start = i;
			i++;
			if (string[i] >= 48 && string[i] <= 57)
				return (ft_substr(string, i + 1, ft_strlen(string) - (i + 1)));
			else if (string[i] == '_' || (string[i] >= 65 && string[i] <= 90)
				|| (string[i] >= 97 && string[i] <= 123) || string[i] == '?')
				string = handlstring_izero(string, start, env, &i);
		}
		i++;
	}
	return (string);
}

void	free_files_linked2(t_linked_list *files)
{
	if (!files)
		return ;
	free(((t_file *)(files->data))->file);
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
