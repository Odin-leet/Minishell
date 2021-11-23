#include "minishell.h"
#include <dirent.h>

void	append(t_linked_list **head_ref, void *data)
{
	t_linked_list	*new_node;
	t_linked_list	*last;

	last = *head_ref;
	new_node = (t_linked_list *)malloc(sizeof(t_linked_list));
	new_node->data = (void *)data;
	new_node->next = NULL;
	if (*head_ref == NULL)
	{
		*head_ref = new_node;
		return ;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = new_node;
	return ;
}

void	*free_pre(char **split, int k)
{
	while (split[k])
	{
		free(split[k]);
		k++;
	}
	free(split);
	split = NULL;
	return (NULL);
}

int	findtype(char *s)
{
	if (ft_strncmp(s, "|", ft_strlen(s)) == 0)
		return (1);
	if (ft_strncmp(s, "<", ft_strlen(s)) == 0)
		return (2);
	if (ft_strncmp(s, ">", ft_strlen(s)) == 0)
		return (3);
	if (ft_strncmp(s, ">>", ft_strlen(s) + 1) == 0)
		return (4);
	if (ft_strncmp(s, "<<", ft_strlen(s) + 1) == 0)
		return (5);
	return (0);
}

int	funmain22(t_vars *v, char **split, char *buffer)
{
	t_linked_list	*head;
	t_linked_list	*parser;

	while (1)
	{
		head = NULL;
		parser = NULL;
		buffer = readline("Minishell 0.0$ ");
		add_history(buffer);
		if (buffer[0] != '\0')
		{
			split = ft_split(buffer, ' ');
			head = mainhelper3(split);
			if (check_errors(head) == 0)
				return (0);
			parser = parser(head, v->envprinc);
			free_head2(head);
			exec(parser, v);
			free(split);
			free_lin_command(parser);
		}
	}
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	char	*buffer;
	char	**split;
	t_vars	v;

	get_env(&v, env);
	argc = 2;
	buffer = NULL;
	split = NULL;
	argc = 0;
	argv = NULL;
	if (funmain22(&v, split, buffer) == 0)
		return (0);
	free_pre(v.env1, 0);
	free_pre(v.envprinc, 0);
	return (0);
}
