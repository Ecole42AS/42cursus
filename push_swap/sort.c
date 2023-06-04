/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 11:44:52 by astutz            #+#    #+#             */
/*   Updated: 2023/06/04 13:13:22 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* returns the index of the number and actualize the others */
int	index_calcuation(t_nlist **head, int nb)
{
	t_nlist	*current;
	int		i;

	i = 0;
	if (!head)
		return (0);
	current = *head;
	while (current)
	{
		if (current->data > nb)
			current->index += 1;
		else
			i++;
		current = current->next;
	}
	return (i);
}

/* returns true if numbers needs to be pushed
   meaning that the bit == 0 */
int	to_push(int nb, int i)
{
	if ((nb >> i) & 1)
		return (0);
	return (1);
}

/* returns true if list is ordered */
int	isordered(t_nlist *head)
{
	t_nlist	*current;
	int		min;

	current = head;
	min = 0;
	while (current)
	{
		if (current->index != min)
			return (0);
		++min;
		current = current->next;
	}
	return (1);
}

/* sorting algorithm */
void	sort(t_nlist **head_a, t_nlist **head_b)
{
	static int	bit_position;
	t_nlist		*current;
	int			size;
	int			i;

	while (!isordered(*head_a))
	{
		size = list_size(*head_a);
		i = -1;
		while (++i < size)
		{
			current = *head_a;
			if (to_push(current->index, bit_position))
				pb(head_b, head_a);
			else
				ra(head_a);
		}
		size = list_size(*head_b);
		while (--size >= 0)
			pa(head_a, head_b);
		++bit_position;
	}
}
