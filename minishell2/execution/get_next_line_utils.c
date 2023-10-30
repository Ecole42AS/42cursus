/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sepi <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 13:51:59 by mde-sepi          #+#    #+#             */
/*   Updated: 2022/11/02 14:55:11 by mde-sepi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

void	f_memset(char *str, int c, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		*(str + i) = c;
		i++;
	}
}

void	*ft_calloc(size_t el, size_t size)
{
	void	*res;

	res = malloc(el * size);
	if (res == NULL)
		return (NULL);
	f_memset(res, '\0', (int)(el * size));
	return (res);
}
