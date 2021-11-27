#include "minishell.h"
#include <string.h>

int	ft_isalpha2(int c)
{
	unsigned char	k;

	k = (unsigned char)c;
	if (c <= 90 && c >= 65)
		return (1);
	else if (c >= 97 && c <= 122)
		return (1);
	else
		return (0);
}

int	returncount(char *string, char *tmp, int i, int j)
{	
	int	count;

	i = 0;
	count = 0;
	j = 0;
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

int	returnthereisenv(int count, int count2, char **env, char *tmp)
{
	int	i;
	int	j;
	int	count3;

	i = 0;
	j = 0;
	count3 = count;
	while (env[i] != NULL)
	{
		j = 0;
		count3 = count;
		while (env[i][j] != '\0')
		{
			if (env[i][j] == '=')
			{
				count2 = j;
				break ;
			}
			j++;
		}
			if (env[i][j] == '\0')
				count2 = j;
		if (count2 > count)
			count3 = count2;
		if (strncmp(tmp, env[i], count3) == 0)
		{
			free(tmp);
			return (1);
		}
		i++;
	}
	return (0);
}

int	checkifthereisenv(char **env, char *string)
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
	j = 0;
	count = returncount(string, tmp, i, j);
	if (returnthereisenv(count, count2, env, tmp) == 1)
		return (1);
	free(tmp);
	return (0);
}

void	replaceeenv2(t_vars *pl, char *tmp, int i, int c)
{
	int	j;

	j = 0;
	c = 0;
	i = 0;
	while (pl->env1[i])
	{
		j = ft_strlen(pl->env1[i]);
		c = 0;
		while (pl->env1[i][c])
		{
			if (pl->env1[i][c] == '=')
				j = c;
			c++;
		}
		if (strncmp(tmp, pl->env1[i], j) == 0)
		{
			free(pl->env1[i]);
			pl->env1[i] = NULL;
			pl->env1[i] = tmp;
		}
		i++;
	}
}

void	replaceeenv1(t_vars *pl, char *string1, int i, int c)
{
	int	j;

	i = 0;
	c = 0;
	j = 0;
	while (pl->envprinc[i])
	{
		j = ft_strlen(pl->envprinc[i]);
		c = 0;
		while (pl->envprinc[i][c] != '\0')
		{
			if (pl->envprinc[i][c] == '=')
				j = c;
			c++;
		}
		if (strncmp(string1, pl->envprinc[i], j) == 0)
		{
			(free(pl->envprinc[i]));
			pl->envprinc[i] = NULL;
			pl->envprinc[i] = string1;
		}
		i++;
	}
}

void	replaceenv(t_vars *pl, char *string)
{
	int		i;
	char	*tmp;
	int		j;
	int		c;
	char	*string1;

	c = 0;
	j = 0;
	i = 0;
	string1 = strdup(string);
	c = thereisequ(string);
	tmp = traitement1(string1, c);
	replaceeenv2(pl, tmp, i, c);
	replaceeenv1(pl, string1, i, c);
}

int	counttab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char	**remplirtmp(char **tmp1, char **env, char *string, int c)
{
	size_t	j;

	c = 0;
	j = 0;
	while (env[c])
	{
		j = 0;
		while (env[c][j])
		{
			tmp1[c][j] = env[c][j];
			j++;
		}
		tmp1[c][j] = '\0';
		c++;
	}
	tmp1[c] = malloc(sizeof(char ) * (ft_strlen(string)+ 1));
	j = 0;
	while (j < ft_strlen(string))
	{
		tmp1[c][j] = string[j];
		j++;
	}
	tmp1[c][j] = '\0';
	tmp1[++c] = NULL;
	return (tmp1);
}

void	freesomething(char *tmp, t_vars *pl)
{
	free(tmp);
	free_pre(pl->env1, 0);
	free_pre(pl->envprinc, 0);
}

void	addenvfinal(char **tmp1, char **tmp3, t_vars *pl, char *tmp)
{
	freesomething(tmp, pl);
	pl->env1 = tmp1;
	pl->envprinc = tmp3;
}

void	addenvhelperif( char **tmp3, char **tmp1, char *string, t_vars *pl)
{
	char	*tmp;
	int		c;

	c = thereisequ(string);
	tmp = NULL;
	tmp = traitement1(string, c);
	tmp1 = malloc(sizeof(char *) * (counttab(pl->env1) + 2));
	tmp3 = malloc(sizeof(char *) * (counttab(pl->envprinc) + 2));
	c = 0;
	while (pl->env1[c] != NULL)
	{
		tmp1[c] = malloc(sizeof(char *) * (ft_strlen(pl->env1[c]) + 1));
		c++;
	}
	c = 0;
	while (pl->envprinc[c] != NULL)
	{
		tmp3[c] = malloc(sizeof(char *) * (ft_strlen(pl->envprinc[c]) + 1));
		c++;
	}
	tmp1 = remplirtmp(tmp1, pl->env1, tmp, c);
	tmp3 = remplirtmp(tmp3, pl->envprinc, string, c);
	addenvfinal(tmp1, tmp3, pl, tmp);
}

void	addenvhelperelse( char **tmp3, char **tmp1, char *string, t_vars *pl)
{
	char	*tmp;
	int		c;

	tmp = NULL;
	tmp = traitement2(string);
	tmp1 = malloc(sizeof(char *) * (counttab(pl->env1) + 2));
	tmp3 = malloc(sizeof(char *) * (counttab(pl->envprinc) + 2));
	c = 0;
	while (pl->env1[c] != NULL)
	{
		tmp1[c] = malloc(sizeof(char *) * (ft_strlen(pl->env1[c]) + 1));
		c++;
	}
	c = 0;
	while (pl->envprinc[c] != NULL)
	{
		tmp3[c] = malloc(sizeof(char *) * (ft_strlen(pl->envprinc[c]) + 1));
		c++;
	}
	tmp1 = remplirtmp(tmp1, pl->env1, tmp, c);
	tmp3 = remplirtmp(tmp3, pl->envprinc, string, c);
	addenvfinal(tmp1, tmp3, pl, tmp);
}

char	**addenv2(char *string, t_vars *pl)
{
	int		c;
	char	**tmp1;
	char	**tmp3;
	size_t	j;

	tmp3 = NULL;
	tmp1 = NULL;
	j = 0;
	c = 0;
	c = thereisequ(string);
	if (c != -1)
	{
		addenvhelperif(tmp3, tmp1, string, pl);
	}
	else
		addenvhelperelse(tmp3, tmp1, string, pl);
	return (NULL);
}

char	**addenv(t_vars *pl, char *string)
{
	int	i;
	int	c;

	i = 0;
	c = checkifthereisenv(pl->env1, string);
	if (c == 1)
	{
		while (string[i])
		{
			if (string[i] == '=')
			{
				replaceenv(pl, string);
				c = -1;
			}
			i++;
		}
	}
	else
	{
		i = 0;
		addenv2(string, pl);
	}
	return (NULL);
}

int	errorexport2(void)
{
	printf("bash: export: quotes error \n");
	return (1);
}

int	errorexport(char *string)
{
	printf("bash: export: %s : not a valid identifier\n", string);
	return (1);
}

int	checkifthereisquotes(char *string)
{
	int	i;
	int	db_q;
	int	sgl_q;

	i = 0;
	db_q = 0;
	sgl_q = 0;
	while (string[i] != '\0')
	{
		if (string[i] == '\"' && sgl_q == 0)
			db_q++;
		if (string[i] == '\'' && db_q == 0)
			sgl_q++;
		if (string[i] == '\"' && ((sgl_q % 2) != 0))
			return (errorexport(string));
		if (string[i] == '\'' && ((db_q % 2) != 0))
			return (errorexport(string));
		i++;
	}
	if (sgl_q % 2 != 0 || db_q % 2 != 0)
		return (errorexport2());
	return (0);
}

int	returnquotescount(char *string)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (string[i] != '\0')
	{
		if (string[i] == '\"')
			count++;
		if (string[i] == '\'')
			count++;
		i++;
	}
	return (count);
}

void	checkforquotes(char **string)
{
	int		i;
	int		c;
	int		count;
	char	*tmp;

	i = -1;
	c = 0;
	count = returnquotescount(*string);
	tmp = malloc(sizeof(char) * (ft_strlen(*string) - count + 1));
	i = 0;
	while ((*string)[i] != '\0')
	{
		if (!((*string)[i] == '\'' || (*string)[i] == '\"'))
			tmp[c++] = (*string)[i];
		i++;
	}
	tmp[c] = '\0';
	free(*string);
	*string = tmp;
}

int	checkifitscomp(char **string)
{
	int	i;

	i = 0;
	checkforquotes(string);
	if (i == 0 && (*string)[i] == '=')
		return (1);
	while ((*string)[i] != '\0' && (*string)[i] != '=')
	{
		if ((*string)[i] != '_' && (ft_isdigit((*string)[i]) == 0)
			&& (ft_isalpha2((*string)[i]) == 0))
			return (1);
		i++;
	}
	return (0);
}

int	exporthelper(t_vars *pl)
{
	int	i;

	i = 1;
	while (pl->collected_cmd[i] != NULL)
	{
		if (checkifthereisquotes(pl->collected_cmd[i]) == 1)
			return (0);
		if (checkifitscomp(&pl->collected_cmd[i]) == 1)
		{
			printf("error of export\n");
			return (0);
		}
		else
			addenv(pl, pl->collected_cmd[i]);
		i++;
	}
	return (1);
}

int	export(t_vars *pl)
{
	int	i;

	i = 1;
	if (pl->collected_cmd[1] == NULL)
	{
		i = 0;
		while (pl->env1[i])
		{
			printf("%s \n", pl->env1[i]);
			i++;
		}
	}
	else
	{
		if (exporthelper(pl) == 0)
			return (0);
	}
	return (1);
}

int	env(t_vars *pl)
{
	int	i;

	i = 0;
	if (pl->collected_cmd[1] != NULL)
	{
		printf("env: %s: No such file or directory\n", pl->collected_cmd[1]);
		return (0);
	}
	while (pl->envprinc[i] != NULL)
	{
		if (thereisequ(pl->envprinc[i]) != -1)
			printf("%s\n", pl->envprinc[i]);
		i++;
	}
	return (1);
}
