/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 13:48:09 by astutz            #+#    #+#             */
/*   Updated: 2022/11/01 14:12:53 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"

size_t ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t i;
	size_t lenSrc;

	lenSrc = ft_strlen(src);
	i = ft_strlen(dest);
	while (src[i] && i < size - 1)
	{
		dest[i] += src[i];
		i++;
	}
	return (size);
}

int main()
{
	char src[] = "hello";
	char dest[] = "you";

	ft_strlcat(dest, src, ft_strlen(dest));
	printf("%s", dest);
}