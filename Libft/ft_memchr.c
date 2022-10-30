/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 12:52:22 by astutz            #+#    #+#             */
/*   Updated: 2022/10/30 14:40:47 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"

void	*ft_memchr(const void *s, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if (((unsigned char *)s)[i] == ((unsigned char)c))
			return ((void *)(s + i));
		i++;
	}
	return (NULL);
}

// void	*ft_memchr(const void *s, int c, size_t n)
// {
// 	size_t		i;

// 	idx = 0;
// 	while (idx < n)
// 	{
// 		if (*((unsigned char *)s + idx) == (unsigned char)c)
// 			return ((void *)s + idx);
// 		idx++;
// 	}
// 	return (NULL);
// }

// int main()
// {
// 	char s[] = "hello world";

// 	printf("%s", ft_memchr(s, 'l', sizeof(s)));
// }