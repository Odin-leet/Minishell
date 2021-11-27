#include "minishell.h"
#include <string.h>

int	unsetreturncount(char *string, char *tmp)
{
	int	j;
	int	count;

	j = 0;
	count = 0;
	if (strchr(string, '=') != NULL)
	{
		while (tmp[j])
		{
			if (tmp[j] == '=')
			{
				count = j;
				break ;
			}
			j++;
		}
	}
	else
		count = ft_strlen(tmp);
	return (count);
}

int	unsetcheckenv(int i, int count, char **env, int count2)
{
	int	j;

	j = 0;
	while (env[i][j] != '\0')
	{
		if (env[i][j] == '=')
		{
			count2 = j;
			break ;
		}
		j++;
		if (env[i][j] == '\0')
			count2 = j;
	}
	if (count2 > count)
		count2 = count;
	return (count2);
}

int	checkifthereisenv2(char **env, char *string)
{
	int		i;
	int		count;
	int		count2;
	int		j;
	char	*tmp;

	count2 = 0;
	tmp = NULL;
	i = 0;
	tmp = ft_strjoin("declare -x ", string);
	count = unsetreturncount(string, tmp);
	while (env[i] != NULL)
	{
		j = 0;
		count2 = unsetcheckenv(i, count, env, count2);
		if (strncmp(tmp, env[i], count) == 0)
		{
			free(tmp);
			return (1);
		}
		i++;
	}
	free(tmp);
	return (0);
}

int	unsetenv1returncount(char **env, char *tmp, int count, int i)
{
	int	j;

	i = -1;
	while (env[++i] != NULL)
	{
		j = 0;
		while (env[i][j] != '\0')
		{
			if (env[i][j] == '=')
			{
				count = j;
				break ;
			}
			j++;
			if (env[i][j] == '\0')
				count = j;
		}
		if (strncmp(tmp, env[i], count) == 0)
		{
			count = i;
			break ;
		}
	}
	return (count);
}

char	**unsettaballoc(char **env, char **tmp, int count)
{
	int	c;
	int	i;

	i = 0;
	c = 0;
	while (env[i] != NULL)
	{
		if (i == count)
			i++;
		else
		{
			tmp[c] = malloc(sizeof(char) * (ft_strlen(env[i]) + 1));
			c++;
			i++;
		}
	}
	return (tmp);
}

char	**remplirtableunset(char **env, char **tmp, int count, int i)
{
	int	c;
	int	j;

	c = 0;
	j = 0;
	while (env[i] != NULL)
	{
		j = 0;
		if (i == count)
			i++;
		else
		{
			while (env[i][j] != '\0')
			{
				tmp[c][j] = env[i][j];
				j++;
			}
			tmp[c][j] = '\0';
			i++;
			c++;
		}
	}
	tmp[c] = NULL;
	return (tmp);
}

void	unsetenv1(t_vars *pl, char *string)
{
	char	**tmp1;
	char	**tmp2;
	char	*tmp;
	int		count;
	int		i;

	i = 0;
	count = 0;
	tmp2 = malloc(sizeof(char *) * (counttab(pl->env1)));
	tmp1 = malloc(sizeof(char *) * (counttab(pl->envprinc)));
	tmp = ft_strjoin("declare -x ", string);
	count = unsetenv1returncount(pl->env1, tmp, count, i);
	tmp2 = unsettaballoc(pl->env1, tmp2, count);
	i = 0;
	tmp2 = remplirtableunset(pl->env1, tmp2, count, i);
	i = 0;
	count = unsetenv1returncount(pl->envprinc, string, count, i);
	tmp1 = unsettaballoc(pl->envprinc, tmp1, count);
	i = 0;
	tmp1 = remplirtableunset(pl->envprinc, tmp1, count, i);
	free_pre(pl->env1, 0);
	free_pre(pl->envprinc, 0);
	free(tmp);
	pl->env1 = tmp2;
	pl->envprinc = tmp1;
}

int	checkifitscomp1(char *string)
{
	int	i;

	i = 0;
	if (i == 0 && string[i] != '_' && (ft_isalpha2(string[i]) == 0))
		return (1);
	while (string[i] != '\0')
	{
		if (string[i] != '_' && (ft_isdigit(string[i]) == 0)
			&& (ft_isalpha2(string[i]) == 0))
			return (1);
		i++;
	}
	return (0);
}	

int	unset(t_vars *pl)
{
	int	i;

	i = 1;
	while (pl->collected_cmd[i])
	{
		if (checkifitscomp1(pl->collected_cmd[i]) == 1)
		{
			printf("bash: unset: `%s': not a valid identifier\n",
				pl->collected_cmd[i]);
			return (1);
		}
		else if (checkifthereisenv2(pl->env1, pl->collected_cmd[i]) == 1)
		{
			unsetenv1(pl, pl->collected_cmd[i]);
		}
		i++;
	}
	return (0);
}
