/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aali-mou <aali-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 11:25:30 by ashite            #+#    #+#             */
/*   Updated: 2021/11/27 17:58:35 by aali-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	signals(void)
{
	if (signal(SIGINT, ctrl_handler) == SIG_ERR)
		exit(1);
	signal(SIGQUIT, SIG_IGN);
}

int	heredoc(char *delimeter)
{
	int		fd;
	char	*line;
	pid_t	pid;

	g_gl.herdoc = 1;
	fd = open(delimeter, O_RDWR | O_TRUNC | O_CREAT, S_IWUSR | S_IRUSR);
	g_gl.herdo = 1;
	pid = fork();
	if (pid == 0)
	{
		signals();
		while (1)
		{
			line = NULL;
			line = readline(">");
			if (line == NULL || ft_strcmp(line, delimeter) == 0)
				break ;
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
			free(line);
		}
		close_and_exit(fd);
	}
	return (exit_status(pid, fd));
}

char	*ft_strjoin_free(char **s1, char *s2)
{
	char	*ret;

	ret = ft_strjoin(*s1, s2);
	free(*s1);
	*s1 = NULL;
	return (ret);
}

int	herdocinit(char **collected_files, int *collected_type)
{
	int	i;

	i = 0;
	while (collected_files != NULL && collected_files[i] != NULL)
	{
		if (collected_type[i] == 5 && collected_files[i] != NULL)
		{
			if (heredoc(collected_files[i]))
			{
				if (collected_type)
					free(collected_type);
				free_pre(collected_files, 0);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	heredocs_finder(t_vars *v)
{
	char	**collected_files;
	int		*collected_type;

	collected_files = NULL;
	collected_type = NULL;
	collected_files = files_collector(v->lfile);
	collected_type = type_collector(v->lfile);
	if ((herdocinit(collected_files, collected_type)) == 1)
		return (1);
	free_pre(collected_files, 0);
	if (collected_type)
		free(collected_type);
	collected_files = NULL;
	collected_type = NULL;
	return (0);
}
