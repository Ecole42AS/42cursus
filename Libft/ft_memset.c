/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 14:11:54 by astutz            #+#    #+#             */
/*   Updated: 2022/10/29 10:54:57 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"

void *memset(void *str, int c, size_t len)
{
	unsigned char *ptr;

	ptr = str;
	while (len > 0)
	{
		*ptr = c;
		ptr++;
		len--;
	}
}

int main()
{
	printf("%p", memset("h", 1, 2));
	return (0);
}
