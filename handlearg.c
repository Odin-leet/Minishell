#include "minishell.h"

int	builtins(char *string)
{
	if (ft_strncmp(string, "echo", ft_strlen(string)) == 0)
		return (1);
	if (ft_strncmp(string, "cd", ft_strlen(string)) == 0)
		return (1);
	if (ft_strncmp(string, "pwd", ft_strlen(string)) == 0)
		return (1);
	if (ft_strncmp(string, "unset", ft_strlen(string)) == 0)
		return (1);
	if (ft_strncmp(string, "env", ft_strlen(string)) == 0)
		return (1);
	if (ft_strncmp(string, "exit", ft_strlen(string)) == 0)
		return (1);
	if (ft_strncmp(string, "export", ft_strlen(string)) == 0)
		return (1);
	return (0);
}

char	*checkforpath(char *string, char *str)
{
	DIR				*dir;
	struct dirent	*sd;

	dir = opendir(string);
	if (dir == NULL)
	{
		printf("there is no file\n");
		return (0);
	}
	sd = readdir(dir);
	while (sd != NULL)
	{
		if (strncmp(sd->d_name, str, ft_strlen(sd->d_name)) == 0)
		{
			(void)closedir(dir);
			return (string);
		}
		sd = readdir(dir);
	}
	(void)closedir(dir);
	return (NULL);
}

int	thereisslach(char *string)
{
	int	i;

	i = 0;
	while (string[i] != '\0')
	{
		if (string[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

char	*elsefunctionhelper(char *string, char **tab, int i, char *tmp)
{
	char	*tmp3;
	char	*tmp2;

	tmp3 = NULL;
	tmp2 = NULL;
	tmp2 = checkforpath(tab[i], string);
	if (tmp2 != NULL)
	{
		tmp3 = tab[i];
		tab[i] = ft_strjoin(tab[i], "/");
		free(tmp3);
		tmp3 = ft_strjoin(tab[i], string);
		free_pre(tab, 0);
		free(tmp);
		free(string);
		return (tmp3);
	}
	if (!(tmp2))
		free(tmp2);
	return (NULL);
}

int	findenvi(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (i);
		i++;
	}
	return (-1);
}

char	*elsefunction(char *string, char **env)
{
	int		i;
	char	*tmp;
	char	**tab;
	char	*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	i = findenvi(env);
	if (i != -1)
	tmp = ft_strdup(env[i], 5);
	else
	{
		printf("bash: %s: No such file or directory \n", string);
		return (0);
	}
	tab = ft_split1(tmp, ':');
	i = 0;
	while (tab[i] != NULL)
	{
		tmp2 = elsefunctionhelper(string, tab, i, tmp);
		if (tmp2 != NULL)
			return (tmp2);
		i++;
	}
	free_pre(tab, 0);
	free(tmp);
	return (string);
}

char	*handleargshelper(char *string, int j, char *ptr, char *ptr2)
{
	int	i;

	i = 0;
	while (string[i] != '\0')
	{
		if (string[i] == '/')
			j = i;
		i++;
	}
	ptr = ft_substr(string, 0, j);
	ptr2 = ft_strdup(string, j + 1);
	if (checkforpath(ptr, ptr2) == NULL)
	{
		free(ptr);
		free(ptr2);
		return (string);
	}
	free(ptr2);
	free(ptr);
	return (string);
}

char	*handleargs(char *string, char **env)
{
	char	*ptr;
	char	*ptr2;
	int		j;

	j = 0;
	ptr = NULL;
	ptr2 = NULL;
	if (builtins(string) == 1)
		return (string);
	else if (thereisslach(string) == 1)
	{
		string = handleargshelper(string, j, ptr, ptr2);
	}
	else
		string = elsefunction(string, env);
	return (string);
}
