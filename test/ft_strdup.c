/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 15:04:41 by astutz            #+#    #+#             */
/*   Updated: 2022/12/26 15:18:21 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

char    *ft_strdup(char *src)
{
	char *str;
	int i;
	int len;

	len = 0;
	while(src[len])
		len++;
	if (!src)
		return (0);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (0);
	i = 0;
	while(src[i])
		str[i++] = src[i];
	str[i] = '\0';
	return (str);
}


int main()
{
	char src[] = "hello";
	char *str;
	
	str = ft_strdup(src);
	printf("%s", str);
}