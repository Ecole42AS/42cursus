/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 20:46:59 by astutz            #+#    #+#             */
/*   Updated: 2023/06/04 13:13:58 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

s_nlist	*ft_lstnew(void *content)
{
	s_nlist	*new;

	new = malloc(sizeof(s_nlist));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}
