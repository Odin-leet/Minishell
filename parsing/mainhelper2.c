/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainhelper2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashite <ashite@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 09:27:29 by aali-mou          #+#    #+#             */
/*   Updated: 2021/11/28 06:02:24 by ashite           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_errors1(t_file *file, int j, char *checks)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (checks[i] == file->file[0])
		{
			while (file->file[j] != '\0')
			{
				while ((file->file[j] == checks[i])
					&& file->file[j] != '\0')
					j++;
				if (check_errors2(j, i, file->file) == 0)
					return (0);
			}
		}
		i++;
	}
	return (1);
}

int	check_errors_pipe(t_file *file, t_linked_list *ptr)
{
	t_file	*file2;

	if (ptr->next)
	{
		file2 = (t_file *)ptr->next->data;
		if (file->file[0] == '|' && file2->file[0] == '|')
		{
			printf("bash: syntax error near unexpected token `|'\n");
			return (0);
		}
	}
	return (1);
}

int	check1(t_file *file, t_file *file2, t_linked_list *ptr, char *checks)
{
	if (ptr->next != NULL)
	{
		file2 = (t_file *)ptr->next->data;
		if (((file->file[ft_strlen(file->file) - 1] == checks[1])
				|| (file->file[ft_strlen(file->file) - 1] == checks[0]))
			&& ((ptr->next == NULL) || file2->file[0] == '|'))
		{
			printf("bash: synta x error near unexpected token \n");
			free(checks);
			return (0);
		}
	}
	else
	{
		file2 = NULL;
		if (((file->file[ft_strlen(file->file) - 1] == checks[1])
				|| (file->file[ft_strlen(file->file) - 1] == checks[0]))
			&& ((ptr->next == NULL)))
		{
			printf("bash: syntax error near unexpected token \n");
			free(checks);
			return (0);
		}
	}
	return (1);
}

char	*remplirchecks(char *checks)
{
	checks = malloc(sizeof(char) * 4);
	checks[1] = '<';
	checks[2] = '|';
	checks[0] = '>';
	return (checks);
}

int	check_errors(t_linked_list *ptr)
{
	t_file	*file;
	t_file	*file2;
	char	*checks;
	int		j;

	checks = NULL;
	checks = remplirchecks(checks);
	j = 0;
	file2 = NULL;
	while (ptr != NULL)
	{
		file = (t_file *)ptr->data;
		if (check_errors_pipe(file, ptr) == 0)
			return (0);
		if (check_errors1(file, j, checks) == 0)
		{
			free(checks);
			return (0);
		}
		if (check1(file, file2, ptr, checks) == 0)
			return (0);
		ptr = ptr->next;
	}
	free(checks);
	return (1);
}
