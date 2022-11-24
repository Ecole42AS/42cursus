# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: astutz <astutz@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/20 18:46:37 by astutz            #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2022/11/24 18:48:17 by astutz           ###   ########.fr        #
=======
#    Updated: 2022/11/24 15:01:43 by astutz           ###   ########.fr        #
>>>>>>> bd7d3a046563a0a209a703d9b7f8ef7c631e28af
#                                                                              #
# **************************************************************************** #

# NAME = libftprintf.a

# LIBFT = libft/libft.a

# SRCS =	srcs/ft_printf.c
# #auxiliar_functions.c \
# 			c_conversor.c \
# 			ft_printf.c \
# 			id_conversor.c \
# 			p_conversor.c \
# 			s_conversor.c \
# 			u_conversor.c \
# 			x_conversor.c 

# #OBJS = $(SRCS:.c=.o)

# # %.o:%.c
# #     gcc $(CFLAGS) $< -o $@
# # %.o: %.c
# # 	$(CC) -I. $(FLAGS) -o $@ -c $?

# CC = gcc

# FLAGS = -Wall -Werror -Wextra -g

# all: $(NAME)

# $(NAME): $(OBJS)
# 		$(MAKE) bonus -C ./libft
# 		cp libft/libft.a $(NAME)
# 		$(CC) $(FLAGS) -c $(SRCS) -I ./ 
# 		ar rc $(NAME) $(OBJS)

# clean:
# 		rm -f *.o
# 		/bin/rm -f $(OBJS)
# 		$(MAKE) clean -C ./libft

# fclean: clean
# 		$(MAKE) fclean -C ./libft
# 		/bin/rm -f $(NAME)

# re: fclean all

# .PHONY: fclean re all clean

# NAME 	= libftprintf.a

# SRCS 	= 	srcs/ft_printf.c
			
# OBJS	= ${SRCS:.c=.o}


# CC		= gcc
# FLAGS 	= -Wall -Wextra -Werror -g

# RM		= rm -f

# ${NAME}:	$(OBJS)
# 			ar rcs $(NAME) $(OBJS)


# %.o: %.c
# 	$(CC) -I. $(FLAGS) -o $@ -c $?
	
# all: 		${NAME}

# clean:		
# 			${RM} ${OBJS}

# fclean:		clean
# 			${RM} ${NAME}

# re:			fclean all


# .PHONY:		all clean fclean re .c.o

NAME	= libftprintf.a

<<<<<<< HEAD
SRCS	= 	srcs/ft_printf.c \
			#parse.c \
			print.c \
			utils.c
=======
SRCS	= 	ft_printf.c
>>>>>>> bd7d3a046563a0a209a703d9b7f8ef7c631e28af

OBJS	= ${SRCS:%.c=%.o} #le pb est la il comprend pas le all .c representer par (%).

# %.o: %.c
# 	$(CC) -I. $(FLAGS) -o $@ -c $?
	
FLAGS	= -Wall -Wextra -Werror -g

$(NAME):
	gcc $(FLAGS) -c $(SRCS) -I ./
	ar rc $(NAME) $(OBJS)

all: $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re