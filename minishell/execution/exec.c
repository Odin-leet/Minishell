/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashite <ashite@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 11:25:30 by ashite            #+#    #+#             */
/*   Updated: 2021/11/28 19:44:44 by ashite           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	builtinns(char *string)
{
	if (ft_strncmp(string, "echo", ft_strlen(string)) == 0)
		return (-1);
	if (ft_strncmp(string, "cd", ft_strlen(string)) == 0)
		return (1);
	if (ft_strncmp(string, "pwd", ft_strlen(string)) == 0)
		return (1);
	if (ft_strncmp(string, "unset", ft_strlen(string)) == 0)
		return (1);
	if (ft_strncmp(string, "env", ft_strlen(string)) == 0)
		return (1);
	if (ft_strncmp(string, "exit", ft_strlen(string)) == 0)
		return (1);
	if (ft_strncmp(string, "export", ft_strlen(string)) == 0)
		return (1);
	return (0);
}

void	delete_close_file(t_linked_list *tmp, t_vars *v, int *fd)
{
	pid_manager(v);
	g_gl.isin = 0;
	if (v->in != 0)
		close(v->in);
	if (v->out != 1)
		close(v->out);
	if (v->pin != 1 && v->pin != 0)
		close(v->pin);
	close(fd[0]);
	close(fd[1]);
	while (tmp)
	{
		v->lfile = ((t_command *)tmp->data)->files;
		while (v->lfile && v->lfile->data)
		{
			if (((t_file *)v->lfile->data)->type == 5)
				unlink(((t_file *)v->lfile->data)->file);
			v->lfile = v->lfile->next;
		}
		tmp = tmp->next;
	}
}

void	executer(t_linked_list *head, t_vars *v, int i)
{
	if (v->collected_cmd)
	{
		if ((v->collected_cmd && v->collected_cmd[0]
				&& i == 0 && !(head->next))
			&& builtinns(v->collected_cmd[0]) > 0)
			parent(v);
		else
			forker(v, i);
	}
}

void	exec(t_linked_list *head, t_vars *v)
{
	int				fd[2];
	int				i;
	t_linked_list	*tmp;

	tmp = head;
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
	delete_close_file(tmp, v, fd);
}
