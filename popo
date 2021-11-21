NAME =	Minishell

SRC =	parsing.c\
		ft_split1.c\
		exec.c

		


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
