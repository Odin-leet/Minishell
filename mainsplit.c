#include "minishell.h"

void	traitmaskhelper(int i,const char *s, int *env_sq, int *env_dq)
{
	if (s[i] == '\'' && *env_sq == 0)
		*env_sq = 1;
	else if (s[i] == '\'' && *env_sq == 1)
		*env_sq = 0;
	else if (s[i] == '\"' && *env_dq == 0)
		*env_dq = 1;
	else if (s[i] == '\"' && *env_dq == 1)
		*env_dq = 0;
}

int	*traitmask(const char *s, int c)
{
	int				*env;
	int				env_sq;
	int				env_dq;
	unsigned int	i;
	unsigned int	j;

	j = strlen(s);
	env_dq = 0;
	env_sq = 0;
	i = 0;
	env = (int *)malloc(sizeof(int) * (strlen(s)));
	while (i < j)
		env[i++] = 0;
	i = 0;
	while (s[i] != '\0')
	{
		traitmaskhelper(i, s, &env_sq, &env_dq);
		if (c == 1)
			env[i] = env_dq;
		else
			env[i] = env_sq;
		i++;
	}
	return (env);
}

static int	len_word(const char *s, t_split split1, int *in_sgl, int *in_db)
{
	int		i;
	size_t	len;
	int		k;
	char	c;

	len = 0;
	k = split1.k;
	c = split1.c;
	i = 0;
	while (s[i] == c && s[i] != '\0' && (in_sgl[k] == 0 || in_db[k] == 0))
	{
		i++;
		k++;
	}
	while ((s[i] != c && s[i] != '\0') || (s[i] == c
			&& (in_sgl[k] == 1 || in_db[k] == 1)))
	{
		len++;
		i++;
		k++;
	}
	
	return (len);
}

static int	count_word(char *s, char c)
{
	size_t	i;
	size_t	count;
	int		*in_db;
	int		*in_sgl;

	in_db = traitmask(s, 1);
	count = 0;
	in_sgl = traitmask(s, 0);
	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
			count++;
		while ((s[i] != c && s[i] != '\0')
			|| (s[i] == c && (in_sgl[i] == 1 || in_db[i] == 1)))
			i++;
		if (s[i] != '\0')
			i++;
	}
	free(in_db);
	free(in_sgl);
	return (count);
}

int	splithelper(t_split split1, const char *s, char c)
{
	unsigned long	j;
	int				*in_db;
	int				*in_sgl;

	in_db = traitmask(s, 1);
	c = 0;
	in_sgl = traitmask(s, 0);
	split1.split[split1.i] = (char *)malloc(sizeof(char)
			* (len_word(&s[split1.k], split1, in_sgl, in_db) + 1));
	j = 0;
	while (s[split1.k] == split1.c && (in_sgl[split1.k] == 0
			|| in_db[split1.k] == 0))
		split1.k++;
	while ((s[split1.k] != split1.c && s[split1.k] != '\0')
		|| (s[split1.k] == split1.c && (in_sgl[split1.k] == 1
				|| in_db[split1.k] == 1)))
	{
		split1.split[split1.i][j] = s[split1.k];
		split1.k++;
		j++;
	}
	split1.split[split1.i][j] = '\0';
	free(in_db);
	free(in_sgl);
	return (split1.k);
}

char	**ft_split(char *s, char c)
{
	t_split	split1;

	split1.i = -1;
	split1.k = 0;
	split1.c = c;
	split1.split = (char **)malloc(sizeof(char *) * (count_word(s, c) + 1));
	if (!s || !(split1.split))
		return (NULL);
	while (++split1.i < count_word(s, c))
		split1.k = splithelper(split1, s, c);
	split1.split[split1.i] = NULL;
	return (split1.split);
}
