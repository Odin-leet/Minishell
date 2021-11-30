/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainhelper22.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashite <ashite@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 05:58:54 by ashite            #+#    #+#             */
/*   Updated: 2021/11/28 06:03:22 by ashite           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	mainhelper2(int j, int i, t_linked_list **head, char *string)
{
	if (j > 1)
	{
		printf("error here \n");
		return (0);
	}
	if (string[i] != '\0')
		storeinfos(ft_substr(string, i, strlen(string) - i), head);
	return (1);
}

t_linked_list	*mainhelper3(char **split)
{
	int				n;
	int				j;
	t_linked_list	*head;

	n = 0;
	head = NULL;
	j = 0;
	while (split[n] != NULL)
	{
		if (checkforpipe(split[n]) == 1)
		{
			mainhelper(split[n], j, &head);
			free(split[n]);
		}
		else
		{
			storeinfos(split[n], &head);
		}
		n++;
	}
	return (head);
}
