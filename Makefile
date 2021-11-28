NAME =	Minishell

SRC =	parsing/parsing.c\
		parsing/exporthelper.c\
		parsing/exporthelper2.c\
		parsing/exporthelper3.c\
		parsing/exporthelper4.c\
		parsing/handelenvtab.c\
		parsing/handlargshelper.c\
		parsing/handleenviren2.c\
		parsing/signalsndmainsplit.c\
		parsing/unsethelper.c\
		parsing/utils_parsing.c\
		parsing/ft_split1.c\
		parsing/export.c\
		parsing/unset.c\
		execution/exec.c\
		execution/cd.c\
		execution/cd_opt.c\
		execution/cd_tools.c\
		execution/exec_tools.c\
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
		parsing/handlearg.c\
		parsing/freefunctions.c\
		parsing/mainhelper1.c\
		parsing/mainhelper2.c\
		parsing/mainhelper3.c\
		parsing/ft_strtrim.c\
		parsing/mainhelper22.c\
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
