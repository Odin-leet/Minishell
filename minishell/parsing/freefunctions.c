/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freefunctions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aali-mou <aali-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 09:26:31 by aali-mou          #+#    #+#             */
/*   Updated: 2021/11/28 04:38:28 by aali-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_head2(t_linked_list *head)
{
	if (head == NULL)
		return ;
	free_head2(head->next);
	free(head->data);
	free(head);
}

void	free_head(t_linked_list *head)
{
	if (head == NULL)
		return ;
	free_head(head->next);
	free(head->data);
	free(head);
}

void	free_head3(t_linked_list *head)
{
	if (head == NULL)
		return ;
	free_head(head->next);
	free_files_linked(head->data);
	free(head->data);
	free(head);
}

void	free_files_linked(t_linked_list *files)
{
	if (!files)
		return ;
	free_files_linked(files->next);
	free(((t_file *)(files->data))->file);
	free(files->data);
	free(files);
}

void	free_lin_command(t_linked_list *command)
{
	t_command	*cmd;

	if (command == NULL)
		return ;
	free_lin_command(command->next);
	cmd = (t_command *)(command->data);
	free_head(cmd->nameargs);
	free_files_linked(cmd->files);
	free(command->data);
	free(command);
}
