/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashite <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 11:25:30 by ashite            #+#    #+#             */
/*   Updated: 2021/11/05 11:25:35 by ashite           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**cmd_collector(t_linked_list *cmd)
{
	char			**sequance;
	t_linked_list	*tempo;
	int				size;

	size = 0;
	tempo = cmd;
	while (tempo != NULL)
	{
		tempo = tempo->next;
		size++;
	}
	sequance = malloc(sizeof(char *) * (size + 1));
	sequance[size] = NULL;
	size = 0;
	while (cmd != NULL)
	{
		sequance[size] = ft_strdup((char *)cmd->data, 0);
		cmd = cmd->next;
		size++;
	}
	return (sequance);
}

char	**files_collector(t_linked_list *lfile)
{
	char			**sequance;
	t_linked_list	*tempo;
	int				size;

	size = 0;
	tempo = lfile;
	while (tempo != NULL)
	{
		tempo = tempo->next;
		size++;
	}
	sequance = malloc(sizeof(char *) * (size + 1));
	sequance[size] = NULL;
	size = 0;
	while (lfile != NULL)
	{
		sequance[size] = ((t_file *)lfile->data)->file;
		lfile = lfile->next;
		size++;
		
	}
	return (sequance);
}

int	*type_collector(t_linked_list *lfile)
{
	int				*tab;
	t_linked_list	*tempo;
	int				size;

	size = 0;
	tempo = lfile;
	while (tempo != NULL)
	{
		tempo = tempo->next;
		size++;
	}
	tab = malloc(sizeof(int *) * (size));
	size = 0;
	while (lfile != NULL)
	{
		tab[size] = ((t_file *)lfile->data)->type;
		printf("tab[size] == %d\n", tab[size]);
		lfile = lfile->next;
		size++;
	}
	return (tab);
}

int	quotescount(int *i, int count, char *string, char c)
{
	if (string[*i] == c)
	{
		count++;
		(*i)++;
		if (string[*i] == c)
		{
			(*i)++;
			count++;
		}
		else
		{
			while (string[*i] != c && string[*i])
				(*i)++;
			if (string[*i] == c)
			{
				count++;
				(*i)++;
			}
		}
	}
	return (count);
}

int	checkforquotes2(char *string)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (string[i] != '\0')
	{
		count = quotescount(&i, count, string, '\"');
		count = quotescount(&i, count, string, '\'');
		i++;
	}
	return (count);
}

char	*db_quotesreplace(char *tmp, char *string, int *c, int *i)
{
	if (string[*i] == '\"')
	{
		(*i)++;
		if (string[*i] == '\"')
			(*i)++;
		else
		{
			while (string[*i] != '\"' && string[*i])
				tmp[(*c)++] = string[(*i)++];
			if (string[(*i)] == '\"')
					(*i)++;
		}
	}
	return (tmp);
}

char	*sgl_quotesreplace(char *tmp, char *string, int *c, int *i)
{
	if (string[*i] == '\'')
	{
		(*i)++;
		if (string[*i] == '\'')
			(*i)++;
		else
		{
			while (string[*i] != '\'' && string[*i])
				tmp[(*c)++] = string[(*i)++];
			if (string[(*i)] == '\'')
					(*i)++;
		}
	}
	return (tmp);
}

char	*changecollectedcmd(char *string, int count)
{
	char	*tmp;
	int		i;
	int		c;

	i = 0;
	c = 0;
	tmp = NULL;
	tmp = malloc(sizeof(char) * (ft_strlen(string) - count + 1));
	while (string[i] != '\0')
	{
		tmp = db_quotesreplace(tmp, string, &c, &i);
		tmp = sgl_quotesreplace(tmp, string, &c, &i);
		if (string[i] != '\0')
		{
			tmp[c] = string[i];
			c++;
			i++;
		}
	}
	tmp[c] = '\0';
	free(string);
	return (tmp);
}

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

char	*exportenv(t_vars *pl, char *string)
{
	int	i;
	int	count;
	int	c;

	i = 0;
	while (pl->envprinc[++i] != NULL)
	{
		count = ft_strlen(string);
		c = thereisequ(pl->envprinc[i]);
		if (c != -1)
		{
			if (count < c)
				count = c;
		}
		else
		{
			c = ft_strlen(pl->envprinc[i]);
			if (count < c)
				count = c;
		}
		if (strncmp(pl->envprinc[i], string, count) == 0)
			return (ft_substr(pl->envprinc[i], count + 1,
					ft_strlen(pl->envprinc[i]) - count));
	}
	return (NULL);
}
/*cat << d | << hjsd >f
cat << k << f
cat << k > file0 << f> file1*/
// void	ft_cd(t_builtin_vars var, int *retv)
// void	ft_cd_normal_case(t_builtin_vars var, char *dest_path, int *retv)
// int	change_oldpwd(char ***envp)
// int	change_pwd(char ***envp)
// void	ft_cd_oldpwd(t_built in_vars var, int *retv)

void	file_manager(t_vars *v)
{
	int	count;

	count = 0;
	v->collected_files = files_collector(v->lfile);
	v->collected_type = type_collector(v->lfile);
	while (v->collected_files[count])
	{
		if (v->out != 0 && (v->collected_type[count] == 4 \
		|| v->collected_type[count] == 3))
			close(v->out);
		else if (v->in != 1 && (v->collected_type[count] == 2 \
		|| v->collected_type[count] == 5))
			close(v->in);
		if (v->collected_type[count] == 3 |)
			v->out = open(v->collected_files[count],
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (v->collected_type[count] == 4)
			v->out = open(v->collected_files[count],
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (v->collected_type[count] == 2 || v->collected_type[count] == 5)
			v->in = open(v->collected_files[count], O_RDONLY, 0644);
		count++;
	}
}

int	builtve(t_vars *v)
{
	if (ft_strncmp(v->collected_cmd[0], "echo",
			ft_strlen(v->collected_cmd[0])) == 0)
		return (echo(v));
	if (ft_strncmp(v->collected_cmd[0], "cd",
			ft_strlen(v->collected_cmd[0])) == 0)
		return (cd(v));
	if (ft_strncmp(v->collected_cmd[0], "pwd",
			ft_strlen(v->collected_cmd[0])) == 0)
		return (pwd());
	if (ft_strncmp(v->collected_cmd[0], "unset",
			ft_strlen(v->collected_cmd[0])) == 0)
		return (unset(v));
	if (ft_strncmp(v->collected_cmd[0], "env",
			ft_strlen(v->collected_cmd[0])) == 0)
		return (env(v));
	if (ft_strncmp(v->collected_cmd[0], "exit",
			ft_strlen(v->collected_cmd[0])) == 0)
		exit(1);
	if (ft_strncmp(v->collected_cmd[0], "export",
			ft_strlen(v->collected_cmd[0])) == 0)
		return (export(v));
	return (0);
}

void	piper(t_vars *v, int i)
{
	dup2(v->in, 0);
	dup2(v->out, 1);
	if (v->in != 0)
		close(v->in);
	if (v->out != 1)
		close(v->out);
	if (v->pin != 0 && i == 1)
		close(v->pin);
}
// << lkl 
void	exec_initializer(t_vars *v, t_linked_list *head)
{
	t_linked_list	*tmp;

	v->collected_cmd = NULL;
	v->collected_files = NULL;
	v->collected_type = 0;
	v->in = 0;
	v->pin = 0;
	v->out = 1;
	tmp = head;
	v->cmd_size = 0;
	while (tmp)
	{
		(v->cmd_size)++;
		//herdoc
		tmp = tmp->next;
	}
	v->pid = malloc(sizeof(pid_t) * (v->cmd_size));
}

void	fail(char *s, int act)
{
	if (act == 0)
	{
		write(2, "bash: ", 6);
		write(2, s, ft_strlen(s));
		write(2, ":command not found\n", 19);
	}	
}

void	children(t_vars *v)
{
	file_manager(v);
	piper(v, 1);
	g_gl.status = 0;
	if (builtins(v->collected_cmd[0]))
		g_gl.status = builtve(v);
	else
	{
		execve(v->collected_cmd[0], v->collected_cmd, v->envprinc);
		 exit(127);

	}
		//write(,"command not found \n", 20)
	if (g_gl.status == 0)
		fail(v->collected_cmd[0], 0);
	exit(1);
}

void	forker(t_vars *v, int i)
{
	v->pid[i] = fork();
	if (v->pid[i] == 0)
		children(v);
	else
	{
		if (v->in != 0)
			close(v->in);
		if (v->out != 1)
			close(v->out);
		v->in = v->pin;
	}
}

void	parent(t_vars *v)
{
	int	s_out;

	s_out = dup(1);
	file_manager(v);
	piper(v, 0);
	if (builtins(v->collected_cmd[0]))
	{
		g_gl.status = builtve(v);
		if (g_gl.status == 1)
			fail(v->collected_cmd[0], g_gl.status);
	}
	dup2(s_out, 1);
}
int    get_fucking_status(int status)
{
    if (WIFEXITED(status) == 1)
        return (WEXITSTATUS(status));
    if (WIFSIGNALED(status) == 1)
        return (128 + WTERMSIG(status));
    return (0);
}
void	pid_manager(t_vars *v)
{
	int	i;

	i = 0;
	while (i < v->cmd_size)
		waitpid(v->pid[i++], &g_gl.status, 0);
	if (g_gl.status > 255)
		g_gl.status = g_gl.status % 255;
	else
		g_gl.status = get_fucking_status(g_gl.status);
	//if (g_gl.status > 256)
	//	g_gl.status = g_gl.status % 127;
	//if(WIFSIGNALED(g_gl.status))
	//{
	//	 g_gl.status += 128;
	//	 printf("sadasdasdasdasdasdasasdasd|}}}\n");
//
	//}
	//g_gl.status = get_fucking_status(g_gl.status);
	free(v->pid);
}



void	exec(t_linked_list *head, t_vars *v)
{
	int	fd[2];
	int	i;

	i = 0;
	exec_initializer(v, head);
	while (head)
	{
		v->lcmd = ((t_command *)head->data)->nameargs;
		v->lfile = ((t_command *)head->data)->files;
		v->collected_cmd = cmd_collector(v->lcmd);
		pipe(fd);
		v->pin = fd[0];
		v->out = fd[1];
		if (!(head->next))
			v->out = 1;
		if ((i == 0 && !(head->next)) && builtins(v->collected_cmd[0]))
			parent(v);
		else
			forker(v, i);
		i++;
		head = head->next;
		free_pre(v->collected_cmd, 0);
		v->collected_cmd = NULL;
	}
	pid_manager(v);
	g_gl.isin = 0;
}

/*
*free(v->collected_cmd);
*[free table in nd out cause we dup 
*the cmd not just assigning the pointer]
*free(v->collected_files);
*free(v->collected_type);
*/