/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 11:45:21 by astutz            #+#    #+#             */
/*   Updated: 2023/06/04 13:13:22 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* returns position of the demanded index in the list */
int	position(t_nlist *head, int nb)
{
	t_nlist	*current;
	int		pos;

	current = head;
	pos = 0;
	while (current)
	{
		if (current->index == nb)
			return (pos);
		pos++;
		current = current->next;
	}
	return (0);
}

/* sorting algorithm for 3 numbers */
void	sort_3(t_nlist **head, int base)
{
	if (isordered(*head))
		return ;
	if ((*head)->index == base && (*head)->next->index == base + 2)
	{
		sa(head);
		ra(head);
	}
	else if ((*head)->index == base + 1 && (*head)->next->index == base)
		sa(head);
	else if ((*head)->index == base + 1 && (*head)->next->index == base + 2)
		rra(head);
	else if ((*head)->index == base + 2 && (*head)->next->index == base + 1)
	{
		ra(head);
		sa(head);
	}
	else if ((*head)->index == base + 2 && (*head)->next->index == base)
		ra(head);
}

/* sorting algorithm for 4 numbers */
void	sort_4(t_nlist **head_a, t_nlist **head_b, int base)
{
	if (position(*head_a, base) < 2)
	{
		while ((*head_a)->index != base)
			ra(head_a);
	}
	else
	{
		while ((*head_a)->index != base)
			rra(head_a);
	}
	pb(head_b, head_a);
	sort_3(head_a, base + 1);
	pa(head_a, head_b);
}

/* sorting algorithm for 5 numbers */
void	sort_5(t_nlist **head_a, t_nlist **head_b)
{
	if (position(*head_a, 0) < 3)
	{
		while ((*head_a)->index != 0)
			ra(head_a);
	}
	else
	{
		while ((*head_a)->index != 0)
			rra(head_a);
	}
	pb(head_b, head_a);
	sort_4(head_a, head_b, 1);
	pa(head_a, head_b);
}
