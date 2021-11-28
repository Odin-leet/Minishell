/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aali-mou <aali-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 09:27:51 by aali-mou          #+#    #+#             */
/*   Updated: 2021/11/28 02:39:32 by aali-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <dirent.h>

void	parserndexecute(t_vars *v, t_linked_list *head, t_linked_list *parseur)
{
	parseur = parser(head, v->envprinc);
	if (parseur == NULL)
		free_files_linked(head);
	else
		free_head2(head);
	exec(parseur, v);
	free(v->split);
	free_lin_command(parseur);
}

void	passtoanewcommand(t_linked_list *head, t_vars *v)
{
	t_linked_list	*head1;
	t_file			*file;

	head1 = head;
	while (head1)
	{
		file = (t_file *)head1->data;
		head1 = head1->next;
	}
	free_files_linked(head);
	free(v->split);
}

void	anonvoidline(t_vars *v, char *buffer, t_linked_list *head,
			t_linked_list *parseur)
{
	g_gl.isin = 1;
	v->split = ft_split(buffer, ' ');
	head = mainhelper3(v->split);
	if (check_errors(head) != 0)
		parserndexecute(v, head, parseur);
	else
		passtoanewcommand(head, v);
}

int	mainwhile(t_vars *v, char *buffer)
{
	t_linked_list	*parseur;
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
			anonvoidline(v, buffer, head, parseur);
		}
		if (buffer)
			free(buffer);
	}
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	char	*buffer;
	t_vars	v;

	get_env(&v, env);
	argc = 2;
	buffer = NULL;
	g_gl.status = 0;
	v.split = NULL;
	argc = 0;
	argv = NULL;
	g_gl.isin = 0;
	g_gl.herdo = 0;
	signal(SIGINT, handlesig);
	signal(SIGQUIT, handlesig);
	if (mainwhile(&v, buffer) == 0)
		return (0);
	free_pre(v.env1, 0);
	free_pre(v.envprinc, 0);
	return (0);
}
