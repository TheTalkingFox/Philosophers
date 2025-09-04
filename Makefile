NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror 

SRC = philo.c check.c utils.c ft_utils.c logic.c init.c

OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ 

all: $(NAME)
 
$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re