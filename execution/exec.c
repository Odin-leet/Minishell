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

#include "../minishell.h"

char **cmd_collector(t_linked_list *cmd)
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
	sequance = malloc(sizeof(char *) * (size + 1));
	sequance[size] = NULL;
	size = 0;
	while (cmd != NULL)
	{
		sequance[size] = ft_strdup((char *)cmd->data, 0);
		cmd = cmd->next;
		size++;
	}
	return (sequance);
}

char **files_collector(t_linked_list *lfile)
{
	char **sequance;
	t_linked_list *tempo;
	int size;

	size = 0;
	tempo = lfile;
	while (tempo != NULL)
	{
		tempo = tempo->next;
		size++;
	}
	sequance = malloc(sizeof(char *) * (size + 1));
	sequance[size] = NULL;
	size = 0;
	while (lfile != NULL)
	{
		sequance[size] = ((t_file *)lfile->data)->file;
		lfile = lfile->next;
		size++;
	}
	return (sequance);
}

int *type_collector(t_linked_list *lfile)
{
	int *tab;
	t_linked_list *tempo;
	int size;
	size = 0;
	tempo = lfile;
	while (tempo != NULL)
	{
		tempo = tempo->next;
		size++;
	}
	tab = malloc(sizeof(int *) * (size));

	size = 0;
	while (lfile != NULL)
	{
		tab[size] = ((t_file *)lfile->data)->type;
		printf("tab[size] == %d\n", tab[size]);
		lfile = lfile->next;
		size++;
	}
	return (tab);
}


int	checkforquotes2(char *string)
{
	int i;
	int	count;

	i = 0;
	count = 0;
	while (string[i] != '\0')
	{
		if (string[i] == '\"')
		{
			count++;
			i++;
			if (string[i] == '\"')
			{
				i++;
				count++;
			}
			else
			{
				while (string[i] != '\"' && string[i])
					i++;
				if (string[i] == '\"')
					{
						count++;
						i++;
					}
			}
		}
		if (string[i] == '\'')
		{
			count++;
			i++;
			if (string[i] == '\'')
			{
				i++;
				count++;
			}
			else
			{
				while (string[i] != '\'' && string[i])
					i++;
				if (string[i] == '\'')
					{
						count++;
						i++;
					}
			}
		}
		i++;
	}
	return(count);

}
//void antiquotes(t_vars *v)
//{
//	int i;
//	int j;
//	int k;
//	char **s;
//	char *tmp;
//	i = 0;
//	j = 0;
//	s = NULL;
//	while (v->collected_cmd[i])
//	{
//		j = 0;
//		while (v->collected_cmd[i][j])
//		{
//			if (v->collected_cmd[i][j] == '"')
//			{
//				k = 0;
//				s = ft_split(v->collected_cmd[i], '"');
//				while (s[k])
//					tmp = ft_strjoin(tmp,s[k++]);//leak
//				else
//				{
//					free(v->collected_cmd[i]);
//					v->collected_cmd[i] = s[i];
//				}
//				break;
//			}	
//		}
//		i++;
//		while (s[i])
//		{
//		
//		}
//	}
//}

char	*changecollectedcmd(char *string, int count)
{
	char	*tmp;
	int		i;
	int		c;

	i = 0;
	c = 0;
	tmp = NULL;
	tmp = malloc(sizeof(char) * (ft_strlen(string) - count + 1));
	while (string[i] != '\0')
	{
		if (string[i] == '\"')
		{
			i++;
			if (string[i] == '\"')
			{
				i++;
			}
			else
			{
				while (string[i] != '\"' && string[i])
				{
					tmp[c++] = string[i++];
				}
				if (string[i] == '\"')
					{
						i++;
					}
			}
		}
		if (string[i] == '\'')
		{
			i++;
			if (string[i] == '\'')
			{
				i++;
			}
			else
			{
				while (string[i] != '\'' && string[i])
				{
					tmp[c++] = string[i++];
				}
				if (string[i] == '\'')
					{
						i++;
					}
			}
		}
		if (string[i] != '\0')
		{
		tmp[c] = string[i];
		c++;
		i++;
		}
	}
	tmp[c] = '\0';
	free(string);
	return(tmp);

}
int echo(t_vars *v)
{
	int i;
	int j;
	int n;
	int	count;

	n = 0;
	count = 0;
	i = 1;
	j = 1;
	
	if (!(v->collected_cmd) || !v->collected_cmd[1])
		return (printf("\n"));

	//antiquotes(v);
	if (v->collected_cmd[i][0] == '-')
	{	checkforquotes2(v->collected_cmd[i]);
		while (v->collected_cmd[i][j] == 'n' && v->collected_cmd[i][j] != '\0')
			j++;
		if (v->collected_cmd[i][j] != 'n' &&  v->collected_cmd[i][j - 1] == 'n' 
		&& v->collected_cmd[i][j] == '\0')
			n = 1;
		if (n == 1)
			i = 2;
	}
	while (v->collected_cmd[i])
	{
		count = checkforquotes2(v->collected_cmd[i]);
		v->collected_cmd[i] = changecollectedcmd(v->collected_cmd[i], count);
		if (v->collected_cmd[i + 1])
			printf("%s ", v->collected_cmd[i]);
		else
			printf("%s", v->collected_cmd[i]);
		i++;
	}
	if (n != 1)
		printf("\n");
	return (1);
}

int pwd(void)
{
	char cwwd[256];

	getcwd(cwwd, sizeof(cwwd));
	printf("%s\n", cwwd);
	return (1);
}
// void	ft_cd(t_builtin_vars var, int *retv)
// void	ft_cd_normal_case(t_builtin_vars var, char *dest_path, int *retv)
// int	change_oldpwd(char ***envp)
// int	change_pwd(char ***envp)
// void	ft_cd_oldpwd(t_builtin_vars var, int *retv)
char    *exportenv(t_vars *pl, char *string)
{
    int     i;
    int     count;
    int     c;

    i = 0;
    while(pl->envprinc[i] != NULL)
    {
        count = ft_strlen(string);
        c = thereisequ(pl->envprinc[i]);
        if (c != -1)
        {
            if (count < c)
                count = c;
        }
        else
        {
            c = ft_strlen(pl->envprinc[i]);
            if (count < c)
                count = c;
        }
        if (strncmp(pl->envprinc[i], string, count) == 0)
            return(ft_substr(pl->envprinc[i], count + 1, ft_strlen(pl->envprinc[i]) - count ));
        i++;
    }
    return (NULL);
}
/*cat << d | << hjsd >f
cat << k << f
cat << k > file0 << f> file1*/

int cd(t_vars *v)
{
	char *cwd;
	char *home;
	char *oldpwd;
	char *str;
	int i;

	int ret;

	//cd ~ -> cd
	cwd = malloc(sizeof(char) * PATH_MAX);
	home = exportenv(v, "HOME");
	oldpwd = exportenv(v, "OLDPWD");
	if (!v->collected_cmd[1] && cwd[0] != '/')
		cwd = strcat(cwd, home);
	else if (v->collected_cmd[1])
	{
		str = v->collected_cmd[1];
		if (v->collected_cmd[1][0] == '-')
		{
			i = 0;
			while (str[i])
			{
				if (str[i] != '-')
					return (0);
				i++;
			}
			if (i%2 == 1)
				ret = chdir(oldpwd);
			getcwd(cwd, PATH_MAX);
			replaceenv(v, cwd);
			return(1);
		}
		getcwd(cwd, PATH_MAX);
		free(oldpwd);
		oldpwd = ft_strjoin("OLDPWD=", cwd);
		if (v->collected_cmd[1][0] == '~')
		{
			v->collected_cmd[1][0] = '/';
			str = ft_strjoin(home, v->collected_cmd[1]);
		}
		strcat(cwd, "/");
		strcat(cwd, str);
		i = 2;
		while (v->collected_cmd[i])
		{
			strcat(cwd, " ");
			strcat(cwd, v->collected_cmd[i++]);
		}
	}
	ret = chdir(cwd);
	printf("[%s]\n", cwd);
	free(cwd);
	free(home);
	if (ret == 0)
	{
		replaceenv(v, oldpwd);
		return (1);
	}	
	printf("No such file or directory\n");
	return (0);
}
void file_manager(t_vars *v)
{
	int count;

	count = 0;
	v->collected_files = files_collector(v->lfile);
	v->collected_type = type_collector(v->lfile);
	while (v->collected_files[count])
	{
		if (v->out != 0 && (v->collected_type[count] == 4 || v->collected_type[count] == 3))
			close(v->out);
		else if (v->in != 1 && (v->collected_type[count] == 2 || v->collected_type[count] == 5))
			close(v->in);
		if (v->collected_type[count] == 3)
			v->out = open(v->collected_files[count], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (v->collected_type[count] == 4)
			v->out = open(v->collected_files[count], O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (v->collected_type[count] == 2)
			v->in = open(v->collected_files[count], O_RDONLY, 0644);
		count++;
	}
}
int builtve(t_vars *v)
{
	if (ft_strncmp(v->collected_cmd[0], "echo", ft_strlen(v->collected_cmd[0])) == 0)
		return (echo(v));
	if (ft_strncmp(v->collected_cmd[0], "cd", ft_strlen(v->collected_cmd[0])) == 0)
		return (cd(v));
	if (ft_strncmp(v->collected_cmd[0], "pwd", ft_strlen(v->collected_cmd[0])) == 0)
		return (pwd());
	if (ft_strncmp(v->collected_cmd[0], "unset", ft_strlen(v->collected_cmd[0])) == 0)
		return (unset(v));
	if (ft_strncmp(v->collected_cmd[0], "env", ft_strlen(v->collected_cmd[0])) == 0)
		return (env(v));
	if (ft_strncmp(v->collected_cmd[0], "exit", ft_strlen(v->collected_cmd[0])) == 0)
		exit(1);
	if (ft_strncmp(v->collected_cmd[0], "export", ft_strlen(v->collected_cmd[0])) == 0)
		return (export(v));
	return (0);
}
void exec(t_linked_list *head, t_vars *v)
{ 
	t_linked_list *tmp;
	int fd[2];
	int s_out;
	int i;

	v->in = 0;
	v->pin = 0;
	v->out = 1;
	tmp = head;
	v->cmd_size = 0;
	while (tmp)
	{
		(v->cmd_size)++;
		tmp = tmp->next;
	}
	i = 0;
	v->pid = malloc(sizeof(pid_t) * (v->cmd_size));
	while (head)
	{
		v->lcmd = ((t_command *)head->data)->nameargs;
		v->lfile = ((t_command *)head->data)->files;
		v->collected_cmd = cmd_collector(v->lcmd);
		pipe(fd);
		v->pin = fd[0];
		v->out = fd[1];
		if (!(head->next))
			v->out = 1;
		if (i == 0 && !(head->next) && builtins(v->collected_cmd[0]))
		{
			s_out = dup(1);
			file_manager(v);
			dup2(v->in, 0);
			dup2(v->out, 1);
			if (v->in != 0)
				close(v->in);
			if (v->out != 1)
				close(v->out);
			builtve(v);
			dup2(s_out, 1);
		}
		else
		{
			v->pid[i] = fork();
			if (v->pid[i] == 0)
			{
				file_manager(v);
				//export + redirection + |
				dup2(v->in, 0);
				dup2(v->out, 1);
				if (v->in != 0)
					close(v->in);
				if (v->out != 1)
					close(v->out);
				if (v->pin != 0)
					close(v->pin);
				if (builtins(v->collected_cmd[0]))
					builtve(v);
				else
					execve(v->collected_cmd[0], v->collected_cmd, v->envprinc);
				//dprintf(2,"bash: %s: command not found\n", s[0]);
				exit(0);
			}
			else
			{
				if (v->in != 0)
					close(v->in);
				if (v->out != 1)
					close(v->out);
				v->in = v->pin;
			}
		}

		i++;
		// free(v->collected_cmd);\\ free table in nd out cause we dup the cmd not just assigning the pointer
		// free(v->collected_files);
		// free(v->collected_type);
		head = head->next;
		v->collected_cmd = NULL;
		v->collected_files = NULL;
		v->collected_type = 0;
	}
	i = 0;
	while (i < v->cmd_size)
	{
		waitpid(v->pid[i], &v->exit_status, 0);
		printf("exit status == %d\n", v->exit_status);
		i++;
	}

	free(v->pid);
}
