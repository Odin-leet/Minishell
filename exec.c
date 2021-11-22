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

#include "minishell.h"
#include <string.h>
// int		ft_strchr(const char *s, int c)
// {
// 	while (*s != '\0')
// 	{
// 		if (*s == c)
// 			return (1);
// 		s++;
// 	}
// 	if (c == '\0')
// 		return (1);
// 	return (0);
// }
//dprintf(2, "%s : wrong\n",s[0]);

size_t	ft_strlcat(char *dst, char *src, size_t size)
{
	size_t	src_len;
	size_t		i;
	size_t	dst_len;

	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	i = 0;
	while (i + dst_len < (size - 1) && src[i] != '\0')
	{
		dst[i + (int)dst_len] = src[i];
		i++;
	}
	dst[i + (int)dst_len] = '\0';
	if (size < dst_len)
		return (size + src_len);
	else
		return (dst_len + src_len);
}

char **cmd_collector(t_linked_list *cmd)
{
	char **sequance;
	t_linked_list *tempo;
	int size;

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
		sequance[size] = (char *)cmd->data;
		cmd = cmd->next;
		size++;
	}
	return (sequance);
}
char **files_collector(t_linked_list *lfile)
{
	char **sequance;
	t_linked_list *tempo;
	int size;

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
int *type_collector(t_linked_list *lfile)
{
	int *tab;
	t_linked_list *tempo;
	int size;
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
int echo(t_vars *v)
{
	int i;
	int j;
	int flag;

	i = 1;
	j = 1;
	flag = 0;
	if (!(v->collected_cmd))
		return (0);
	//if s = empty return new line with the return signal (but I'm the sys now)
	if (v->collected_cmd[i][0] == '-')
	{
		while(v->collected_cmd[i][j] == 'n')
			j++;
		if (v->collected_cmd[i][j] == ' ')
		{
			flag = 2;
			i = 2;
		}	
	}
	while (v->collected_cmd[i])
	{
		if (v->collected_cmd[i + 1])
			printf("%s ", v->collected_cmd[i]);
		else
			printf("%s", v->collected_cmd[i]);
		i++;
	}
	if (flag == 0)
		printf("\n");
	return (1);
}

int pwd(void)
{
  char cwd[256];

  getcwd(cwd,sizeof(cwd));
  printf("%s\n" ,cwd);
  return (1);
}

int cd(t_vars *v)
{
  char cwd[256];
  getcwd(cwd,sizeof(cwd));
  if (v->collected_cmd[1])
  ft_strlcat(cwd,"/",1);
  ft_strlcat(cwd,v->collected_cmd[1],ft_strlen(v->collected_cmd[1]));
  printf("[%s]\n", cwd);
  chdir(cwd);
  printf("%s\n",v->collected_cmd[1]);
  return 0;
}
void file_manager(t_vars *v)
{
	int count;

	count = 0;
	v->collected_files = files_collector(v->lfile);
	v->collected_type = type_collector(v->lfile);
	while (v->collected_files[count])
	{
		if (v->out != 0 && (v->collected_type[count] == 4 || v->collected_type[count] == 3))
			close(v->out);
		else if (v->in != 1 && (v->collected_type[count] == 2 || v->collected_type[count] == 5))
			close(v->in);
		if (v->collected_type[count] == 3)
			v->out = open(v->collected_files[count], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (v->collected_type[count] == 4)
			v->out = open(v->collected_files[count], O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (v->collected_type[count] == 2)
			v->in = open(v->collected_files[count], O_RDONLY, 0644);
		count++;
	}
}
int builtve(t_vars *v)
{
	if (ft_strncmp(v->collected_cmd[0], "echo", ft_strlen(v->collected_cmd[0])) == 0)
		return (echo(v));
	if (ft_strncmp(v->collected_cmd[0], "cd", ft_strlen(v->collected_cmd[0])) == 0)
		return (cd(v));
	if (ft_strncmp(v->collected_cmd[0], "pwd", ft_strlen(v->collected_cmd[0])) == 0)
		return (pwd());
	// if (ft_strncmp(v->collected_cmd[0], "unset", ft_strlen(v->collected_cmd[0])) == 0)
	// 	return (unset(v));
	// if (ft_strncmp(v->collected_cmd[0], "env", ft_strlen(v->collected_cmd[0])) == 0)
	// 	return (env(v));
	// if (ft_strncmp(v->collected_cmd[0], "exit", ft_strlen(v->collected_cmd[0])) == 0)
	// 	return (exit());
	// if (ft_strncmp(v->collected_cmd[0], "export", ft_strlen(v->collected_cmd[0])) == 0)
	// 	return (export(v));
	return (0);
}
void exec(t_linked_list *head, t_vars *v)
{
	t_linked_list *tmp;
	int fd[2];
	int i;

	v->in = 0;
	v->pin = 0;
	v->out = 1;
	tmp = head;
	v->cmd_size = 0;
	while (tmp)
	{
		(v->cmd_size)++;
		tmp = tmp->next;
	}
	i = 0;
	v->pid = malloc(sizeof(pid_t) * (v->cmd_size));
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
		if (i == 0 && !(head->next) && builtins(v->collected_cmd[0]))
			builtve(v);
		else
		{
			v->pid[i] = fork();
			if (v->pid[i] == 0)
			{
				file_manager(v);
				//export + redirection + |
				dup2(v->in, 0);
				dup2(v->out, 1);
				if (v->in != 0)
					close(v->in);
				if (v->out != 1)
					close(v->out);
				if (v->pin != 0)
					close(v->pin);
				if (builtins(v->collected_cmd[0]))
					builtve(v);
				else
					execve(v->collected_cmd[0], v->collected_cmd, v->envprinc);
				//dprintf(2,"bash: %s: command not found\n", s[0]);
				exit(0);
			}
			else
			{
				if (v->in != 0)
					close(v->in);
				if (v->out != 1)
					close(v->out);
				v->in = v->pin;
			}
		}

		i++;
		// free(v->collected_cmd);
		// free(v->collected_files);
		// free(v->collected_type);
		head = head->next;
		v->collected_cmd = NULL;
		v->collected_files = NULL;
		v->collected_type = 0;
	}
	i = 0;
	while (i < v->cmd_size)
	{
		waitpid(v->pid[i], NULL, 0);
		i++;
	}
	free(v->pid);
}
