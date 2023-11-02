/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 09:50:55 by astutz            #+#    #+#             */
/*   Updated: 2023/11/02 11:07:39 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/* Strcmp is used to compare two strings. */
int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}

// int main() {
//     const char *str1 = "hello";
//     const char *str2 = "world";
//     const char *str3 = "hello";
    
//     int result1 = ft_strcmp(str1, str2);
//     int result2 = ft_strcmp(str1, str3);

// 	printf("result1: %d\n", result1);
// 	printf("result2: %d\n", result2);

//     if (result1 < 0) {
//         printf("'%s' is less than '%s'\n", str1, str2);
//     } else if (result1 > 0) {
//         printf("'%s' is greater than '%s'\n", str1, str2);
//     } else {
//         printf("'%s' is equal to '%s'\n", str1, str2);
//     }

//     if (result2 < 0) {
//         printf("'%s' is less than '%s'\n", str1, str3);
//     } else if (result2 > 0) {
//         printf("'%s' is greater than '%s'\n", str1, str3);
//     } else {
//         printf("'%s' is equal to '%s'\n", str1, str3);
//     }

//     return 0;
// }