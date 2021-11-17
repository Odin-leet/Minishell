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
// /*char	*ft_strchr(const char *s, int c)
// {
// 	while (*s != '\0')
// 	{
// 		if (*s == c)
// 			return ((char *)s);
// 		s++;
// 	}
// 	if (c == '\0')
// 		return ((char *)s);
// 	return (0);
// }*/
// void whoexec(t_linked_list *cmd)
// {
// 	//if (()
// 	//execsys();
// }
// int intializer();
// int exec(t_linked_list *head)
// {
// 	int i;
// 	int fd[2];
// 	int in;
// 	int out;
// 	int pvin;

// 	t_linked_list *lcmd;
// 	t_linked_list *lfile;
// 	pipe(fd);
// 	i = 0;
// 	while (head != NULL)
// 	{
// 		lcmd = ((t_command*)head->data)->nameargs;
// 		lfile = ((t_command*)head->data)->files;
// 		while (lcmd != NULL || lfile != NULL)
// 		{
// 			if (lcmd != NULL)
// 			{
// 				printf("-%d\ncmd : %s\n",i,(char *)lcmd->data);
				
// 				lcmd = lcmd->next;
// 			}	
// 			if (lfile != NULL)
// 			{
// 				printf("- %d \nfile : %s\ntype : %d\n",i,((t_file*)lfile->data)->file,((t_file*)lfile->data)->type);
// 				whoexec(head);
// 				lfile = lfile->next;
// 			}
// 			i++;
// 		}
// 		head = head->next;
// 		printf("there is pipe here  \n");
// 	}
//     return 0;
// }

// int main(int argc, char **argv)
// {
// 	char *args[3] = {"/bin/ls","/bin/ls", "/usr/bin/wc"};
// 	pid_t pid;
// 	int fd[2];
// 	int in = 0;
// 	int pin = 0;
// 	int out = 1;

// 	pipe(fd);
// 	//pin = fd[0];
// 	//out = fd[1];
// 	printf("pin : %d\nout : %d\nin : %d, fd[0] : %d\nfd[1] : %d\n", pin,out, in,fd[0],fd[1]);
// 	for(int i = 0; i < 3; i++)
// 	{
// 		if (i == 1) 
// 			fd[out] = 1;
// 		pid = fork();
// 		if (pid == 0)
// 		{
// 			dup2(in, 0); // duplicate stdin into in = 0
// 			dup2(fd[out], 1); // duplicate stdout into out = 4
// 			if (fd[pin] != 0) // pin = 3 -> close(3);
// 				close(fd[pin]);
// 			if (in != 0) // in = 0 
// 				close(in);
// 			if (fd[out] != 1) // out = 4 -> close(4);
// 				close(fd[out]);
// 			execve(args[i], &argv[i], 0);
// 		}
// 		else
// 		{
// 			waitpid(pid, NULL, 0);
// 			if (fd[out] != 1)// out = 4 -> close(4);
// 				close(fd[out]);
// 			if (in != 0)// in = 0
// 				close(in);
// 			in = fd[pin];
// 		}
// 	}
// 	return (0);
// }

int main(int argc, char **argv)
{
	char *args[3] = {"/bin/ls","/bin/ls", "/usr/bin/wc"};
	pid_t pid;
	int fd[2];
	int in = 0;
	int pin = 0;
	int out = 1;
	int i;

	pipe(fd);
	//pin = fd[0];
	//out = fd[1];
	printf("pin : %d\nout : %d\nin : %d, fd[0] : %d\nfd[1] : %d\n", pin,out, in,fd[0],fd[1]);
	/*if (i == 1) 
			fd[out] = 1;*/
	
	while(i < 3)
	{
		pid = fork();
		if (pid == 0)
		{
			if (i == 0) 
			dup2(fd, 0) ; // duplicate stdin into in = 0
			dup2(fd[out], 1); // duplicate stdout into out = 4
			if (fd[pin] != 0) // pin = 3 -> close(3);
				close(fd[pin]);
			if (in != 0) // in = 0 
				close(in);
			if (fd[out] != 1) // out = 4 -> close(4);
				close(fd[out]);
			execve(args[i], &argv[i], 0);
		}
		else
		{
			waitpid(pid, NULL, 0);
			if (fd[out] != 1)// out = 4 -> close(4);
				close(fd[out]);
			if (in != 0)// in = 0
				close(in);
			in = fd[pin];
		}
		i++;
	}
	return (0);
}
pid = fork();
	// if (pid < 0)
	// 	exit_fatal();
	else if (pid == 0) //child
	{
		dup2(temp->fd[1], STDOUT);
		dup2(temp->prev->fd[0], STDIN) < 0
		execve(temp->argv[0], temp->argv, env);
		exit(EXIT_SUCCESS);
	}
	else //parent
	{
		waitpid(pid, NULL, 0);
		if (pipe_open)
		{
			close(temp->fd[1]);
			close(temp->fd[0]);
		}
		if (temp->prev && temp->prev->type == TYPE_PIPE)
			close(temp->prev->fd[0]);
	}
/*                                                                         
void    ft_pipe_exec(int pipes, char **args, char **envp)
{
    pid_t pid[pipes + 2];
    int fd[pipes][2];
    int j = 0;
    int stop = 0;
    int stats = 0;

    for (int k = 0; *args != NULL; k++)
    {
        int q = 0;
        if (pipe(fd[j]) < 0)
            ft_exit_error("error: fatal");
        for (; args[q] != NULL; q++)
        {
            if (!strcmp(args[q], "|"))
            {
                stop = 0;
                args[q] = NULL;
                break ;
            }
            stop = 1;
        }
        if ((pid[k] = fork()) < 0)
            ft_exit_error("error: fatal");
        else if(pid[k] == 0)
        {
            if (j == 0)
            {
                if (dup2(fd[0][1], 1) < 0)
                    ft_exit_error("error: fatal");
                if (close(fd[0][0]) < 0)
                    ft_exit_error("error: fatal");
            }
            else if (j == pipes)
            {
                if (dup2(fd[j - 1][0], 0) < 0)
                    ft_exit_error("error: fatal");
            }
            else
            {
                if (dup2(fd[j - 1][0], 0) < 0)
                    ft_exit_error("error: fatal");
                if (dup2(fd[j][1], 1) < 0)
                    ft_exit_error("error: fatal");
                if (close(fd[j][0]) < 0)
                    ft_exit_error("error: fatal");
            }
            if (execve(args[0], args, envp) < 0)
                ft_exit_error("error: fatal");
            exit(1);
        }
        if (j == 0)
        {
            if (close(fd[0][1]) < 0)
                ft_exit_error("error: fatal");
        }
        else if (j == pipes)
        {
            if (close(fd[j - 1][0]) < 0)
                ft_exit_error("error: fatal");
        }
        else
        {
            if (close(fd[j][1]) < 0)
                ft_exit_error("error: fatal");
            if (close(fd[j - 1][0]) < 0)
                ft_exit_error("error: fatal");
        }
        args += q + 1;
        j++;
        if (stop)
            break ;
    }
    for (int kk = 0; kk <= pipes; kk++)
        if (waitpid(pid[kk], &stats, 0) < 0)
            ft_exit_error("error: fatal");
}*/