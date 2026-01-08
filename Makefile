NAME    := cub3D
CC      := cc
CFLAGS  := -Wall -Wextra -Werror -g

# MiniLibX
MLX_DIR := includes/minilibx-linux
MLX_INC := -I$(MLX_DIR)
MLX_LIB := -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

SRC     := src/main.c
OBJ     := main.o

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_LIB) -o $(NAME)

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) $(MLX_INC) -c $(SRC) -o $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus


