SRCS	=	main.c \
			init.c \
			start_routines.c \
			philo_routines.c \
			utils.c \
			arg_utils.c \
			end.c

OBJS	= $(SRCS:.c=.o)

CC		= cc

CFLAGS	= -g -Wall -Wextra -Werror -pthread -fsanitize=thread

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