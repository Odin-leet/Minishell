#ifndef MINISHELL_H
#define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_nameargs{
    char *string;
    struct nameargs *next
}       t_nameargs;

typedef struct command{
    struct s_nameargs *nameargs;
    struct file *files;
    struct command *next;
}           t_command;
 
 typedef struct s_file{
     char *file;
     int    type;
     struct file *next;
 }          t_file;

 
