#include "minishell.h"

t_linked_list *parser(t_linked_list *lexer, char **env)
{
	t_linked_list *head = NULL;
	t_command *command;
	t_file *token;
	int i;

	i = 0;
	command = (t_command *)malloc(sizeof(t_command));
	command->files = NULL;
	command->nameargs = NULL;

	while (lexer)
	{
		token = (t_file *)lexer->data;
		if (token->type == 0 && i == 0)
		{
			if ((token->file = (void *)handleargs((char *)token->file, env)) == NULL)
				return (NULL);
			append(&(command->nameargs), (void *)token->file);
			//printf("tokenfile === %s \n", (char *)token->file);

			i++;
		}
		else if (token->type == 0)
		{
			token->file = (void *)handleenvir((char *)token->file, env);
			printf("{{{%s}}}\n", token->file);
			append(&(command->nameargs), (void *)token->file);
		}
		else if (token->type != 0 && token->type != 1 && (lexer->next) && ((t_file *)(lexer->next->data))->type == 0)
		{
			t_file *f;
			t_file *tmp = (t_file *)(lexer->next->data);

			f = (t_file *)malloc(sizeof(t_file));
		//	f->file = strdup(tmp->file);
			f->file = tmp->file;
			free(token->file);
			f->type = token->type;
			append(&(command->files), (void *)f);
			lexer = lexer->next;
		}
		else if (token->type != 1)
			printf("error\n");
		printf("%s -- %d \n",(char *)token->file , (int) token->type);
		if (token->type == 1 || lexer->next == NULL)
		{
			append(&(head), (void *)command);
			if (token->type == 1)
			{
			command = (t_command *)malloc(sizeof(t_command));
			command->files = NULL;
			command->nameargs = NULL;\
			//free(lexer->data);
			//free(lexer);
			free_files_linked2(lexer);
			i = 0;
			}

			//	printf("lool im here \n");
		}
		lexer = lexer->next;
	}
	return (head);
}