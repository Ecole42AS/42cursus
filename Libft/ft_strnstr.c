/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 13:03:47 by astutz            #+#    #+#             */
/*   Updated: 2022/11/03 13:46:31 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	i = 0;
	while (haystack && needle && i < len)
	{
		if (haystack)
	}
}

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

int main()
{
	char s[] = "hello world zoo";
	char s1[] = "world";
	char *res;
	
	res = ft_strnstr(s, s1, 2);
	printf("%s", res);
}

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

// permalink python tutor: https://pythontutor.com/render.html#code=%23include%20%22string.h%22%0A%0Achar%20%20%20%20*ft_strnstr%28const%20char%20*str,%20const%20char%20*to_find,%20size_t%20len%29%0A%7B%0A%20%20%20%20size_t%20%20%20%20%20%20%20%20position%3B%0A%0A%20%20%20%20if%20%28*to_find%20%3D%3D%20'%5C0'%29%0A%20%20%20%20%20%20%20%20return%20%28%28char%20*%29str%29%3B%0A%20%20%20%20position%20%3D%20strlen%28%28char%20*%29to_find%29%3B%0A%20%20%20%20while%20%28*str%20!%3D%20'%5C0'%20%26%26%20len--%20%3E%3D%20position%29%0A%20%20%20%20%7B%0A%20%20%20%20%20%20%20%20if%20%28*str%20%3D%3D%20*to_find%20%26%26%20memcmp%28str,%20to_find,%20position%29%20%3D%3D%200%29%0A%20%20%20%20%20%20%20%20%20%20%20%20return%20%28%28char%20*%29str%29%3B%0A%20%20%20%20%20%20%20%20str%2B%2B%3B%0A%20%20%20%20%7D%0A%20%20%20%20return%20%28NULL%29%3B%0A%7D%0A%0Aint%20main%28%29%0A%7B%0A%20%20%20%20char%20s%5B%5D%20%3D%20%22hello%20world%20zoo%22%3B%0A%20%20%20%20char%20s1%5B%5D%20%3D%20%22world%22%3B%0A%20%20%20%20char%20*res%3B%0A%20%20%20%20%0A%20%20%20%20res%20%3D%20ft_strnstr%28s,%20s1,%205%29%3B%0A%20%20%20%20printf%28%22%25s%22,%20res%29%3B%0A%7D&cumulative=false&curInstr=15&heapPrimitives=nevernest&mode=display&origin=opt-frontend.js&py=c_gcc9.3.0&rawInputLstJSON=%5B%5D&textReferences=false