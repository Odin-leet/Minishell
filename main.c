# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

int main(int argc, char **argv,char **env)
{
	char *args[3] = {"/bin/ls", "-la", 0};
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
			printf("%s nothing here\n", argv[i]);
			execve(args[0], args, env);
			// if (execve(args[i], &argv[i], 0) != 1)
			// {
			//     printf("wrong shit happend\n");
			//     return 0;
			// }
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