NAME =	Minishell

SRC =	parsing.c\
		ft_split1.c\
		export.c\
		unset.c\
		execution/exec.c\
		libftfunc.c\
		libftfunc1.c\
		parser.c\
		mainsplit.c\
		handleenvir.c\
		handelenvtab.c\
		handlearg.c\
		freefunctions.c\
		mainhelper1.c\
		mainhelper2.c\
		mainhelper3.c


		


OBJS = ${SRC:.c=.o}



 CC = gcc

all : $(NAME)

$(NAME) : ${OBJS}
		
		$(CC)  -Wall -Wextra -Werror  -g $(SRC) -o  $(NAME)  -lreadline


clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re:	fclean all
