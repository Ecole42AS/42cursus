/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalphaa.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:56:14 by astutz            #+#    #+#             */
/*   Updated: 2022/11/14 17:49:32 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;

	size = ft_strlen(s1 + s2 + 1);
	ptr = malloc(size * sizeof(char));
	if (!ptr)
		return (NULL);
	ft_strlcat(s1, s2, size);
	ft_strlcpy(ptr, s1, size);
	return (ptr);
}