/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <alex.rastafari@hotmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:41:36 by astutz            #+#    #+#             */
/*   Updated: 2022/10/26 15:41:37 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "libft.h"
// #include "stdio.h"

int		ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') ||
			(c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

// int main()
// {
//   int res = ft_isalpha(65);
//   printf("%d", res);
// }