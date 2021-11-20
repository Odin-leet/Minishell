void exec(t_linked_list *head, char **env)
{
	t_vars v;
	int fd[2];
	int i;
	char **ss;
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
		
		pipe(fd);
		v.pin = fd[0];
		v.out = fd[1];
		if (!(head->next))
			v.out = 1;
		
		v.pid = fork();
		if (v.pid == 0)
		{

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
		i++;
	}
}