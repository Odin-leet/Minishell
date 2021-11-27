/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aali-mou <aali-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 11:25:30 by ashite            #+#    #+#             */
/*   Updated: 2021/11/27 09:52:28 by aali-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (s1[i] == '\0')
		return (-(unsigned char)s2[i]);
	if (s2[i] == '\0')
		return ((unsigned char)s1[i]);
	return (0);
}

void	close_and_exit(int fd)
{
	close(fd);
	exit(fd);
}

int	get_status(int status)
{
	if (WIFEXITED(status) == 1)
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status) == 1)
		return (128 + WTERMSIG(status));
	return (0);
}

int	exit_status(pid_t pid, int fd)
{
	int	exit_status;
	int	status;

	waitpid(pid, &status, 0);
	exit_status = get_status(status);
	g_gl.herdo = 0;
	g_gl.herdoc = 0;
	close(fd);
	if (exit_status == 2)
		return (1);

	return (0);
}

void	ctrl_handler(int sig)
{
	g_gl.herdoc = 2;
	exit(sig);
}

void	signals(void)
{
	if (signal(SIGINT, ctrl_handler) == SIG_ERR)
		exit(1);
	signal(SIGQUIT, SIG_IGN);
}

int	heredoc(char *delimeter, char *file_name)
{
	int		fd;
	char	*line;
	pid_t	pid;

	g_gl.herdoc = 1;
	fd = open(file_name, O_RDWR | O_TRUNC | O_CREAT, S_IWUSR | S_IRUSR);
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
				close_and_exit(fd);
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
			free(line);
		}
		close_and_exit(fd);
	}
	return (exit_status(pid, fd));
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char *ret;

	ret = ft_strjoin(s1, s2);
	free(s1);
	s1 = NULL;
	return (ret);
}


char	*ft_rng(void)
{
	static int	nb = 0;
	char		*name;
	char		*str_nb;
	char		*str_modulo;
	char		*tmp;

	nb++;
	str_nb = ft_itoa(nb);
	str_modulo = ft_itoa(nb % 3);
	tmp = ft_strdup("/tmp/", 0);
	tmp = ft_strjoin_free(tmp, str_nb);
	name = ft_strjoin(tmp, str_modulo);
	free(tmp);
	free(str_nb);
	free(str_modulo);
	return (name);
}

int	heredocs_finder(t_vars *v)
{
	int		i;
	char	*filename;

	i = 0;
    v->collected_files = files_collector(v->lfile);
	v->collected_type = type_collector(v->lfile);
	while (v->collected_files != NULL && v->collected_files[i] != NULL)
	{
		if (v->collected_type[i] == 5 && v->collected_files[i] != NULL)
		{
			filename = ft_rng();
			if (heredoc(v->collected_files[i], filename))
			{
				free(filename);
				filename = NULL;
				free_pre(v->collected_files, 0);
                free(v->collected_type);
				v->collected_type = NULL;
				return (1);
			}
			free(v->collected_files[i]);
			v->collected_files[i] = NULL;
			v->collected_files[i] = ft_strdup(filename, 0);
			free(filename);
			filename = NULL;
		}
		i++;
	}
    return (0);
}
