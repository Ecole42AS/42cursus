/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 08:14:55 by astutz            #+#    #+#             */
/*   Updated: 2022/12/10 08:20:47 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

char    *ft_strcpy(char *s1, char *s2)
{
	int	i;

	i = 0;
	while(s1[i] && s2[i])
		s1[i++] = s2[i];
	s1[i] = 0;
	return (s1);
}

int main()
{
	char dest[] = "hello";
	char src[] = "haribobest";

	ft_strcpy(dest, src);
	printf("%s", dest);
}