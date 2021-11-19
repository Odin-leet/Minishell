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
	sequance = malloc(sizeof(char*) * (size  + 1));
	sequance[size] = NULL;
	//printf("%d === size \n",size);
	size = 0;
	while(cmd!= NULL)
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
	sequance = malloc(sizeof(char*) * (size  + 1));
	sequance[size] = NULL;
	//printf("%d === size \n",size);
	size = 0;
	while(lfile!= NULL)
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
	while(tempo!=  NULL)
	{
		tempo = tempo->next;
		size++;
	}
	tab = malloc(sizeof(int*) * (size));

	size= 0;
	while(lfile!= NULL)
	{
		tab[size] = ((t_file *)lfile->data)->type;
		printf("tab[size] == %d\n",tab[size]);
		lfile = lfile->next;
		size++;
	}
	//tab[size] = NULL;
	return (tab);
}

// int file_manager(char *out_or_in)
// {

// 	if ()
// }	
// while (v.collected_files[c] != NULL)
// {printf("command  %s\n file name: %s\n type : %d\n",v.collected_cmd[0], v.collected_files[c], v.collected_type[c]);
// c++;}
void exec(t_linked_list *head, char **env)
{
	t_vars v;
	int fd[2];
	int i;
	char **ss;
	int count;
	ss = env;

	v.in = 0;
	v.pin = 0;
	v.out = 1;
	i = 0;
	while (head)
	{
		v.lcmd = ((t_command *)head->data)->nameargs;
		v.lfile = ((t_command *)head->data)->files;
		v.collected_cmd = cmd_collector(v.lcmd);
		v.collected_files = files_collector(v.lfile);
		v.collected_type = type_collector(v.lfile);
	
		pipe(fd);
		v.pin = fd[0];
		v.out = fd[1];
		if (!(head->next))
			v.out = 1;
		count = 0;
		
		v.pid = fork();
		if (v.pid == 0)
		{
			while (v.collected_files[count])
			{
				if (v.out != 0 && (v.collected_type[count] == 4 || v.collected_type[count] == 3))
					close(v.out);
				if (v.in != 1 && (v.collected_type[count] == 3 || v.collected_type[count] == 5))
					close(v.in);
				if (v.collected_type[count] == 3)
					v.out = open(v.collected_files[count], O_WRONLY | O_CREAT | O_TRUNC, 0644);
				else if (v.collected_type[count] == 4)
					v.out = open(v.collected_files[count], O_WRONLY | O_CREAT | O_APPEND, 0644);
				else if (v.collected_type[count] == 2)
					v.in = open(v.collected_files[count], O_RDONLY, 0644);
			}
			dup2(v.in, 0);
			dup2(v.out, 1);
			if (v.in != 0)
				close(v.in);
			if (v.out != 1)
				close(v.out);
			if (v.pin != 0)
				close (v.pin);
			execve(v.collected_cmd[0], v.collected_cmd, env);
			dprintf(2, "%s : wrong\n",v.collected_cmd[0]);
			exit(0);
		}
		else
		{
			wait(0);
			// I need to save PIDs inside my struct
			if (v.in != 0)
				close(v.in);
			if (v.out != 1)
				close(v.out);
			v.in = v.pin;
		}

		//free(v.collected_cmd);
		head = head->next;
		v.collected_cmd = NULL;
		//i++;
	}
}