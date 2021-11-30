/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainhelper1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aali-mou <aali-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 09:27:24 by aali-mou          #+#    #+#             */
/*   Updated: 2021/11/27 09:27:25 by aali-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	mainhelperhelper2(int i, char *string, int c, t_linked_list **head)
{
	int	j;
	int	*in_db;
	int	*in_sgl;

	in_db = traitmask(string, 1);
	in_sgl = traitmask(string, 0);
	j = 0;
	while (((string[i] == '>' || string[i] == '<' || string[i] == '|')
			&& in_sgl[i] == 0 && in_sgl[i] == 0) && string[i] != '\0')
	{
		j++;
		i++;
		if (string[i] != '|' && string[i] != '>' && string[i] != '<')
		{	
			storeinfos(ft_substr(string, c, j), head);
			break ;
		}
	}
	free(in_db);
	free(in_sgl);
	return (i);
}

int	mainhelperhelper1(int i, char *string, t_linked_list **head)
{
	int	t;
	int	*in_db;
	int	*in_sgl;

	t = 0;
	in_db = traitmask(string, 1);
	in_sgl = traitmask(string, 0);
	t = i;
	if (string)
	{
		while (string[i] != '\0' && ((in_db[i] == 1 || in_sgl[i] == 1)
				|| (string[i] != '|' && string[i] != '>' && string[i] != '<')))
			i++;
	}
	if (i != 0)
		storeinfos(ft_substr(string, t, i - t), head);
	free(in_db);
	free(in_sgl);
	return (i);
}

int	mainhelper(char *string, int j, t_linked_list **head)
{
	char	*pip;
	int		i;
	int		c;

	pip = ft_strdup("|", 0);
	c = 0;
	i = 0;
	j = 0;
	while (string[i] != '\0')
	{
		i = mainhelperhelper1(i, string, head);
		c = i;
		i = mainhelperhelper2(i, string, c, head);
	}
	if (c == -1)
		storeinfos(pip, head);
	free(pip);
	return (1);
}
