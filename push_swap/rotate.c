/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 11:43:56 by astutz            #+#    #+#             */
/*   Updated: 2023/06/04 12:59:21 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* first element of stack A becomes last
   and all the others gain one place */
void	ra(t_node **head_a)
{
	t_node	*last;
	t_node	*second;
	t_node	*first;

	second = (*head_a)->next;
	last = get_last(*head_a);
	first = *head_a;
	last->next = first;
	last->next->next = NULL;
	*head_a = second;
	ft_printf("ra\n");
}
