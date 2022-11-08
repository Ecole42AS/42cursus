/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 09:30:21 by astutz            #+#    #+#             */
/*   Updated: 2022/11/08 14:04:23 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Returns the substring of the given string at the given start position with 
 * the given length (or smaller if the length of the original string is less 
 * than start + length, or length is bigger than MAXSTRINGLEN).*/
#include "libft.h"

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
