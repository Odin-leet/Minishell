/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashite <ashite@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 01:20:01 by ashite            #+#    #+#             */
/*   Updated: 2021/11/28 01:27:45 by ashite           ###   ########.fr       */
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
