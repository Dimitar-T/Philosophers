CC = cc
CFLAGS = -Wall -Wextra -Werror -g
SRC = main.c util.c init.c simulation.c philo_actions.c
OBJ = $(SRC:.c=.o)
NAME = philo
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean: 
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re party
