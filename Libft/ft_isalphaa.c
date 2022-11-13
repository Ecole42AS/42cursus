/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalphaa.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:56:14 by astutz            #+#    #+#             */
/*   Updated: 2022/11/13 10:57:20 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*newchain;
	size_t	i;

	i = 0;
	if (!len || !start)
		return (NULL);
	newchain = malloc(sizeof(char) * len);
	if (!newchain)
		return (NULL);
	while (s[start] && start < len)
	{
		newchain[i] = s[start];
		i++;
		start++;
	}
	return (newchain);
}
