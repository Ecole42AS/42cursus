/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_and_push.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 11:45:38 by astutz            #+#    #+#             */
/*   Updated: 2023/05/13 11:45:41 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* puts first element of list B and puts it
   on top of list A, returns if list
   A is NULL */
void	pa(t_list **head_a, t_list **head_b)
{
	t_list	*ele_b;

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
void	pb(t_list **head_b, t_list **head_a)
{
	t_list	*ele_a;

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
void	sa(t_list **head_a)
{
	t_list	*ele1;
	t_list	*ele2;

	ele1 = *head_a;
	ele2 = (*head_a)->next;
	if (!ele1 || !ele2)
		return ;
	ele1->next = ele2->next;
	ele2->next = ele1;
	*head_a = ele2;
	ft_printf("sa\n");
}
