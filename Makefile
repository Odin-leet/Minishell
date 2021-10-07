NAME =	Minishell

SRC =	get_next.c\
		philo3.c\
		philo4.c\
		ft_atoi.c
		


OBJS = ${SRC:.c=.o}



 CC = gcc

all : $(NAME)

$(NAME) : ${OBJS}
		
		$(CC)  -Wall -Wextra -Werror  $(SRC) -o  $(NAME) 

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re:	fclean all
