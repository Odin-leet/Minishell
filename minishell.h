/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashite <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 11:24:56 by ashite            #+#    #+#             */
/*   Updated: 2021/11/24 07:47:35 by aali-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <signal.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <dirent.h>
# include <sys/_types.h>
# include <sys/syslimits.h>
# include <readline/history.h>
# include <readline/readline.h>

int			g_count;

typedef struct s_split{
	int		k;
	char	**split;
	int		i;
	char	c;
}				t_split;

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

typedef struct s_parser {
	t_linked_list	*head;
	t_command		*command;
	int				i;
}				t_parser;
typedef struct s_global {
	int	status;
}				t_global;
t_global	g_gl;
typedef struct s_vars
{
	int				in;
	int				out;
	int				pin;
	pid_t			*pid;
	char			*home;
	char			*curr;
	char			*oldpwd;
	char			**env1;
	char			**envprinc;
	int				cmd_size;
	char			**collected_cmd;
	int				exit_status;
	int				status;
	char			**collected_files;
	int				*collected_type;
	t_linked_list	*newhead;
	t_linked_list	*lcmd;
	t_linked_list	*lfile;
}				t_vars;
int				get_next_line(int fd, char **line, int BUFFER_SIZE);
char			*replaceenv2(char *string, int start, int end, char **env);
void			get_env(t_vars *pl, char **env);
char			*handleenvir2(char *string, char *tmp, char *tmp2);
char			*handleenvir1(char *string, int i, int start, char **env);
char			*handleenvir(char *string, char **env);
t_linked_list	*parser(t_linked_list *lexer, char **env);
char			**collector(t_linked_list *cmd);
int				unset(t_vars *pl);
char			*ft_strchr(char *s, int c);
char			*ft_strdup(char *s1, size_t i);
char			*ft_strjoin(char *s1, char *s2);
size_t			ft_strlen(char *s);
char			*ft_substr(char *s, unsigned int start, size_t len);
char			*ft_calloc(size_t count, size_t size);
void			exec(t_linked_list *head, t_vars *v);
int				builtins(char *string);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			**ft_split1(char const *s, char c);
char			**ft_split(char *s, char c);
int				splithelper(t_split split1, const char *s, char c);
int				*traitmask(const char *s, int c);
int				export(t_vars *pl);
int				ft_isdigit(int c);
int				ft_isalpha2(int c);
int				ft_isalpha(int c);
char			*ft_strjoin(char *s1, char *s2);
char			*ft_substr(char *s, unsigned int start, size_t len);
char			*traitement1(char *str, int j);
char			*traitement2(char *str);
char			**transferenv(char **tmp);
int				thereisequ(char *env);
int				counttab(char **tab);
void			replaceenv(t_vars *pl, char *string);
char			**addenv(t_vars *pl, char *string);
int				checkifthereisenv2(char **env, char *string);
int				thereisequ(char *env);
t_linked_list	*mainhelper3(char **split);
void			free_lin_command(t_linked_list *command);
void			free_files_linked(t_linked_list *files);
void			free_head(t_linked_list *head);
char			*ft_itoa(int n);
void			free_head2(t_linked_list *head);
int				mainhelper(char *string, int j, t_linked_list **head);
int				mainhelper2(int j, int i, t_linked_list **head, char *string);
int				check_errors(t_linked_list *ptr);
void			storeinfos(char *string, t_linked_list **head);
int				check_errors2(int j, int i, char *string);
int				checkforpipe(char *s);
void			free_files_linked2(t_linked_list *files);
char			*handleargs(char *string, char **env);
char			*elsefunction(char *string, char **env);
int				thereisslach(char *string);
char			*checkforpath(char *string, char *str);
int				builtins(char *string);
int				findtype(char *s);
void			*free_pre(char **split, int k);
void			append(t_linked_list **head_ref, void *data);
int				env(t_vars *pl);
char			*ft_strtrim(char *s1, char const *set);
#endif
