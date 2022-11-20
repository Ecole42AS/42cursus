# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: astutz <astutz@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/20 18:46:37 by astutz            #+#    #+#              #
#    Updated: 2022/11/20 19:05:13 by astutz           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

LIBFT = libft/libft.a

SRCS =	#ft_printf.c 				\
		srcs/ft_print_base_itoa.c	\
		srcs/ft_print_ptr.c			\
		srcs/ft_printf_char.c 		\
		srcs/ft_printf_hex.c		\
		srcs/ft_printf_int.c		\
		srcs/ft_printf_string.c		\
		srcs/ft_printf_unsigned.c	\
		srcs/ft_printf_utils.c		\
		srcs/ft_loadflags.c

OBJS = $(SRCS:.c=.o)

CC = gcc

FLAGS = -Wall -Werror -Wextra -g

all: $(NAME)

$(NAME): $(OBJS)
		$(MAKE) bonus -C ./libft
		cp libft/libft.a $(NAME)
		$(CC) $(FLAGS) -c $(SRCS) -I ./ 
		ar rc $(NAME) $(OBJS)

clean:
		rm -f *.o
		/bin/rm -f $(OBJS)
		$(MAKE) clean -C ./libft

fclean: clean
		$(MAKE) fclean -C ./libft
		/bin/rm -f $(NAME)

re: fclean all