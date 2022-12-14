/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_list_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 15:49:41 by astutz            #+#    #+#             */
/*   Updated: 2022/12/26 15:50:58 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_list_test.h"
#include <stdio.h>
#include <stdlib.h>

int	ft_list_size(t_list *begin_list)
{
	t_list	*list;
	int		count;

	count = 0;
	list = begin_list;
	if (list)
	{
		while (list)
		{
			count++;
			list = list->next;
		}
	}
	return (count);
}

t_list	*new(void *data)
{
	t_list *n;

	n = (t_list *)malloc(sizeof(t_list));
	if (n)
	{
		n->data = data;
		n->next = NULL;
	}
	return (n);
}

int main()
{
	t_list *p, *s, *j, *t;

	p = new("One");
	s = new("Two");
	j = new("Three");
	t = new("Four");
	p->next = s;
	s->next = j;
	j->next = t;
	printf("%d\n", ft_list_size(s));
	return 0;
}