/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 18:05:21 by astutz            #+#    #+#             */
/*   Updated: 2022/12/03 20:56:54 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(char *s)
{
	size_t	i;
	char	*str;

	str = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i])
		str[i++] = s[i];
	str[i] = 0;
	return (str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	str = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
		str[i++] = s1[i];
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = 0;
	return (str);
}

char	*ft_substr(char *s, unsigned int start, size_t n)
{
	char	*str;
	size_t	i;

	if (ft_strlen(s) <= start)
		n = 0;
	if (ft_strlen(s) - start < n)
		n = ft_strlen(s) - start;
	str = (char *)malloc((n + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (n > 0)
		{
			str[i++] = s[start++];
			n--;
		}
	str[i] = 0;
	return (str);
}
