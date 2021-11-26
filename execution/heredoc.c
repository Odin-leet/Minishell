#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (s1[i] == '\0')
		return (-(unsigned char)s2[i]);
	if (s2[i] == '\0')
		return ((unsigned char)s1[i]);
	return (0);
}









int	heredocs_finder(char **cmd_tab)
{
	int		i;
	char	*filename;

	i = 0;
	while (cmd_tab != NULL && cmd_tab[i] != NULL)
	{
		if (!ft_strcmp(cmd_tab[i], "<<") && cmd_tab[i + 1] != NULL)
		{
			filename = ft_random_name();
			if (here_doc(cmd_tab[i + 1], filename))
			{
				free(filename);
				ft_free_args(cmd_tab);
				return (1);
			}
			free(cmd_tab[i]);
			cmd_tab[i] = ft_strdup("<");
			free(cmd_tab[i + 1]);
			cmd_tab[i + 1] = ft_strdup(filename);
			free(filename);
			filename = NULL;
		}
		i++;
	}
	return (0);
}