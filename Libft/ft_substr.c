/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 09:30:21 by astutz            #+#    #+#             */
/*   Updated: 2022/11/06 10:18:21 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*newchain;
	size_t	i;

	if (!s)
		return (NULL);
	if (len <= 0 || (start + 1 > ft_strlen(s)))
	{
		newchain = (char *)malloc(1);
		*newchain = 0;
		return (newchain);
	}
	newchain = (char *)malloc (sizeof(char) * (len + 1));
	if (!newchain)
		return (NULL);
	i = 0;
	if (start < ft_strlen(s))
	{
		while (s[start] != '\0' && i < len)
			newchain[i++] = s[start++];
	}
	newchain[i] = '\0';
	return (newchain);
}

// #include "libft.h"

// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	char	*src;
// 	int		i;

// 	i = 0;
// 	if ((!s))
// 		return (NULL);
// 	if (start > ft_strlen((char *)s))
// 	{
// 		src = (char *)malloc(sizeof(char));
// 		src[0] = '\0';
// 		return (src);
// 	}
// 	src = (char *)malloc((len + 1) * sizeof(char));
// 	while (s[start] && len--)
// 	{
// 		src[i] = (char)s[start];
// 		start++;
// 		i++;
// 	}
// 	src[i] = '\0';
// 	return (src);
// }