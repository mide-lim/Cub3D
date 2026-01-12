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

# MiniLibX (Linux)
MLXDIR	:= includes/minilibx-linux
MLX		:= $(MLXDIR)/libmlx.a
MLXINC	:= -I$(MLXDIR)
MLXFLAGS	:= -L$(MLXDIR) -lmlx -lX11 -lXext -lm

SRC	:= \
	src/main.c \
	src/parser/read_file.c

OBJ	:= $(SRC:%.c=$(OBJDIR)/%.o)

all: library $(NAME)

library:
	$(MAKE) -C $(LIBFTDIR)
	$(MAKE) -C $(MLXDIR)

$(NAME): $(OBJ) $(HEADER) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBFT) $(MLXFLAGS)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(MLXINC) -Iincludes -c $< -o $@

clean:
	$(MAKE) clean -C $(LIBFTDIR)
	$(MAKE) clean -C $(MLXDIR)
	rm -rf $(OBJDIR)

fclean: clean
	$(MAKE) fclean -C $(LIBFTDIR)
	rm -f $(NAME)

re: fclean all
bonus: all

.PHONY: all clean fclean re bonus library
