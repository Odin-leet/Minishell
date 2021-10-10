#ifndef MINISHELL_H
# define MINISHELL_H

 
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

 typedef struct s_file{
     char *file;
     int    type;
 }          t_file;

typedef struct s_ll {
    t_file   *data;
    struct  s_ll *next;
}               t_linked_list;

typedef struct command {
    t_linked_list *nameargs;
    t_linked_list *files;
}           t_command;





t_file fil;
int		get_next_line(int fd, char **line, int BUFFER_SIZE);
char	*ft_strchr(char *s, int c);
char	*ft_strdup(char *s1, size_t i);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(char *s);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_calloc(size_t count, size_t size);
#endif