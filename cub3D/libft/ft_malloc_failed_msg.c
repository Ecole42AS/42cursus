/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_failed_msg.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 10:05:08 by astutz            #+#    #+#             */
/*   Updated: 2023/10/31 10:08:10 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_malloc_failed_msg(int size, size_t type)
{
	void	*ptr;

	ptr = ft_calloc(size + 1, type);
	if (!ptr)
	{
		perror("Memory allocation failure");
		exit(1);
	}
	return (ptr);
}
