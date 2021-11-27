NAME =	Minishell

SRC =	parsing/parsing.c\
		parsing/ft_split1.c\
		parsing/export.c\
		parsing/unset.c\
		execution/exec.c\
		execution/cd.c\
		execution/heredoc.c\
		execution/herdoc2.c\
		execution/executer.c\
		execution/exechelepr.c\
		execution/filemanager.c\
		execution/otherbuiltins.c\
		execution/builtins1.c\
		execution/collecter.c\
		parsing/libftfunc.c\
		parsing/libftfunc1.c\
		parsing/mainsplit.c\
		parsing/handleenvir.c\
		parsing/handelenvtab.c\
		parsing/handlearg.c\
		parsing/freefunctions.c\
		parsing/mainhelper1.c\
		parsing/mainhelper2.c\
		parsing/mainhelper3.c\
		parsing/ft_strtrim.c\
		parsing/parser.c\
		parsing/ft_itoa.c

OBJS = ${SRC:.c=.o}

 CC = gcc

all : $(NAME)

$(NAME) : ${OBJS}
		$(CC)  -Wall -Wextra -Werror  -g $(SRC) -o  $(NAME) -lreadline -L /Users/${USER}/.brew/opt/readline/lib -I /Users/${USER}/.brew/opt/readline/include

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re:	fclean all
