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
/*char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (0);
}*/
/*void whoexec(t_linked_list *cmd)
{
	if (()
	execsys();
}*/
int intializer();
int exec(t_linked_list *head)
{
	int i;
	int fd[2];
	int in;
	int out;
	int pvin;

	t_linked_list *lcmd;
	t_linked_list *lfile;
	pipe(fd);
	i = 0;
	while (head != NULL)
	{
		lcmd = ((t_command*)head->data)->nameargs;
		lfile = ((t_command*)head->data)->files;
		while (lcmd != NULL || lfile != NULL)
		{
			if (lcmd != NULL)
			{
				printf("-%d\ncmd : %s\n",i,(char *)lcmd->data);
				lcmd = lcmd->next;
			}	
			if (lfile != NULL)
			{
				printf("- %d \nfile : %s\ntype : %d\n",i,((t_file*)lfile->data)->file,((t_file*)lfile->data)->type);
				whoexec(head);
				lfile = lfile->next;
			}
			i++;
		}
		head = head->next;
		printf("there is pipe here  \n");
	}
    return 0;
}

int main(int argc, char **argv)
{
	char *args[3] = {"/bin/ls", "/usr/bin/wc"};
	pid_t pid;
	int fd[2];
	int in = 0;
	int pin = 0;
	int out = 1;

	pipe(fd);
	pin = fd[0];
	out = fd[1];
	for(int i = 0; i < 2; i++)
	{
		/*last cmd out should be [1]
		*/
		if (i == 1)
			out = 1;
		pid = fork();
		if (pid == 0)
		{
			dup2(in, 0);
			dup2(out, 1);
			if (pin != 0)
				close(pin);
			if (in != 0)
				close(in);
			if (out != 1)
				close(out);
			execve(args[i], &argv[i], 0);
		}
		else
		{
			if (out != 1)
				close(out);
			if (in != 0)
				close(in);
			in = pin;
		}
	}
	return (0);
}
