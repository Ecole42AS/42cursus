/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 14:11:54 by astutz            #+#    #+#             */
/*   Updated: 2022/10/29 18:23:32 by astutz           ###   ########.fr       */
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

void	*ft_memset(void *str, int c, size_t n)
{
	size_t		i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)str)[i] = c;
		i++;
	}
	return (str);
}

// int main()
// {
// 	int arr1[] = { 3, 4 }; // 0003 0004
// 	int arr2[] = { 1, 2 };
// 	ft_memset(arr1, 256, 2 * sizeof(int));
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


