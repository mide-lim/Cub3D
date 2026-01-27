# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                                              #
# **************************************************************************** #

NAME	:= cub3D
CC		:= cc
CFLAGS	:= -Wall -Wextra -Werror -g

OBJDIR	:= obj
HEADER	:= includes/cub3D.h

# Libft (opcional)
LIBFTDIR	:= includes/libft
LIBFT		:= $(LIBFTDIR)/libft.a

GNLDIR	:= includes/get_next_line
GNL		:= $(GNLDIR)/get_next_line.a

# MiniLibX (Linux)
MLXREPO = https://github.com/42paris/minilibx-linux.git
MLXDIR	:= includes/minilibx-linux
MLX		:= $(MLXDIR)/libmlx.a
MLXINC	:= -I$(MLXDIR)
MLXFLAGS	:= -L$(MLXDIR) -lmlx -lX11 -lXext -lm

SRC	:= \
	src/main.c \
	src/parser/read_file.c

OBJ	:= $(SRC:%.c=$(OBJDIR)/%.o)

all: library $(NAME)

$(MLX):
	@if [ ! -f "$(MLX)" ]; then \
		echo "📦 minilibx ausente ou incompleta, instalando..."; \
		rm -rf $(MLXDIR); \
		git clone $(MLXREPO) $(MLXDIR); \
		$(MAKE) -C $(MLXDIR); \
	fi

library: $(MLX)
	$(MAKE) -C $(LIBFTDIR)
	$(MAKE) -C $(GNLDIR)


$(NAME): $(OBJ) $(HEADER) $(GNL) $(LIBFT)  $(MLX) 
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(GNL) $(LIBFT)  $(MLXFLAGS) 

$(OBJDIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(MLXINC) -Iincludes -c $< -o $@

clean:
	$(MAKE) clean -C $(LIBFTDIR)
	$(MAKE) clean -C $(GNLDIR)
	$(MAKE) clean -C $(MLXDIR)
	rm -rf $(OBJDIR)

fclean: clean
	$(MAKE) fclean -C $(LIBFTDIR)
	$(MAKE) fclean -C $(GNLDIR)
	rm -f $(NAME)

re: fclean all
bonus: all

.PHONY: all clean fclean re bonus library
