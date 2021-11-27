/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aali-mou <aali-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 17:47:15 by aali-mou          #+#    #+#             */
/*   Updated: 2021/11/27 17:55:45 by aali-mou         ###   ########.fr       */
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
