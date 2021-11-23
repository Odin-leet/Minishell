#include "minishell.h"

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
	{
		env[i] = 0;
		i++;
	}
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\'' && env_sq == 0)
			env_sq = 1;
		else if (s[i] == '\'' && env_sq == 1)
			env_sq = 0;
		else if (s[i] == '\"' && env_dq == 0)
			env_dq = 1;
		else if (s[i] == '\"' && env_dq == 1)
			env_dq = 0;
		if (c == 1)
			env[i] = env_dq;
		else
			env[i] = env_sq;
		i++;
	}
	return (env);
}

static int	len_word(const char *s, char c, int *in_sgl, int *in_db, int k)
{
	int		i;
	size_t	len;

	len = 0;
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
	free(in_db);
	free(in_sgl);
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

int	splithelper(int i, const char *s, int k, char **split, char c)
{
	unsigned long	j;
	int				*in_db;
	int				*in_sgl;

	in_db = traitmask(s, 1);
	in_sgl = traitmask(s, 0);
	split[i] = (char *)malloc(sizeof(char)
			* (len_word(&s[k], c, in_sgl, in_db, k) + 1));
	j = 0;
	while (s[k] == c && (in_sgl[k] == 0 || in_db[k] == 0))
		k++;
	while ((s[k] != c && s[k] != '\0')
		|| (s[k] == c && (in_sgl[k] == 1 || in_db[k] == 1)))
	{
		split[i][j] = s[k];
		k++;
		j++;
	}
	split[i][j] = '\0';
	return (k);
}

char	**ft_split(char *s, char c)
{
	int		i;
	size_t	k;
	char	**split;

	i = -1;
	k = 0;
	split = (char **)malloc(sizeof(char *) * (count_word(s, c) + 1));
	if (!s || !(split))
		return (NULL);
	while (++i < count_word(s, c))
		k = splithelper(i, s, k, split, c);
	split[i] = NULL;
	return (split);
}
