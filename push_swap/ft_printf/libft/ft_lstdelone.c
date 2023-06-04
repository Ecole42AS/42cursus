/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 08:17:36 by astutz            #+#    #+#             */
/*   Updated: 2023/06/04 13:13:58 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(s_nlist *lst, void (*del)(void*))
{
	if (lst && del)
	{
		del(lst ->content);
		free(lst);
	}
}
