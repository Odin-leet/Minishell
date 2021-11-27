/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aali-mou <aali-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 09:27:51 by aali-mou          #+#    #+#             */
/*   Updated: 2021/11/27 23:42:26 by aali-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <dirent.h>

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

void	handlesig(int sig)
{
	if (g_gl.herdo == 0)
	{
		if (sig == SIGINT)
		{
			if (g_gl.isin == 1)
			{
				write(1, "\n", 1);
				g_gl.isin = 0;
			}
			else
			{
				write(1, "\n", 1);
				rl_on_new_line();
				rl_replace_line("", 0);
				rl_redisplay();
				g_gl.status = 1;
			}
		}
		if (sig == SIGQUIT)
		{
			if (g_gl.isin)
				write(2, "Quit: 3\n", 8);
			else
			{
				rl_on_new_line();
				rl_redisplay();
			}
		}
	}
}

int	funmain22(t_vars *v, char **split, char *buffer)
{
	t_linked_list	*head1;
	t_linked_list	*parseur;
	t_file			*file;
	t_linked_list	*head;

	while (1)
	{
		head = NULL;
		parseur = NULL;
		buffer = readline("Minishell 0.0$ ");
		add_history(buffer);
		if (buffer == NULL)
		{
			printf("exit\n");
			exit(1);
		}
		if (buffer[0] != '\0' && (checkspace(buffer) == 1))
		{
			g_gl.isin = 1;
			split = ft_split(buffer, ' ');
			head = mainhelper3(split);
			if (check_errors(head) != 0)
			{
				parseur = parser(head, v->envprinc);
				if (parseur == NULL)
					free_files_linked(head);
				else
					free_head2(head);
				exec(parseur, v);
				free(split);
				free_lin_command(parseur);
			}
			else
			{
				head1 = head;
				while (head1)
				{
					file = (t_file *)head1->data;
					head1 = head1->next;
				}
				free_files_linked(head);
				free(split);
			}
		}
		if (buffer)
			free(buffer);
	}
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	char	*buffer;
	char	**split;
	t_vars	v;

	get_env(&v, env);
	argc = 2;
	buffer = NULL;
	g_gl.status = 0;
	split = NULL;
	argc = 0;
	argv = NULL;
	g_gl.isin = 0;
	g_gl.herdo = 0;
	signal(SIGINT, handlesig);
	signal(SIGQUIT, handlesig);
	if (funmain22(&v, split, buffer) == 0)
		return (0);
	free_pre(v.env1, 0);
	free_pre(v.envprinc, 0);
	return (0);
}
