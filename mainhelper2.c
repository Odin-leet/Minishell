#include "minishell.h"

int	check_errors1(t_file *file, int i, int j, char *checks)
{
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

int	check_errors(t_linked_list *ptr)
{
	t_file	*file;
	char	*checks;
	int		i;
	int		j;

	checks = malloc(sizeof(char) * 4);
	checks[1] = '<';
	checks[2] = '|';
	checks[0] = '>';
	j = 0;
	file = (t_file *)ptr->data;
	while (ptr != NULL)
	{
		i = 0;
		file = (t_file *)ptr->data;
		if (check_errors1(file, i, j, checks) == 0)
			return (0);
		ptr = ptr->next;
	}
	free(checks);
	return (1);
}

int	mainhelper2(int j, int i, t_linked_list **head, char *string)
{
	if (j > 1)
	{
		printf("error here \n");
		return (0);
	}
	if (string[i] != '\0')
		storeinfos(ft_substr(string, i, strlen(string) - i), head);
	return (1);
}

t_linked_list	*mainhelper3(char **split)
{
	int				n;
	int				j;
	t_linked_list	*head;

	n = 0;
	head = NULL;
	j = 0;
	while (split[n] != NULL)
	{
		if (checkforpipe(split[n]) == 1)
		{
			mainhelper(split[n], j, &head);
			free(split[n]);
		}
		else
		{
			storeinfos(split[n], &head);
		}
		n++;
	}
	return (head);
}
