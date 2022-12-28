/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 22:33:44 by astutz            #+#    #+#             */
/*   Updated: 2022/12/28 21:19:28 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	// if (s[i] == (char)c)
	// 	return ((char *)&s[i]);
	return (NULL);
}

int main()
{
	// char	str[] = "ood";
	// char	*res;
	// res = ft_strchr(str, 'l');
}