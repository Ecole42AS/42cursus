# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: astutz <astutz@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/20 18:46:37 by astutz            #+#    #+#              #
#    Updated: 2023/05/13 20:25:59 by astutz           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
NAME = libftprintf.a
LIBFT = ./libft/libft.a
HEADERDIR = ./includes

SRCS	= 	srcs/ft_printf.c  	\
			srcs/ft_putptr.c   	\
			srcs/ft_putunbr.c  	\
			srcs/ft_putxnbr.c  	\
			srcs/ft_putxxnbr.c 	\
			srcs/ft_print_c.c	\
			srcs/ft_print_di.c 	\
			srcs/ft_print_s.c	\
			srcs/ft_print_percent.c

OBJS = ${SRCS:.c=.o}

.c.o:	
	${CC} ${CFLAGS} -c -I ${HEADERDIR} $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			make -C libft
			cp ${LIBFT} .
			mv libft.a libftprintf.a
			ar rcs ${NAME} ${OBJS}

all:	${NAME}

clean: 
	rm -rf ${OBJS}

fclean:	clean
	rm -rf ${NAME}

re: fclean all

.PHONY: all fclean clean re