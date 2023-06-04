/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 10:34:32 by astutz            #+#    #+#             */
/*   Updated: 2023/06/04 13:00:19 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include "ft_printf/includes/ft_printf.h"

typedef struct s_node {
	int				data;
	int				index;
	struct s_node	*next;
}	t_node;

//linked_list
void	add_int(t_node **head, int nb);
t_node	*get_last(t_node *head);
void	list_free(t_node **head);

//push_swap_utils
int		list_size(t_node *head);
int		isanumber(char *str);
void	print_node(t_node *head);
void	print_node_index(t_node *head);
int		free_split(char **tofree, int flag, char condition);

//rotate
void	ra(t_node **head_a);

//reverse rotate
void	rra(t_node **head_a);

//swap & push
void	pa(t_node **head_a, t_node **head_b);
void	pb(t_node **head_b, t_node **head_a);
void	sa(t_node **head_a);

//sort
void	sort(t_node **head_a, t_node **head_b);
int		index_calcuation(t_node **head, int nb);
int		to_push(int nb, int i);
int		isordered(t_node *head);

//sort small
int		position(t_node *head, int nb);
void	sort_3(t_node **head, int base);
void	sort_4(t_node **head_a, t_node **head_b, int base);
void	sort_5(t_node **head_a, t_node **head_b);

#endif
