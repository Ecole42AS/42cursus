/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 13:17:46 by astutz            #+#    #+#             */
/*   Updated: 2022/12/26 14:25:42 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

// size_t	ft_strspn(const char *s, const char *accept)
// {
// 	size_t i;
// 	size_t j;

// 	if (!s || !accept)
// 		return (0);
// 	i = 0;
// 	while (s[i])
// 	{
// 		j = 0;
// 		while (accept[j])
// 		{
// 			if(accept[j++] == s[i])
// 				j++;
// 		}
// 		i++;
// 	}
// 	return (i - j);
// }

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == c)
			return ((char *)s);
		++s;
	}
	return (0);
}

size_t	ft_strspn(const char *s, const char *accept)
{
	size_t i = 0;

	while (s[i] != '\0')
	{
		if (ft_strchr(accept, s[i]) == 0)
			break;
		i++;
	}
	return (i);
}

int main()
{
	char s[] = "hellpo";
	char accept[] = "oehl";
	size_t num;
	size_t num1;
	
	num = ft_strspn(s, accept);
	num1 = strspn(s, accept);
	printf("%ld\n", num);
	printf("%ld", num1);
}