/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aali-mou <aali-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 02:38:26 by aali-mou          #+#    #+#             */
/*   Updated: 2021/11/28 02:45:46 by aali-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	append(t_linked_list **head_ref, void *data)
{
	t_linked_list	*new_node;
	t_linked_list	*last;

	last = *head_ref;
	new_node = (t_linked_list *)malloc(sizeof(t_linked_list));
	new_node->data = (void *)data;
	new_node->next = NULL;
	if (*head_ref == NULL)
	{
		*head_ref = new_node;
		return ;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = new_node;
	return ;
}

void	*free_pre(char **split, int k)
{
	if (split)
	{
		while (split[k])
		{
			free(split[k]);
			split[k] = NULL;
			k++;
		}
		free(split);
		split = NULL;
	}
	return (NULL);
}

int	findtype(char *s)
{
	if (ft_strncmp(s, "|", ft_strlen(s)) == 0)
		return (1);
	if (ft_strncmp(s, "<", ft_strlen(s)) == 0)
		return (2);
	if (ft_strncmp(s, ">", ft_strlen(s)) == 0)
		return (3);
	if (ft_strncmp(s, ">>", ft_strlen(s) + 1) == 0)
		return (4);
	if (ft_strncmp(s, "<<", ft_strlen(s) + 1) == 0)
		return (5);
	return (0);
}

int	checkspace(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i] != '\0')
	{
		if (buffer[i] == ' ')
			i++;
		else
			return (1);
	}
	return (0);
}

void	else1(t_file *token, char **env, t_command **command)
{
	token->file = (void *)handleenvir((char *)token->file, env);
	append(&((*command)->nameargs), (void *)token->file);
}
