NAME = philo

INC 	= includes/philo.h

SRC		=	src/philo.c\
			src/free_destroy.c\
			src/init.c\
			src/actions.c\
			src/time_libc.c\
			src/process.c\

CC 		= gcc

FLAGS	= -Wall -Wextra -Werror -pthread

OBJS 	= $(SRC:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(SRC) -o $(NAME)

all: $(NAME) $(OBJS) $(INC)

%.o: %.c $(INC)
		$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
