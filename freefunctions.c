#include "minishell.h"

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
	t_file	*file2;

	if (head == NULL)
		return ;
	file2 = (t_file *)(head->data);
	free(file2->file);
	free_head(head->next);
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

void	free_files_linked2(t_linked_list *files)
{
	if (!files)
		return ;
	free(((t_file *)(files->data))->file);
}
