CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = main.c util.c

NAME = philo
all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) -o $(NAME) $(SRC)

clean:
	rm -f *.o

fclean:
	rm -f $(NAME)

re: 
	fclean all

party:
	curl parrot.live

.PHONY: all clean fclean re party