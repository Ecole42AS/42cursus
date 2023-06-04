/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 10:32:46 by astutz            #+#    #+#             */
/*   Updated: 2023/06/04 12:59:21 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*  add the integer to the end
	of the linked list using malloc */
void	add_int(t_node **head, int nb)
{
	t_node	*new_node;
	t_node	*current;

	new_node = (t_node *) malloc(sizeof(t_node));
	new_node->data = nb;
	new_node->index = index_calcuation(head, new_node->data);
	new_node->next = NULL;
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	current = get_last(*head);
	current->next = new_node;
}

/* returns last element of the linked list */
t_node	*get_last(t_node *head)
{
	t_node	*last;

	if (!head)
		return (NULL);
	last = head;
	while (last->next)
		last = last->next;
	return (last);
}

/*frees list entirely (ne free pas head)*/
void	list_free(t_node **head)
{
	t_node	*current;
	t_node	*stock;

	stock = *head;
	while (stock != NULL)
	{
		current = stock;
		stock = stock->next;
		free(current);
	}
	*head = NULL;
}
