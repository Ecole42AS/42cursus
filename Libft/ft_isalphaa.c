/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalphaa.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:56:14 by astutz            #+#    #+#             */
/*   Updated: 2022/11/16 20:45:51 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n == 0)
		write (fd, "0", 1);
	if (n < 0)
		n = -n;
	if (n > 0)
	{
		n = (n % 10) + 48;
		write (fd, &n, 1);
		n /= 10;
	}
}


typedef struct s_list
{
void *content;
struct s_list *next;
} t_list;