/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aali-mou <aali-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 11:25:30 by ashite            #+#    #+#             */
/*   Updated: 2021/11/27 17:41:25 by aali-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_fucking_status(int status)
{
	if (WIFEXITED(status) == 1)
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status) == 1 && g_gl.failed < 0)
		return (128 + WTERMSIG(status));
	else if (g_gl.failed > 0 && WIFSIGNALED(status) == 1)
		return (1);
	return (0);
}

void	pid_manager(t_vars *v)
{
	int	i;

	i = 0;
	while (i < v->cmd_size)
		waitpid(v->pid[i++], &g_gl.status, 0);
	if (g_gl.status > 255)
		g_gl.status = g_gl.status % 255;
	else
		g_gl.status = get_fucking_status(g_gl.status);
	free(v->pid);
}

void	execinitialisation(t_vars **v)
{
	if ((*v)->collected_files)
		free_pre((*v)->collected_files, 0);
	if ((*v)->collected_type)
		free((*v)->collected_type);
	if ((*v)->collected_cmd)
		free_pre((*v)->collected_cmd, 0);
		(*v)->collected_files = NULL;
		(*v)->collected_files = NULL;
		(*v)->collected_cmd = NULL;
}

void	execinistia2(t_vars **v)
{
	(*v)->collected_files = NULL;
	(*v)->collected_files = NULL;
	(*v)->collected_cmd = NULL;
}

void	exec(t_linked_list *head, t_vars *v)
{
	int	fd[2];
	int	i;

	i = 0;
	g_gl.status = exec_initializer(v, head);
	while (head && g_gl.herdoc == 0)
	{
		v->lcmd = ((t_command *)head->data)->nameargs;
		v->lfile = ((t_command *)head->data)->files;
		v->collected_type = type_collector(v->lfile);
		v->collected_files = files_collector(v->lfile);
		v->collected_cmd = cmd_collector(v->lcmd);
		pipe(fd);
		v->pin = fd[0];
		v->out = fd[1];
		if (!(head->next))
			v->out = 1;
		executer(head, v, i);
		i++;
		head = head->next;
		execinitialisation(&v);
	}
	pid_manager(v);
	g_gl.isin = 0;
}
