/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 18:34:04 by astutz            #+#    #+#             */
/*   Updated: 2022/11/21 16:15:49 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft/libft.h"
# include "stdarg.h"

# define SPECIFIERS "cspdiuxX%"

typedef struct s_printf
{
	va_list	args;
	size_t	width;
	size_t	precission;
	size_t	lenght;
	size_t	hash;
	size_t	zero;
	size_t	dash;
	size_t	space;
	size_t	plus;
	size_t	point;
	size_t	sign;
	size_t	ox;
}						t_printf;

int						ft_printf(const char *format, ...);
t_printf				*ft_init_tab(t_printf *tab);
t_printf				*ft_reset_tab(t_printf *tab);

void					s_conversor(t_printf *tab);
void					c_conversor(t_printf *tab, int choice);
void					id_conversor(t_printf *tab);
void					u_conversor(t_printf *tab);
void					p_conversor(t_printf *tab);
void					x_conversor(t_printf *tab, int choice);
void					width_highest_value_dash(t_printf *tab, char *number);
void					width_highest_value_notdash(t_printf *tab, \
						char *number, size_t len);
void					precission_highest_value(t_printf *tab, char *number);
void					len_highest_value(t_printf *tab, char *number);
void					filling_width(int amount, t_printf *tab);
void					printing_sign(t_printf *tab);
void					exception_negatives(t_printf *tab, int number);
void					print_space(t_printf *tab, long number);
int						ft_numlen_base(unsigned long n, int base);
void					px_width_highest_dash(t_printf *tab, char *number);
void					px_width_highest_notdash(t_printf *tab, char *number);

#endif