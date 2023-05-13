/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 10:34:00 by astutz            #+#    #+#             */
/*   Updated: 2023/05/13 20:54:43 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* returns true if nb is a double, false otherwise */
int	isdouble(s_list *head, int nb)
{
	s_list	*current;

	current = head;
	while (current)
	{
		if (current->data == nb)
			return (1);
		current = current->next;
	}
	return (0);
}

/* returns true if number is out-range */
int	isoutrange(char *nb)
{
	long long	number;
	int			len;
	int			sgn;
	int			i;

	number = 0;
	i = -1;
	len = ft_strlen(nb);
	sgn = 1;
	if (nb[0] == '-')
	{
		sgn = -1;
		i++;
	}
	while (++i < len)
	{
		if (!ft_isdigit(nb[i]))
			return (1);
		number = number * 10 + (nb[i] - '0');
	}
	number *= sgn;
	if (number > 2147483647 || number < -2147483648)
		return (1);
	return (0);
}

/* adds an array to the stack A
	returns false if error, true otherwise
	condition free if split, none otherwise */
int	array_to_add(char **nb, s_list **head, int flag, char condition)
{
	int	i;

	i = -1;
	if (flag == 1)
		i++;
	while (nb[++i])
	{
		if (isoutrange(nb[i]))
			return (free_split(nb, 0, condition));
		if (!isanumber(nb[i]))
			return (free_split(nb, 0, condition));
		if (isdouble(*head, ft_atoi(nb[i])))
			return (free_split(nb, 0, condition));
		add_int(head, ft_atoi(nb[i]));
	}
	return (free_split(nb, 1, condition));
}

/* choses the good sorting algorithm
   based on the size of the stack */
void	choose_sorting(s_list **head_a, s_list **head_b)
{
	int	size;

	size = list_size(*head_a);
	if (!isordered(*head_a))
	{
		if (size <= 1)
			return ;
		else if (size == 2)
				sa(head_a);
		else if (size == 3)
			sort_3(head_a, 0);
		else if (size == 4)
			sort_4(head_a, head_b, 0);
		else if (size == 5)
			sort_5(head_a, head_b);
		else
			sort(head_a, head_b);
	}
}

/* launches the program */
int	main(int ac, char **av)
{
	static s_list	*head_a;
	static s_list	*head_b;

	if (ac == 1 || av[1] == NULL)
		return (0);
	else if (ac == 2)
	{
		if (!array_to_add(ft_split(av[1], ' '), &head_a, 0, 'f'))
		{
			(ft_putstr_fd("Error\n", 2));
			return (1);
		}
	}
	else
	{
		if (!array_to_add(av, &head_a, 1, ' '))
		{
			(ft_putstr_fd("Error\n", 2));
			return (1);
		}
	}
	choose_sorting(&head_a, &head_b);
	list_free(&head_a);
	list_free(&head_b);
	return (0);
}
