/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashite <ashite@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 17:33:43 by aali-mou          #+#    #+#             */
/*   Updated: 2021/11/28 01:21:33 by ashite           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**cmd_collector2(t_linked_list *cmd)
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
		cmd = cmd->next;
		checkforquotes(&sequance[size]);
		size++;
	}
	return (sequance);
}

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
			v->collected_cmd2 = cmd_collector2(v->lcmd);
			g_gl.failed = execve(v->collected_cmd2[0],
					v->collected_cmd2, v->envprinc);
			if (g_gl.failed == -1)
				fail(v->collected_cmd2[0], 0);
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
