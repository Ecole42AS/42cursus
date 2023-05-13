/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 11:43:14 by astutz            #+#    #+#             */
/*   Updated: 2023/05/13 20:34:10 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* returns true if it is a number, false otherwise */
int	isanumber(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' && ft_isdigit(str[1]))
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/* prints the element of the list */
void	prins_list(s_list *head)
{
	s_list	*current;

	current = head;
	while (current != NULL)
	{
		ft_printf("%d ", current->data);
		current = current->next;
	}
	write(1, "\n", 1);
}

/*prints the index */
void	prins_list_index(s_list *head)
{
	s_list	*current;

	current = head;
	while (current != NULL)
	{
		ft_printf("%d ", current->index);
		current = current->next;
	}
	write(1, "\n", 1);
}

/* returns length of linked list */
int	list_size(s_list *head)
{
	s_list	*current;
	int		count;

	count = 0;
	current = head;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

/* free the split and returns the flag int
   if condition == "f", frees otherwise not */
int	free_split(char **tofree, int flag, char condition)
{
	int	i;

	if (condition == 'f')
	{
		i = -1;
		while (tofree[++i])
		{
			free(tofree[i]);
		}
		free(tofree);
	}
	return (flag);
}
