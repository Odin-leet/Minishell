/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aali-mou <aali-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 17:33:43 by aali-mou          #+#    #+#             */
/*   Updated: 2021/11/28 21:04:39 by aali-mou         ###   ########.fr       */
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

void	execvequotes(t_vars *v)
{
	int	i;
	int	count;

	i = 1;
	while (v->collected_cmd2[i])
	{
		count = checkforquotes2(v->collected_cmd2[i]);
		v->collected_cmd2[i] = changecollectedcmd(v->collected_cmd2[i], count);
		i++;
	}
}

void	children(t_vars *v)
{
	file_manager(&v);
	piper(v, 1);
	g_gl.failed = 0;
	g_gl.status = 0;
	if (v->collected_cmd && v->collected_cmd[0])
	{
		if (builtinns(v->collected_cmd[0])
			|| builtinns(v->collected_cmd[0]) < 0)
			g_gl.status = builtve(v);
		else
		{
			v->collected_cmd2 = cmd_collector(v->lcmd);
			execvequotes(v);
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

	s_out = 1;
	file_manager(&v);
	piper(v, 0);
	if (v->collected_cmd && v->collected_cmd[0])
	{
		printf("speeeeeecail %d\n",g_gl.special);
		if (builtins(v->collected_cmd[0]))
		{
			g_gl.status = builtve(v);
		}
	}
	if (v->collected_files)
		printf("kayn file");
	dup2(s_out, 1);
}
