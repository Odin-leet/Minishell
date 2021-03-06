/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashite <ashite@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 11:24:56 by ashite            #+#    #+#             */
/*   Updated: 2021/11/28 20:31:43 by ashite           ###   ########.fr       */
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
	int	isin;
	int	herdo;
	int	failed;
	int	special;
	int	herdoc;
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
	char			*root;
	char			**env1;
	char			**envprinc;
	int				cmd_size;
	char			**collected_cmd;
	char			**collected_cmd2;
	int				exit_status;
	int				status;
	char			**collected_files;
	int				*collected_type;
	char			**split;
	t_linked_list	*newhead;
	t_linked_list	*lcmd;
	t_linked_list	*herdoc;
	t_linked_list	*lfile;
}				t_vars;

int				get_next_line(int fd, char **line, int BUFFER_SIZE);
void			else1(t_file *token, char **env, t_command **command);
char			*elsefunctionhelper(char *s, char **ta, int i, char *tm);
char			*elsefunctionhelper2(char *t, char *s, char **e, int i);
int				count_word(char *s, char c);
char			*checkingforendofaenv(char *s, char *t, int *i, int *end);
void			else2(t_file *t, t_command **c, t_linked_list **l, char **e);
void			get_env1(char **env, t_vars *pl);
int				findenvi(char **env);
void			handlesig1(void);
char			*handleargs(char *string, char **env);
void			handlesig1(void);
void			handlesig(int sig);
int				checkspace(char *buffer);
char			**unsettaballoc(char **env, char **tmp, int count);
char			*replaceenv2(char *string, int start, int end, char **env);
char			**remplirtmp(char **tmp1, char **env, char *string, int c);
void			get_env(t_vars *pl, char **env);
int				unsetenv1returncount(char **env, char *tmp, int count, int i);
char			*handleenvir2(char *string, char *tmp, char *tmp2);
char			*handleenvir1(char *string, int i, int start, char **env);
char			**remplirtableunset(char **env, char **tmp, int count, int i);
void			unsetenv1(t_vars *pl, char *string);
char			*handleenvir(char *string, char **env);
t_linked_list	*parser(t_linked_list *lexer, char **env);
char			**collector(t_linked_list *cmd);
int				returnquotescount(char *string);
int				returnthereisenv(int count, int count2, char **env, char *tmp);
int				unset(t_vars *pl);
int				helpercount(char **env, int count2, int j, int i);
int				returncount(char *string, char *tmp, int i, int j);
char			*ft_strchr(char *s, int c);
char			*ft_strdup(char *s1, size_t i);
char			*ft_strjoin(char *s1, char *s2);
size_t			ft_strlen(char *s);
char			*ft_substr(char *s, unsigned int start, size_t len);
char			*ft_calloc(size_t count, size_t size);
void			exec(t_linked_list *head, t_vars *v);
void			free_head3(t_linked_list *head);
int				builtins(char *string);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			**ft_split1(char const *s, char c);
char			**ft_split(char *s, char c);
int				splithelper(t_split split1, const char *s, char c);
int				*traitmask(const char *s, int c);
void			replaceeenv2(t_vars *pl, char *tmp, int i, int c);
int				export(t_vars *pl);
int				ft_isdigit(int c);
int				exporthelper(t_vars *pl);
int				ft_isalpha2(int c);
int				ft_isalpha(int c);
char			*ft_strjoin(char *s1, char *s2);
char			*ft_substr(char *s, unsigned int start, size_t len);
char			*traitement1(char *str, int j);
char			*traitement2(char *str);
char			**transferenv(char **tmp);
void			freesomething(char *tmp, t_vars *pl);
int				thereisequ(char *env);
void			replaceeenv1(t_vars *pl, char *string1, int i, int c);
void			addenvfinal(char **tmp1, char **tmp3, t_vars *pl, char *tmp);
void			addenvhelperif( char **tmp3, char **tmp1, char *s, t_vars *pl);
void			addenvhelperelse( char **tmp3, char **t, char *s, t_vars *pl);
int				counttab(char **tab);
void			replaceenv(t_vars *pl, char *string);
char			**addenv(t_vars *pl, char *string);
int				errorexport2(void);
int				errorexport(char *string);
int				checkifthereisenv2(char **env, char *string);
void			replaceenv(t_vars *pl, char *string);
int				checkifthereisenv(char **env, char *string);
char			**addenv2(char *string, t_vars *pl);
int				thereisequ(char *env);
t_linked_list	*mainhelper3(char **split);
void			free_lin_command(t_linked_list *command);
int				checkifitscomp1(char *string);
void			free_files_linked(t_linked_list *files);
int				checkifthereisquotes(char *string);
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
int				checkifitscomp(char **string);
void			*free_pre(char **split, int k);
void			append(t_linked_list **head_ref, void *data);
int				env(t_vars *pl);
char			*ft_strtrim(char *s1, char const *set);
int				cd(t_vars *v);
char			*exportenv(t_vars *pl, char *string);
int				heredocs_finder(t_vars *v);
int				*type_collector(t_linked_list *lfile);
char			**files_collector(t_linked_list *lfile);
char			**cmd_collector(t_linked_list *cmd);
int				quotescount(int *i, int count, char *string, char c);
int				checkforquotes2(char *string);
void			checkforquotes(char **string);
char			*sgl_quotesreplace(char *tmp, char *string, int *c, int *i);
char			*db_quotesreplace(char *tmp, char *string, int *c, int *i);
char			*changecollectedcmd(char *string, int count);
int				ft_atoi(const char *str);
char			*exportenv(t_vars *pl, char *string);
void			piper(t_vars *v, int i);
void			executer(t_linked_list *head, t_vars *v, int i);
void			parent(t_vars *v);
void			forker(t_vars *v, int i);
void			children(t_vars *v);
int				builtve(t_vars *v);
int				ft_exit(t_vars *v);
int				pwd(void);
int				echo(t_vars *v);
void			echo_logie(t_vars *v, int i, int n);
void			file_manager(t_vars **v);
int				is_not_digit(char *s);
int				exec_initializer(t_vars *v, t_linked_list *head);
void			fail(char *s, int act);
int				exit_status(pid_t pid, int fd);
int				get_status(int status);
void			close_and_exit(int fd);
int				ft_strcmp(const char *s1, const char *s2);
void			ctrl_handler(int sig);
void			pid_manager(t_vars *v);
void			execinitialisation(t_vars **v);
int				cdtier(t_vars *v);
int				cd_moja(t_vars *v);
int				change_dir(t_vars *v, char *dir);
int				cdhome(t_vars *v);
int				cdback(t_vars *v);
int				cd_cleanup(t_vars *v, int ret);
int				builtinns(char *string);

#endif
