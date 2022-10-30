/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 14:11:54 by astutz            #+#    #+#             */
/*   Updated: 2022/10/30 12:48:17 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"

// void *memset(void *str, int c, size_t len)
// {
// 	unsigned char *ptr;

// 	ptr = str;
// 	while (len > 0)
// 	{
// 		*ptr = c;
// 		ptr++;
// 		len--;
// 	}
// }

// void	*ft_memset(void *str, int c, size_t n)
// {
// 	size_t		idx;

// 	idx = 0;
// 	while (idx < n)
// 	{
// 		*((unsigned char *)str + idx) = c;
// 		idx++;
// 	}
// 	return (str);
// }

void	*ft_memset(void *b, int c, size_t len)
{
	size_t		i;

	i = 0;
	while (i < len)
	{
		((unsigned char *)b)[i] = c;
		i++;
	}
	return (b);
}

// int main()
// {
// 	int arr1[] = { 49, 50 }; // 0003 0004 49 50
// 	//int arr2[] = { 1, 2 };
// 	ft_memset(arr1, 50, 0);
// 	printf("%08x   %08x\n", arr1[0], arr1[1]);
// 	printf("%d   %d\n", arr1[0], arr1[1]);
// 	return (0);
// }

// int main()
// {
// 	char str[] = "he";
// 	ft_memset(str + 1, 'g', sizeof(char));
// 	printf("%s", str);
// 	return (0);
// }
