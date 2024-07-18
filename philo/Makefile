NAME	=	philo
SRC		=	philo_utils.c philo_utils2.c main.c philo.c philo_utils3.c
OBJS 	= 	$(SRC:.c=.o)
CC 		= 	gcc
CFLAGS 	= 	-Wall -Wextra -Werror# -fsanitize=thread
RM	 	= 	rm -rf

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re