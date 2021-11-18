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
char **collector(t_linked_list *cmd)
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
void exec(t_linked_list *head, char **env)
{
	t_linked_list *cmd;
	char **s;
	pid_t pid;
	int fd[2];
	int in;
	int pin;
	int out;
	in = 0;
	pin = 0;
	out = 1;
	int t = 0;
	while (head)
	{
		cmd = ((t_command *)head->data)->nameargs;
		s = collector(cmd);
		pipe(fd);
		pin = fd[0];
		out = fd[1];
		if (!(head->next))
			out = 1;
		
		pid = fork();
		if (pid == 0)
		{
			dup2(in, 0);
			dup2(out, 1);
			if (in != 0)
				close(in);
			if (out != 1)
				close(out);
			// if (pin != 0)
			// 	close (pin);
			execve(s[0], s, env);
			dprintf(2, "%s : wrong\n",s[0]);
			//dprintf(2, "%s : wrong\n",s[0]);
			exit(0);
		}
		else
		{
			wait(0);
			if (in != 0)
				close(in);
			if (out != 1)
				close(out);
			in = pin;
		}
		//free(s);
		head = head->next;
		s = NULL;
		t++;
	}
}