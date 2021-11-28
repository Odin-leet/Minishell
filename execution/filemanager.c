/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filemanager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aali-mou <aali-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 17:38:54 by aali-mou          #+#    #+#             */
/*   Updated: 2021/11/28 21:04:29 by aali-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	case_checker(t_vars *v)
{
	int	count1;
	int	count;
	int	count2;

	count1 = 0;
	count2 = 0;
	count = 0;
	g_gl.special = 0;
	while (v->collected_files && v->collected_files[count])
	{
		if (v->collected_type[count] == 4)
			count1 = count;
		if (v->collected_type[count] == 2)
			count2 = count;
		count++;
	}
	if (v->collected_files[count1] == v->collected_files[count2])
		return (0);
	else
		return (1);
}

void	file_manager(t_vars **v)
{
	int	count;

	count = 0;
	while ((*v)->collected_files && (*v)->collected_files[count]
		&& case_checker(*v))
	{
		if ((*v)->out != 0 && ((*v)->collected_type[count] == 4
				|| (*v)->collected_type[count] == 3))
			close((*v)->out);
		else if ((*v)->in != 1 && ((*v)->collected_type[count] == 2
				|| (*v)->collected_type[count] == 5))
			close((*v)->in);
		if ((*v)->collected_type[count] == 3)
			(*v)->out = open((*v)->collected_files[count],
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if ((*v)->collected_type[count] == 4)
			(*v)->out = open((*v)->collected_files[count],
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if ((*v)->collected_type[count] == 2
			|| (*v)->collected_type[count] == 5)
				(*v)->in = open((*v)->collected_files[count], O_RDONLY, 0644);
		if ((*v)->in < 0 || (*v)->out < 0)
			write(2, "No such file or directory\n", 26);
		count++;
	}
}

int	is_not_digit(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	exec_initializer(t_vars *v, t_linked_list *head)
{
	t_linked_list	*tmp;
	int				ret;

	ret = 0;
	g_gl.herdo = 0;
	g_gl.herdoc = 0;
	v->in = 0;
	v->pin = 0;
	v->out = 1;
	tmp = head;
	v->cmd_size = 0;
	while (tmp)
	{
		v->lfile = ((t_command *)tmp->data)->files;
		(v->cmd_size)++;
		if (v->lfile != NULL)
			ret = heredocs_finder(v);
		tmp = tmp->next;
	}
	v->pid = malloc(sizeof(pid_t) * (v->cmd_size));
	return (ret);
}

void	fail(char *s, int act)
{
	if (act == 0 && s)
	{
		write(2, "Minishell: ", 12);
		write(2, s, ft_strlen(s));
		write(2, ":command not found\n", 19);
	}	
}
