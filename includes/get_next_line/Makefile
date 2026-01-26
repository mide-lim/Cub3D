NAME := get_next_line
CC := gcc
CFLAGS := -Wall -Wextra -Werror
SRCS := get_next_line.c get_next_line_utils.c
OBJS := $(SRCS:.c=.o)
HDR := get_next_line.h



all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c $(HDR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re