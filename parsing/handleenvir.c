/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleenvir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aali-mou <aali-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 09:27:07 by aali-mou          #+#    #+#             */
/*   Updated: 2021/11/27 09:27:08 by aali-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <string.h>

char	*replaceenv3(char *string, char **env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], string, ft_strlen(string)) == 0)
		{
			j = 1;
			break ;
		}
		else
			i++;
	}
	if (j == 1)
	{
		j = ft_strlen(string);
		free(string);
		return (ft_strdup(env[i], j));
	}
	return (NULL);
}

char	*replaceenv2(char *string, int start, int end, char **env)
{
	char	*tmp;

	tmp = NULL;
	if (end == 0)
		end = ft_strlen(string);
	tmp = string;
	string = ft_substr(string, start + 1, (end - 1) - start);
	free(tmp);
	tmp = string;
	string = ft_strjoin(string, "=");
	free(tmp);
	tmp = NULL;
	string = replaceenv3(string, env);
	return (string);
}

char	*handleemvir3(char *string, char *tmp, char *tmp2)
{
	if (tmp != NULL && tmp2 != NULL)
		string = ft_strjoin(tmp, tmp2);
	else if (tmp != NULL && tmp2 == NULL)
		string = ft_strdup(tmp, 0);
	else
		string = ft_strdup(tmp2, 0);
	return (string);
}

char	*handleenvir2(char *string, char *tmp, char *tmp2)
{
	char	*tmp3;

	if (tmp != NULL && string != NULL)
	{
		tmp3 = string;
		string = ft_strjoin(tmp, string);
		free(tmp3);
	}
	if (tmp2 != NULL && string != NULL)
	{
		tmp3 = string;
		string = ft_strjoin(string, tmp2);
		free(tmp3);
	}
	if (string == NULL)
		string = handleemvir3(string, tmp, tmp2);
	if (tmp2 != NULL)
		free(tmp2);
	if (tmp)
		free(tmp);
	return (string);
}

char	*checkingforendofaenv(char *string, char *tmp2, int *i, int *end)
{
	(*i)++;
	while (string[*i] != '\0')
	{
		if (string[*i] != '_' && (ft_isdigit(string[*i]) == 0)
			&& (ft_isalpha2(string[*i]) == 0) && string[*i] != '?')
		{
			*end = *i;
			tmp2 = ft_substr(string, *end, ft_strlen(string) - *end);
			return (tmp2);
		}
		else
			(*i)++;
	}
	return (NULL);
}

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

char	*handleenvir(char *string, char **env)
{
	int	i;
	int	start;

	start = 0;
	i = 0;
	while (string[i] != '\0')
	{
		if (string[i] == '\'')
			return (string);
		if (string[i] == '$')
		{
			if (i != 0)
				start = i;
			i++;
			if (string[i] >= 48 && string[i] <= 57)
				return (ft_substr(string, i + 1, ft_strlen(string) - (i + 1)));
			else if (string[i] == '_' || (string[i] >= 65 && string[i] <= 90)
				|| (string[i] >= 97 && string[i] <= 123) || string[i] == '?')
				return (string = handleenvir1(string, i, start, env));
		}
		i++;
	}
	return (string);
}
