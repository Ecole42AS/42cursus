/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 13:03:47 by astutz            #+#    #+#             */
/*   Updated: 2022/11/05 09:29:22 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t		position;

	if (*to_find == '\0')
		return ((char *)str);
	position = ft_strlen((char *)to_find);
	while (*str != '\0' && len-- >= position)
	{
		if (*str == *to_find && ft_memcmp(str, to_find, position) == 0)
			return ((char *)str);
		str++;
	}
	return (NULL);
}

// int main()
// {
// 	char s[] = "hello world zoo";
// 	char s1[] = "world";
// 	char *res;
// 	res = ft_strnstr(s, s1, 2);
// 	printf("%s", res);
// }

//len = len de haystack

// ###### Python tutor try ######

// #include "string.h"

// char    *ft_strnstr(const char *str, const char *to_find, size_t len)
// {
//     size_t        position;

//     if (*to_find == '\0')
//         return ((char *)str);
//     position = strlen((char *)to_find);
//     while (*str != '\0' && len-- >= position)
//     {
//         if (*str == *to_find && memcmp(str, to_find, position) == 0)
//             return ((char *)str);
//         str++;
//     }
//     return (NULL);
// }

// int main()
// {
//     char s[] = "hello world zoo";
//     char s1[] = "world";
//     char *res;
//     res = ft_strnstr(s, s1, 5);
//     printf("%s", res);
// }
