/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 18:34:04 by astutz            #+#    #+#             */
/*   Updated: 2022/11/27 09:23:15 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft/libft.h"
# include "stdarg.h"

int		ft_printf(const char *format, ...);
int		ft_putunbr(unsigned int nb);
int		ft_putptr(unsigned long nb);
int		ft_putxnbr(unsigned int nb);
int		ft_putxxnbr(unsigned int nb);
int		ft_print_percent(void);
int		ft_print_c(int c);
int		ft_print_di(int n);
int		ft_print_s(char *str);

#endif