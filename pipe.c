
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
}