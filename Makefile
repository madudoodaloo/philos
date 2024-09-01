NAME = philo

CC = cc 
RM = rm -rf 
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

SRC = $(wildcard *.c)
OBJS = $(SRC:.c=.o)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
