/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 10:34:32 by astutz            #+#    #+#             */
/*   Updated: 2023/06/04 13:13:58 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include "ft_printf/includes/ft_printf.h"

typedef struct s_nlist {
	int				data;
	int				index;
	struct s_nlist	*next;
}	t_nlist;

//linked_list
void	add_int(t_nlist **head, int nb);
t_nlist	*get_last(t_nlist *head);
void	list_free(t_nlist **head);

//push_swap_utils
int		list_size(t_nlist *head);
int		isanumber(char *str);
void	print_nlist(t_nlist *head);
void	print_nlist_index(t_nlist *head);
int		free_split(char **tofree, int flag, char condition);

//rotate
void	ra(t_nlist **head_a);

//reverse rotate
void	rra(t_nlist **head_a);

//swap & push
void	pa(t_nlist **head_a, t_nlist **head_b);
void	pb(t_nlist **head_b, t_nlist **head_a);
void	sa(t_nlist **head_a);

//sort
void	sort(t_nlist **head_a, t_nlist **head_b);
int		index_calcuation(t_nlist **head, int nb);
int		to_push(int nb, int i);
int		isordered(t_nlist *head);

//sort small
int		position(t_nlist *head, int nb);
void	sort_3(t_nlist **head, int base);
void	sort_4(t_nlist **head_a, t_nlist **head_b, int base);
void	sort_5(t_nlist **head_a, t_nlist **head_b);

#endif
