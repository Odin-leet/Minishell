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
	sequance = malloc(sizeof(char*) * size + 1);
	sequance[size] = NULL;
	size = 0;
	while(cmd != NULL)
	{
		sequance[size] = (char *)cmd->data;
		cmd = cmd->next;
		printf("sequence == |%s|\n",sequance[size]);
		size++;
	}
	return (sequance);
}
// void whoexec(t_linked_list *cmd)
// {}	//if (()	execsys();

// void xv_it(t_vars *vars)
// {
// 	//execve traitement i should use pipes here and it's gonna be the same process even if there is no xv
// }
// int issyscall(char *string)
// {
// 	return (thereisslach(string));// repeated function call just to make sense
// }
//  int intializer();
//  int exec(t_linked_list *head)
//  {
//  	int i;
//  	int fd[2];
//  	t_vars vars;
//  	pipe(fd);
//  	i = 0;
//  	while (head != NULL)
//  	{
//  		vars.lfile = ((t_command*)head->data)->files;
//  		vars.lcmd = ((t_command*)head->data)->nameargs;
//  		vars.collected = collector(vars.lcmd); // only free the collector after setting his values to NULL after they stop pointing to our cmd struct
 		
// 		 while (vars.lcmd != NULL || vars.lfile != NULL)
//  		{
//  			if (vars.lcmd != NULL)
// 			{
// 				if (issyscall((char *)vars.lcmd->data) == 1)
// 					xv_it(&vars);
// 				else
// 				{	handle_it(head) ;
// 					return(0);
// 				}
// 				 printf("-%d\ncmd : %s\n",i,(char *)vars.lcmd->data);
//  				vars.lcmd = vars.lcmd->next;
//  			}
//  			if (vars.lfile != NULL)
//  			{
//  				printf("- %d \nfile : %s\ntype : %d\n",i,((t_file*)vars.lfile->data)->file,((t_file*)vars.lfile->data)->type);
//  				whoexec(head);
//  				vars.lfile = vars.lfile->next;
//  			}
//  			i++;
//  		}
//  		head = head->next;
//  		printf("there is pipe here  \n");
//  	}
//  	return 0;
//  }			
// int has_infile(t_linked_list file);

// int has_outfile(t_linked_list file);
// int main(int argc, char **argv, char **env)
// {
// 	char *args[3] = {"/bin/ls", "/bin/ls","/usr/bin/wc"};
// 	pid_t pid;
// 	int fd[2];
// 	int in = 0;
// 	int pin = 0;
// 	int out = 1;
// 	int i = 0;
	
// 	while (i<3)
// 	{
// 		perror(args[i]);
// 		pipe(fd);
// 		pin = fd[0];
// 		out = fd[1];
// 		if (i == 2)
// 			out = 1;
// 		dprintf(2, "%d| %d\n",in ,out );
// 		pid = fork();
// 		if(pid == 0)
// 		{
// 			dup2(in, 0);
// 			dup2(out, 1);
// 			if(in != 0)
// 				close(in);
// 			if (out != 1)
// 				close(out);
// 			// if (pin != 0)
// 			// 	close (pin);
// 			execve(args[i], argv, env);
// 			dprintf(2, "%s\n", args[i]);
// 			exit(0);
// 		}else
// 		{
// 			if (in != 0)
// 				close(in);
// 			if (out != 1)
// 				close(out);
// 			in = pin;
// 			i++;
// 		}
		
// 	}
// 	return (0);
// }

		// Last element condition 
		// mid condition 
		// has file por not
		// link the pipes
		/*if (i == 1)
			fd[out] = 1;
		pid = fork();
		if (pid == 0)
		{
			dup2(fd[in], 0);
			dup2(fd[out], 1);
			if (pin != 0)
				close(pin);
			if (fd[in] != 0)
				close(in);
			if (fd[out] != 1)
				close(fd[out]);*/