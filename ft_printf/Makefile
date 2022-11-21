# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: astutz <astutz@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/20 18:46:37 by astutz            #+#    #+#              #
#    Updated: 2022/11/21 16:13:46 by astutz           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

LIBFT = libft/libft.a

SRCS = auxiliar_functions.c \
			c_conversor.c \
			ft_printf.c \
			id_conversor.c \
			p_conversor.c \
			s_conversor.c \
			u_conversor.c \
			x_conversor.c 

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

.PHONY: fclean re all clean