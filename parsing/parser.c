/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aali-mou <aali-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 09:27:46 by aali-mou          #+#    #+#             */
/*   Updated: 2021/11/28 02:45:21 by aali-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	lastif(int *i, t_command **command, t_linked_list **lexer,
		t_linked_list **head)
{
	t_file	*token;

	token = (t_file *)((*lexer)->data);
	append(head, (void *)*command);
	if (token->type == 1)
	{
		*command = (t_command *)malloc(sizeof(t_command));
		(*command)->files = NULL;
		(*command)->nameargs = NULL;
		free_files_linked2(*lexer);
		*i = 0;
	}
}

void	else2(t_file *token, t_command **command,
			t_linked_list **lexer, char **env)
{
	t_file	*f;
	t_file	*tmp;

	tmp = (t_file *)((*lexer)->next->data);
	f = (t_file *)malloc(sizeof(t_file));
	if (token->type != 5)
		tmp->file = (void *)handleenvir((char *)tmp->file, env);
	f->file = tmp->file;
	free(token->file);
	f->type = token->type;
	append(&((*command)->files), (void *)f);
	*lexer = (*lexer)->next;
}

int	handle_parser_helper(t_parser *p, t_file *token, char **env)
{
	token->file = (void *)handleenvir((char *)token->file, env);
	token->file = (void *)handleargs((char *)token->file, env);
	if (token->file == NULL)
	{	
		free(p->command);
		return (0);
	}
	append(&((p->command)->nameargs), (void *)token->file);
	(p->i)++;
	return (1);
}

int	handle_parser(t_parser *p, char **env, t_linked_list **lexer)
{
	t_file	*token;

	token = (t_file *)((*lexer)->data);
	if (token->type == 0 && p->i == 0)
	{
		if (handle_parser_helper(p, token, env) == 0)
			return (0);
	}
	else if (token->type == 0)
		else1(token, env, &(p->command));
	else if (token->type != 0 && token->type != 1
		&& ((*lexer)->next) && ((t_file *)((*lexer)->next->data))->type == 0)
		else2(token, &(p->command), lexer, env);
	else if (token->type != 1)
	{
		printf("error undefind arg\n");
		free(token->file);
	}
	if (token->type == 1 || (*lexer)->next == NULL)
		lastif(&(p->i), &(p->command), lexer, &(p->head));
	return (1);
}

t_linked_list	*parser(t_linked_list *lexer, char **env)
{
	t_parser	p;

	p.i = 0;
	p.head = NULL;
	p.command = (t_command *)malloc(sizeof(t_command));
	p.command->files = NULL;
	p.command->nameargs = NULL;
	while (lexer)
	{
		if (!handle_parser(&p, env, &lexer))
			return (NULL);
		lexer = lexer->next;
	}
	return (p.head);
}
