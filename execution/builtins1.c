/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aali-mou <aali-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 17:36:06 by aali-mou          #+#    #+#             */
/*   Updated: 2021/11/27 18:03:47 by aali-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo_logie(t_vars *v, int i, int n)
{
	int	count;

	while (v->collected_cmd[i])
	{
		count = checkforquotes2(v->collected_cmd[i]);
		v->collected_cmd[i] = changecollectedcmd(v->collected_cmd[i], count);
		if (v->collected_cmd[i + 1])
			printf("%s ", v->collected_cmd[i]);
		else
			printf("%s", v->collected_cmd[i]);
		i++;
	}
	if (n != 1)
		printf("\n");
}

int	echo(t_vars *v)
{
	int	i;
	int	j;
	int	n;

	i = 1;
	if (!(v->collected_cmd) || !v->collected_cmd[1])
		return (printf("\n") - 1);
	while (v->collected_cmd[i][0] == '-')
	{
		n = 0;
		j = 1;
		while (v->collected_cmd[i][j] == 'n' && v->collected_cmd[i][j] != '\0')
			j++;
		if (v->collected_cmd[i][j] != 'n' && v->collected_cmd[i][j - 1] == 'n' \
		&& v->collected_cmd[i][j] == '\0')
			n = 1;
		if (n != 1)
			break ;
		if (!v->collected_cmd[i + 1] && n == 1)
			return (0);
		i++;
	}
	echo_logie(v, i, n);
	return (0);
}

int	pwd(void)
{
	char	cwd[256];

	getcwd(cwd, sizeof(cwd));
	printf("%s\n", cwd);
	return (0);
}

int ft_exit(t_vars *v)
{
	char    **s;

	s = v->collected_cmd;
	
	if (!(s[1]))
		exit(0);
	else if ((is_not_digit(s[1]) == 0) && !(s[2]))
        exit(ft_atoi(s[1]));
	else if (((is_not_digit(s[1]) == 0) && (s[2])))
	{
		write(2, "bash: exit: too many arguments\n", 31);
		return (1);
	}
	else if (((is_not_digit(s[1]) == 1)))
		exit(1);
	return (1);
}

int	builtve(t_vars *v)
{
	g_gl.failed = 0;
	if (ft_strncmp(v->collected_cmd[0], "echo",
			ft_strlen(v->collected_cmd[0])) == 0)
		g_gl.failed = echo(v);
	if (ft_strncmp(v->collected_cmd[0], "cd",
			ft_strlen(v->collected_cmd[0])) == 0)
		g_gl.failed = cd(v);
	if (ft_strncmp(v->collected_cmd[0], "pwd",
			ft_strlen(v->collected_cmd[0])) == 0)
		g_gl.failed = pwd();
	if (ft_strncmp(v->collected_cmd[0], "unset",
			ft_strlen(v->collected_cmd[0])) == 0)
		g_gl.failed = unset(v);
	if (ft_strncmp(v->collected_cmd[0], "env",
			ft_strlen(v->collected_cmd[0])) == 0)
		g_gl.failed = env(v);
	if (ft_strncmp(v->collected_cmd[0], "exit",
			ft_strlen(v->collected_cmd[0])) == 0)
		ft_exit(v);
	if (ft_strncmp(v->collected_cmd[0], "export",
			ft_strlen(v->collected_cmd[0])) == 0)
		g_gl.failed = export(v);
	return (g_gl.failed);
}