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
# include <fcntl.h>
#include <sys/_types.h>
#include <dirent.h>

int g_count ;

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
	int		pin;
	pid_t	*pid;
	char	**env1;
	char	**envprinc;
	int		cmd_size;
	char	**collected_cmd;
	char	**collected_files;
	int 	*collected_type;
	t_linked_list *newhead;
	t_linked_list *lcmd;
	t_linked_list *lfile;
}				t_vars;
int		get_next_line(int fd, char **line, int BUFFER_SIZE);
char 	**collector(t_linked_list *cmd);
int    unset(t_vars *pl);
char	*ft_strchr(char *s, int c);
char	*ft_strdup(char *s1, size_t i);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(char *s);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_calloc(size_t count, size_t size);
void	exec(t_linked_list *head, t_vars *v);
int builtins(char *string);
int ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split1(char const *s, char c);
int    export(t_vars *pl);
int ft_isdigit(int c);
int ft_isalpha2(int c);
size_t	ft_strlen(char *s);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char *s, unsigned int start, size_t len);
char *traitement1(char *str, int j);
char *traitement2(char *str);
char **transferenv(char **tmp);
int thereisequ(char *env);
int     counttab(char **tab);
void replaceenv(t_vars *pl, char *string);
char **addenv(t_vars *pl, char *string);
int     checkifthereisenv2(char **env, char *string);
int		env(t_vars *pl);
#endif
