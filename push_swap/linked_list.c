/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 10:32:46 by astutz            #+#    #+#             */
/*   Updated: 2023/06/04 13:13:22 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*  add the integer to the end
	of the linked list using malloc */
void	add_int(t_nlist **head, int nb)
{
	t_nlist	*new_node;
	t_nlist	*current;

	new_node = (t_nlist *) malloc(sizeof(t_nlist));
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
t_nlist	*get_last(t_nlist *head)
{
	t_nlist	*last;

	if (!head)
		return (NULL);
	last = head;
	while (last->next)
		last = last->next;
	return (last);
}

/*frees list entirely (ne free pas head)*/
void	list_free(t_nlist **head)
{
	t_nlist	*current;
	t_nlist	*stock;

	stock = *head;
	while (stock != NULL)
	{
		current = stock;
		stock = stock->next;
		free(current);
	}
	*head = NULL;
}
