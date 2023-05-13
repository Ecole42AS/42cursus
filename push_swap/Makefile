# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: astutz <astutz@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/13 10:07:53 by astutz            #+#    #+#              #
#    Updated: 2023/05/13 12:24:41 by astutz           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

NAME = push_swap

all: ${NAME}

push_swap: *.o ft_printf/libftprintf.a
	$(CC) -o $@ $^

%.o: %.c
	$(CC) -c $(CFLAGS) $?

ft_printf/libftprintf.a:
	@make -C ft_printf

clean:
	rm -f $(OBJECTS)
	@make -C ft_printf clean

fclean: clean
	rm -f push_swap ft_printf/libftprintf.a

re: fclean all

.PHONY: all bonus clean fclean re