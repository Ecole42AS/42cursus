/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 15:53:15 by astutz            #+#    #+#             */
/*   Updated: 2022/12/26 15:54:03 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list_size.h"

int	ft_list_size(t_list *begin_list)
{
	if (begin_list == 0)
		return (0);
	else
		return (1 + ft_list_size(begin_list->next));
}

// int	ft_list_size(t_list *begin_list)
// {
// 	t_list	*list;
// 	int		count;

// 	count = 0;
// 	list = begin_list;
// 	if (list)
// 	{
// 		while (list)
// 		{
// 			count++;
// 			list = list->next;
// 		}
// 	}
// 	return (count);
// }