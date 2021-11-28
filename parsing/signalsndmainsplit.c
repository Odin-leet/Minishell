/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signalsndmainsplit.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aali-mou <aali-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 02:34:32 by aali-mou          #+#    #+#             */
/*   Updated: 2021/11/28 02:38:52 by aali-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_env(t_vars *pl, char **env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[i] != NULL)
		i++;
	pl->envprinc = malloc(sizeof (char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		j = 0;
		j = ft_strlen(env[i]);
		pl->envprinc[i] = malloc(sizeof(char) * (j + 1));
		i++;
	}
	get_env1(env, pl);
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

void	handlesig1(void)
{
	if (g_gl.isin == 1)
	{
		write(1, "\n", 1);
		g_gl.isin = 0;
	}
	else
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_gl.status = 1;
	}
}

void	handlesig2(void)
{
	if (g_gl.isin)
		write(2, "Quit: 3\n", 8);
	else
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handlesig(int sig)
{
	if (g_gl.herdo == 0)
	{
		if (sig == SIGINT)
		{
			handlesig1();
		}
		if (sig == SIGQUIT)
		{
			handlesig1();
		}
	}
}
