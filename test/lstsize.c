/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstsize.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 08:27:06 by astutz            #+#    #+#             */
/*   Updated: 2022/12/31 08:36:56 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lstsize.h"

int	ft_list_size(t_list *begin_list)
{
	int count;
	
	count = 0;
	while(begin_list)
	{
		count++;
		begin_list = begin_list -> next;
	}
	return (count);
}