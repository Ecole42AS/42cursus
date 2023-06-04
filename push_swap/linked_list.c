/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 10:32:46 by astutz            #+#    #+#             */
/*   Updated: 2023/06/04 12:20:22 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*  add the integer to the end
	of the linked list using malloc */
void	add_int(s_list **head, int nb)
{
	s_list	*new_node;
	s_list	*current;

	new_node = (s_list *) malloc(sizeof(s_list));
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
s_list	*get_last(s_list *head)
{
	s_list	*last;

	if (!head)
		return (NULL);
	last = head;
	while (last->next)
		last = last->next;
	return (last);
}

/*frees list entirely (ne free pas head)*/
void	list_free(s_list **head)
{
	s_list	*current;
	s_list	*stock;

	stock = *head;
	while (stock != NULL)
	{
		current = stock;
		stock = stock->next;
		free(current);
	}
	*head = NULL;
}
