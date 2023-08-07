/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 22:00:39 by astutz            #+#    #+#             */
/*   Updated: 2023/08/07 15:04:54 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

void *ft_calloc(size_t nmemb, size_t size)
{
    void *array = malloc(nmemb * size);
    if (array != NULL)
    {
        size_t i = 0;
        char *str = (char *)array;
        while (i < nmemb * size)
        {
            str[i] = 0;
            i++;
        }
    }
    return array;
}

char *ftd_strchr(const char *s, int c)
{
	int i;

	i = -1;
	while(s[++i])
	{
		if (s[i] == c)
			return ((char *)(s + i));
	}
	return (NULL);
}

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s != '\0' && *s != (char)c)
		s++;
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

char *ft_strstr(const char *haystack, const char *needle)
{
	char *to_find;
	char *str;

	str = (char*)haystack;
	to_find = (char*)needle;
	if(!*to_find)
		return(str);
	while(*str)
	{
		if (*str == *needle && memcmp(str, to_find, strlen(to_find)) == 0)
			return (str);
		str++;
	}
	return (NULL);
}

int main()
{
	int *c;
	int i;
	char *x;
	char *y;
	char *dest;
	char *src;
	
	dest = "frewfr";
	src = "rfd";
	// i = -1;
	// c = (int*)ft_calloc(4, sizeof(int));
	// if (!c)
	// 	printf("2");
	// while(++i < 4)
	// 	printf("%d \n", (c[i]));
	// x = ftd_strchr(str, src);
	// y = ft_strchr(str, src);
	// printf("%s // %s(diabolo)", x, y);
	x = strncpy(dest, src, strlen(src));
	strlcpy(dest, src, strlen(src));
	printf("%s \n%s(myfunc)", x, dest);
	return(0);
}
