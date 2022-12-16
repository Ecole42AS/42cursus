/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpbrk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 12:57:33 by astutz            #+#    #+#             */
/*   Updated: 2022/12/14 09:22:48 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio.h"
#include <string.h>

char	*ft_strpbrk(const char *s1, const char *s2)
{
	int i;
	int j;

	if (!s1 || !s2)
		return (0);
	i = 0;
	while (s1[i])
	{
		j = 0;
		while (s2[j])
		{
			if (s1[i] == s2[j])
				return ((char *)(s1 + i));
			j++;
		}
		i++;
	}
	return (0);
}

int main()
{
	char s1[] = "astutz123456789";
	char s2[] = "";
	char *res;
	char *res1;
	
	res = ft_strpbrk(s1, s2);
	res1 = strpbrk(s1, s2);
	printf("%s\n", res);
	printf("%s", res1);
}