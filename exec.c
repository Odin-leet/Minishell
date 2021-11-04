#include "minishell.h"

void whoexec(t_linked_list cmd)
{
    
}
int intializer()
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
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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