# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mide-lim <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/14 20:42:34 by mide-lim          #+#    #+#              #
#    Updated: 2024/10/15 17:57:03 by mide-lim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs

SOURCES = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isascii.c
SOURCES += ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c
SOURCES += ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c
SOURCES += ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c
SOURCES += ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c
SOURCES += ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c
SOURCES += ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c
SOURCES += ft_putendl_fd.c ft_putnbr_fd.c
OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(AR) $(NAME) $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJECTS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
