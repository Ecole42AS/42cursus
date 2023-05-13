/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 10:34:32 by astutz            #+#    #+#             */
/*   Updated: 2023/05/13 12:21:10 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include "ft_printf/includes/ft_printf.h"

typedef struct t_list {
	int				data;
	int				index;
	struct t_list	*next;
}	s_list;

//linked_list
void	add_int(s_list **head, int nb);
s_list	*get_last(s_list *head);
void	list_free(s_list **head);

//push_swap_utils
int		list_size(s_list *head);
int		isanumber(char *str);
void	prins_list(s_list *head);
void	prins_list_index(s_list *head);
int		free_split(char **tofree, int flag, char condition);

//rotate
void	ra(s_list **head_a);

//reverse rotate
void	rra(s_list **head_a);

//swap & push
void	pa(s_list **head_a, s_list **head_b);
void	pb(s_list **head_b, s_list **head_a);
void	sa(s_list **head_a);

//sort
void	sort(s_list **head_a, s_list **head_b);
int		index_calcuation(s_list **head, int nb);
int		to_push(int nb, int i);
int		isordered(s_list *head);

//sort small
int		position(s_list *head, int nb);
void	sort_3(s_list **head, int base);
void	sort_4(s_list **head_a, s_list **head_b, int base);
void	sort_5(s_list **head_a, s_list **head_b);

#endif
