/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:02:54 by astutz            #+#    #+#             */
/*   Updated: 2022/12/26 13:55:26 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

size_t ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

size_t	ft_strcspn(const char *s, const char *reject)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s[i])
	{
		j = 0;
		while (reject[j])
		{
			if (reject[j] == s[i])
				return (i);
			j++;
		}
		i++;
	}
	return (ft_strlen(s));
}

int main()
{
	char s[] = "astutz123456789";
	char reject[] = "d";
	size_t num;
	size_t num1;
	
	num = ft_strcspn(s, reject);
	num1 = strcspn(s, reject);
	printf("%s\n", s);
	printf("%ld\n", num);
	printf("%ld", num1);
}