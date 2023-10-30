/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 14:44:26 by astutz            #+#    #+#             */
/*   Updated: 2023/09/29 14:50:36 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		s++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{	
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	i;
	char	*str;

	ptr = malloc(size * nmemb);
	if (!ptr)
		return (NULL);
	if (ptr != NULL)
	{
		str = (char *)ptr;
		i = -1;
		while (++i < size * nmemb)
			str[i] = 0;
	}
	return (str);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (!dst && !src)
		return (0);
	i = 0;
	while (i < n)
	{
		((unsigned char *)dst)[i] = ((const unsigned char *)src)[i];
		i++;
	}
	return (dst);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = 0;
	while (s1[s1_len])
		s1_len++;
	s2_len = 0;
	while (s2[s2_len])
		s2_len++;
	s = malloc(sizeof(*s) * (s1_len + s2_len + 1));
	if (s != NULL)
	{
		ft_memcpy(s, s1, s1_len);
		ft_memcpy(s + s1_len, s2, s2_len);
		s[s1_len + s2_len] = '\0';
	}
	return (s);
}
