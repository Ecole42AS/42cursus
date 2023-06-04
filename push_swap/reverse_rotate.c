/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 11:43:36 by astutz            #+#    #+#             */
/*   Updated: 2023/06/04 12:59:21 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* last element of stack A becomes first
   and all the elements go down one place */
void	rra(t_node **head_a)
{
	t_node	*last;
	t_node	*pre_last;
	t_node	*first;

	last = get_last(*head_a);
	first = *head_a;
	pre_last = *head_a;
	while (pre_last->next != last)
		pre_last = pre_last->next;
	pre_last->next = NULL;
	last->next = first;
	*head_a = last;
	ft_printf("rra\n");
}
