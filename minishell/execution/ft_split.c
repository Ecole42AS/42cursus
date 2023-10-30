/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sepi <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 14:07:42 by mde-sepi          #+#    #+#             */
/*   Updated: 2022/09/14 14:17:44 by mde-sepi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

char	**creamal(int row, int collums)
{
	char	**ret;
	int		i;
	char	*ptr;

	ret = malloc((row + 1) * sizeof(ptr));
	i = 0;
	while (i < row)
	{
		ret[i] = malloc(collums + 1);
		i++;
	}
	ret[row] = NULL;
	return (ret);
}

int	longestword(char *str, char c)
{
	int	i;
	int	length;
	int	max;

	i = 0;
	max = 0;
	while (str[i] != '\0')
	{	
		length = 0;
		while (str[i] != c && str[i] != '\0')
		{
			length++;
			i++;
		}
		if (length > max)
			max = length;
		if (str[i] != '\0')
			i++;
	}
	return (max);
}

int	wordcount(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c || str[i] == '\0')
		{
			while (str[i] == c)
				i++;
			count++;
		}
		i++;
	}
	return (count + 1);
}

void	str_copy(int *s, int *e, char *new, char *old)
{
	int	i;

	i = 0;
	while (*s + i < *e)
	{
		new[i] = old[*s + i];
		i++;
	}
	new[i] = '\0';
	*s = *e + 1;
}

char	**ft_split(char *str, char charset)
{
	char	**ret;
	int		i;
	int		coupe;
	int		mot;

	ret = creamal(wordcount(str, charset), longestword(str, charset));
	i = 0;
	coupe = 0;
	mot = -1;
	while (1)
	{	
		if (str[i] == charset || str[i] == '\0')
		{	
			while (str[coupe] == charset)
					coupe++;
			if (i > coupe)
				str_copy(&coupe, &i, ret[++mot], str);
		}
		if (str[i] == '\0')
			break ;
		i++;
	}
	return (ret);
}
