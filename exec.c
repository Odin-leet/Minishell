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
	int		*ft_strchr(const char *s, int c)
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
	}
	char **collector(t_linked_list *rass)
	{
		//
	}
	/*void whoexec(t_linked_list *cmd)

	{
		if (()
		execsys();
	}*/
	void xv_it(t_vars *vars)
	{
		//execve traitement
	}
	int intializer();
	int exec(t_linked_list *head)
	{
		int i;
		int fd[2];
		t_vars vars;

		pipe(fd);
		i = 0;
		while (head != NULL)
		{
			vars.lcmd = ((t_command*)head->data)->nameargs;
			vars.collected = collector(vars.lcmd); // don't forget to free that shit after xv_it;
			if (issyscall((char *)vars.lcmd->data) == 1)
				xv_it(&vars);
			else if (handle_it(head)) ;
				//call collector use it then free collected
				// I should use cmd head instead of the principal head !![done]
			vars.lfile = ((t_command*)head->data)->files;
			while (vars.lcmd != NULL || vars.lfile != NULL)
			{
				if (vars.lcmd != NULL)
				{
					printf("-%d\ncmd : %s\n",i,(char *)vars.lcmd->data);
					vars.lcmd = vars.lcmd->next;
				}	
				if (vars.lfile != NULL)
				{
					printf("- %d \nfile : %s\ntype : %d\n",i,((t_file*)vars.lfile->data)->file,((t_file*)vars.lfile->data)->type);
					whoexec(head);
					vars.lfile = vars.lfile->next;
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
