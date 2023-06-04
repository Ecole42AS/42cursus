/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 08:49:30 by astutz            #+#    #+#             */
/*   Updated: 2023/06/04 13:00:19 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

s_node	*ft_lstmap(s_node *lst, void *(*f)(void *), void (*del)(void *))
{
	s_node	*lstnew;
	s_node	*lstfinal;

	if (!lst || !f)
		return (NULL);
	lstfinal = NULL;
	while (lst)
	{
		lstnew = ft_lstnew(f(lst->content));
		if (!lstnew)
		{
			ft_lstclear(&lst, del);
			return (NULL);
		}
		ft_lstadd_back(&lstfinal, lstnew);
		lst = lst->next;
	}
	return (lstfinal);
}

// s_node	*ft_lstmap(s_node *lst, void *(*f)(void *), void (*del)(void *))
// {
// 	s_node	*newlst;
// 	s_node	*newelement;

// 	if (lst == NULL || (*f) == NULL || (*del) == NULL)
// 		return (NULL);
// 	newlst = NULL;
// 	while (lst != NULL)
// 	{
// 		newelement = ft_lstnew((*f)(lst->content));
// 		if (newelement == NULL)
// 		{
// 			ft_lstclear(&newelement, del);
// 			return (NULL);
// 		}
// 		ft_lstadd_back(&newlst, newelement);
// 		lst = lst->next;
// 	}
// 	return (newlst);
// }
