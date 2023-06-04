/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_and_push.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 11:45:38 by astutz            #+#    #+#             */
/*   Updated: 2023/06/04 13:13:22 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* puts first element of list B and puts it
   on top of list A, returns if list
   A is NULL */
void	pa(t_nlist **head_a, t_nlist **head_b)
{
	t_nlist	*ele_b;

	if (*head_b)
	{
		ele_b = *head_b;
		*head_b = ele_b->next;
		ele_b->next = *head_a;
		*head_a = ele_b;
		ft_printf("pa\n");
	}
}

/* puts first element of list A and puts it
   on top of list B, returns if list
   B is NULL */
void	pb(t_nlist **head_b, t_nlist **head_a)
{
	t_nlist	*ele_a;

	if (*head_a)
	{
		ele_a = *head_a;
		*head_a = ele_a->next;
		ele_a->next = *head_b;
		*head_b = ele_a;
		ft_printf("pb\n");
	}
}

/* swaps first 2 elements top of list A */
void	sa(t_nlist **head_a)
{
	t_nlist	*ele1;
	t_nlist	*ele2;

	ele1 = *head_a;
	ele2 = (*head_a)->next;
	if (!ele1 || !ele2)
		return ;
	ele1->next = ele2->next;
	ele2->next = ele1;
	*head_a = ele2;
	ft_printf("sa\n");
}
