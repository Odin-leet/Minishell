# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

int main(int argc, char **argv,char **env)
{
	char *args[3] = {"/bin/ls", "/usr/bin/wc", NULL};
	pid_t pid;
	int fd[2];
	int stdin = 0;  //input is read from somewhere
	int stdout = 1; //output is written somewhere
	int stderr = 2;
	int i = 0;
// don't turn left :)
	pipe(fd);
	while (i < 1)
	{
		pid = fork();
		if (pid == 0)
		{
			dup2(fd[0], stdin);
			dup2(fd[1], stdout);
			if (fd[1] != 1)
				close(fd[1]);
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
