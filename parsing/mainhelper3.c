/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainhelper3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aali-mou <aali-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 09:27:37 by aali-mou          #+#    #+#             */
/*   Updated: 2021/11/27 18:50:15 by aali-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	checkforpipe(char *s)
{
	int	i;
	int	*in_db;
	int	*in_sgl;

	in_db = traitmask(s, 1);
	in_sgl = traitmask(s, 0);
	i = 0;
	while (s[i] != '\0')
	{
		if ((s[i] == '|' || s[i] == '<' || s[i] == '>')
			&& in_db[i] == 0 && in_sgl[i] == 0)
		{
			free(in_db);
			free(in_sgl);
			return (1);
		}
		i++;
	}
	free(in_db);
	free(in_sgl);
	return (0);
}

int	check_errors3(int j, char *string)
{
	if (j > 2 && strlen(string) > 2)
	{
		printf("error here %s \n", string);
		return (0);
	}
	else if (j == 1 && strlen(string) > 1)
	{
		printf("error here %s \n", string);
		return (0);
	}
	else if (j == 2 && strlen(string) > 2)
	{
		printf("error here %s \n", string);
		return (0);
	}
	return (1);
}

int	check_errors2(int j, int i, char *string)
{
	if (i == 2)
	{
		if (j > 1 && strlen(string) > 1)
		{
			printf("error here %s \n", string);
			return (0);
		}
	}
	else
	{
		if (check_errors3(j, string) == 0)
			return (0);
	}
	return (1);
}

void	storeinfos(char *string, t_linked_list **head)
{
	t_file	*file2;
	int		type;

	type = 0;
	file2 = (t_file *)malloc(sizeof(t_file));
	type = findtype(string);
	file2->file = string;
	file2->type = type;
	append(head, file2);
}
