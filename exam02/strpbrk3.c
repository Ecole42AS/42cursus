/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strpbrk3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 19:39:13 by astutz            #+#    #+#             */
/*   Updated: 2023/01/11 20:14:10 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>

char *ft_strpbrk(const char *s, char *accept)
{
	int i;
	int j;

	i = 0;
	while (s[i])
	{
		j = 0;
		while (accept[j])
		{
			if (s[i] == accept[j])
				return ((char *)(s + i));
			j++;
		}
		i++;
	}
	return (0);
}

int main()
{
	char s[] = "hello";
	char accept[] = "hl";
	char *result;
	char *result1;

	result = strpbrk(s, accept);
	result1 = ft_strpbrk(s, accept);
	printf("%s\n-------", result);
	printf("%s", result1);

}