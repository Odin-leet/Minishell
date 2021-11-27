/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aali-mou <aali-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 17:33:43 by aali-mou          #+#    #+#             */
/*   Updated: 2021/11/27 17:42:55 by aali-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	children(t_vars *v)
{
	file_manager(&v);
	piper(v, 1);
	g_gl.failed = 0;
	g_gl.status = 0;
	if (v->collected_cmd && v->collected_cmd[0])
	{
		if (builtins(v->collected_cmd[0]))
			g_gl.status = builtve(v);
		else
		{
			g_gl.failed = execve(v->collected_cmd[0],
					v->collected_cmd, v->envprinc);
			if (g_gl.failed == -1)
				fail(v->collected_cmd[0], 0);
			exit(127);
		}
	}
	exit(1);
}

void	forker(t_vars *v, int i)
{
	v->pid[i] = fork();
	if (v->pid[i] == 0)
		children(v);
	else
	{
		if (v->in != 0)
			close(v->in);
		if (v->out != 1)
			close(v->out);
		v->in = v->pin;
	}
}

void	parent(t_vars *v)
{
	int	s_out;

	s_out = dup(1);
	file_manager(&v);
	piper(v, 0);
	if (v->collected_cmd && v->collected_cmd[0])
	{
		if (builtins(v->collected_cmd[0]))
		{
			g_gl.status = builtve(v);
		}
	}
	dup2(s_out, 1);
}

void	executer(t_linked_list *head, t_vars *v, int i)
{
	if (v->collected_cmd)
	{
		if ((v->collected_cmd && v->collected_cmd[0]
				&& i == 0 && !(head->next)) && builtins(v->collected_cmd[0]))
			parent(v);
		else
			forker(v, i);
	}
}

void	piper(t_vars *v, int i)
{
	dup2(v->in, 0);
	dup2(v->out, 1);
	if (v->in != 0)
		close(v->in);
	if (v->out != 1)
		close(v->out);
	if (v->pin != 0 && i == 1)
		close(v->pin);
}
