/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashite <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 11:24:56 by ashite            #+#    #+#             */
/*   Updated: 2021/11/05 11:25:00 by ashite           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
#include <sys/_types.h>


typedef struct s_file{
	char	*file;
	int		type;
}				t_file;

typedef struct s_ll{
	void		*data;
	struct s_ll	*next;
}				t_linked_list;

typedef struct command{
	t_linked_list	*nameargs;
	t_linked_list	*files;
}				t_command;

typedef struct s_vars
{
	int		in;
	int		out;
	int		pvin;
	pid_t	pid;
	char	**collected;
	t_linked_list *newhead;
	t_linked_list *lcmd;
	t_linked_list *lfile;
}				t_vars;
int		get_next_line(int fd, char **line, int BUFFER_SIZE);
char **collector(t_linked_list *cmd);
char	*ft_strchr(char *s, int c);
char	*ft_strdup(char *s1, size_t i);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(char *s);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_calloc(size_t count, size_t size);
int		exec(t_linked_list *head);
char		**ft_split1(char const *s, char c);
#endif
