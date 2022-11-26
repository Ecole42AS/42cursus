/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 18:34:04 by astutz            #+#    #+#             */
/*   Updated: 2022/11/26 18:34:30 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft/libft.h"
# include "stdarg.h"

int		ft_printf(const char *format, ...);
void	ft_putunbr_fd(unsigned int n, int fd);
void	ft_putptr_fd(void *ptr, int fd);
void	ft_putxnbr_fd(unsigned int n, int fd);
void	ft_putxxnbr_fd(unsigned int n, int fd);

#endif