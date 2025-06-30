SRCS	=	philo_routines.c \
			philo.c \
			utils.c \
			init.c

OBJS	= $(SRCS:.c=.o)

CC		= cc

CFLAGS	= -Wall -Wextra -Werror -pthread

NAME	= philo

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	@echo "[DELETING...]"
	rm -rf $(OBJS)
	@echo "[DELETED]"

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all fclean clean re