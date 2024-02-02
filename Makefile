NAME = philosophers

SRCS = main.c philosophers.c utils.c threads.c parcing.c free.c print.c\


OBJS = $(SRCS:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -pthread -g3

all: $(NAME)

$(NAME): $(OBJS)
# @make -C ./libft			libft/libft.a
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)
#	rm -rf ./libft/*.o

fclean: clean
	rm -f $(NAME)
#	rm -rf libft/libft.a
	
re: fclean all