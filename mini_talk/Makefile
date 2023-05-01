# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: astutz <astutz@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/18 20:10:06 by astutz            #+#    #+#              #
#    Updated: 2023/04/20 19:07:09 by astutz           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=		server.c client.c \

SRCSB	=		server_bonus.c client_bonus.c \

OBJS	=		$(SRCS:.c=.o)

OBJSB	=		$(SRCSB:.c=.o)

CC		=		gcc

CFLAGS	=		-Wall -Wextra -Werror -g

all: 			server client server_bonus client_bonus

server: 		server.o ft_printf/libftprintf.a
				$(CC) -o $@ $^

server_bonus:	server_bonus.o ft_printf/libftprintf.a
				$(CC) -o $@ $^

client:			client.o ft_printf/libftprintf.a
				$(CC) -o $@ $^

client_bonus:	client_bonus.o ft_printf/libftprintf.a
				$(CC) -o $@ $^

%.o: 			%.c
				$(CC) -c $(CFLAGS) $?

ft_printf/libftprintf.a:
				@make -C ft_printf

clean:
				rm -f $(OBJS) $(OBJSB)
				@make -C ft_printf clean

fclean:			clean
				rm -f server client ft_printf/libftprintf.a
				rm -f server_bonus client_bonus
				@make -C ft_printf fclean

re: 			fclean all

.PHONY:			all  clean fclean re