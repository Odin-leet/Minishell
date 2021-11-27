/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collecter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aali-mou <aali-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 17:30:42 by aali-mou          #+#    #+#             */
/*   Updated: 2021/11/27 21:09:02 by aali-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**cmd_collector(t_linked_list *cmd)
{
	char			**sequance;
	t_linked_list	*tempo;
	int				size;

	size = 0;
	tempo = cmd;
	while (tempo != NULL)
	{
		tempo = tempo->next;
		size++;
	}
	sequance = malloc(sizeof(char *) * (size + 1));
	sequance[size] = NULL;
	size = 0;
	while (cmd != NULL)
	{
		sequance[size] = ft_strdup((char *)cmd->data, 0);
        checkforquotes(&sequance[size]);
		cmd = cmd->next;
		size++;
	}
	return (sequance);
}

char	**files_collector(t_linked_list *lfile)
{
	char			**sequance;
	t_linked_list	*tempo;
	int				size;

	size = 0;
	tempo = lfile;
	while (tempo != NULL)
	{
		tempo = tempo->next;
		size++;
	}
	sequance = malloc(sizeof(char *) * (size + 1));
	sequance[size] = NULL;
	size = 0;
	while (lfile != NULL)
	{
		sequance[size] = ft_strdup(((t_file *)lfile->data)->file, 0);
		lfile = lfile->next;
		size++;
	}
	return (sequance);
}

int	*type_collector(t_linked_list *lfile)
{
	int				*tab;
	t_linked_list	*tempo;
	int				size;

	size = 0;
	tempo = lfile;
	while (tempo != NULL)
	{
		tempo = tempo->next;
		size++;
	}
	tab = malloc(sizeof(int *) * (size));
	size = 0;
	while (lfile != NULL)
	{
		tab[size] = ((t_file *)lfile->data)->type;
		lfile = lfile->next;
		size++;
	}
	return (tab);
}

int	ft_atoi(const char *str)
{
	long long	nbr;
	int			i;
	int			s;

	i = 0;
	nbr = 0;
	s = 1;
	while (str[i] == 32 || (str[i] < 14 && str[i] > 8))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			s = -1;
	}
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + (str[i++] - '0');
		if (nbr > 4294967295)
		{
			return (-1);
		}
	}
	return (nbr * s);
}

char	*exportenv(t_vars *pl, char *string)
{
	int	i;
	int	count;
	int	c;

	i = 0;
	while (pl->envprinc[++i] != NULL)
	{
		count = ft_strlen(string);
		c = thereisequ(pl->envprinc[i]);
		if (c != -1)
		{
			if (count < c)
				count = c;
		}
		else
		{
			c = ft_strlen(pl->envprinc[i]);
			if (count < c)
				count = c;
		}
		if (strncmp(pl->envprinc[i], string, count) == 0)
			return (ft_substr(pl->envprinc[i], count + 1,
					ft_strlen(pl->envprinc[i]) - count));
	}
	return (NULL);
}
