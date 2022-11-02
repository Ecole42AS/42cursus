/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 19:55:31 by astutz            #+#    #+#             */
/*   Updated: 2022/11/02 20:40:04 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;

	i = ft_strlen(s);
	if ((char)c == '\0')
		return ((char *)s + i);
	while (i > 0)
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i--;
	}
	return ((char *) NULL);
}

// char	*ft_strrchr(const char *s, int c)
// {
// 	int	len;

// 	len = ft_strlen((char *)s) + 1;
// 	while (len--)
// 	{
// 		if (s[len] == (char)c)
// 			return ((char *)&s[len]);
// 	}
// 	return (NULL);
// }

// char	*ft_strrchr(const char *str, int c)
// {
// 	int		idx;

// 	idx = ft_strlen((char *)str) + 1;
// 	while (idx--)
// 	{
// 		if (*(str + idx) == c)
// 			return ((char *)(str + idx));
// 	}
// 	return (0);
// }