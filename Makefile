NAME = philo

CC = cc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror -g

SRC = ./srcs/eat.c \
	./srcs/init.c \
	./srcs/parser.c \
	./srcs/time.c \
	./srcs/philo.c\
	./srcs/threads.c\
	./srcs/utils.c

OBJS_DIR = objs
OBJS = $(patsubst %.c,$(OBJS_DIR)/%.o,$(SRC))

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	@$(RM) $(OBJS_DIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re