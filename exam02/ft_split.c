/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 15:34:51 by astutz            #+#    #+#             */
/*   Updated: 2023/01/04 17:17:37 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>



int	ft_wordlen(char *str)
{
	int i = 0;

	while (str[i] != '\0' && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
		++i;
	return (i);
}

char* worddup(char *str)
{
	int i;
	int len;
	char *word;
	
	len = ft_wordlen(str);
	i = 0;
	word = malloc(sizeof(char) * (len + 1));
	word[len] = '\0';
	while (i < len)
	{
		word[i] = str[i];
		i++;
	}
	return (word);
}

// char	*word_dupe(char *str)
// {
// 	int i = 0;
// 	int len = ft_wordlen(str);
// 	char *word = malloc(sizeof(char) * (len + 1));
	
// 	word[len] = '\0';
// 	while (i < len)
// 	{
// 		word[i] = str[i];
// 		++i;
// 	}
// 	return (word);
// }

// void fill_word(char **split, char *str)
// {
// 	int i;
// 	int word_index;

// 	i = 0;
// 	word_index = 0;
// 	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
// 		i++;
// 	while (str[i] != '\0')
// 	{
// 		split[word_index] = worddup(str);
// 		++word_index;
// 		while (str[i] != '\0' && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
// 			++i;
// 		while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
// 			++i;
// 	}
// }

// PK CA NE MARCHE PAS !!

void	fill_word(char **array, char *str)
{
	int word_index = 0;
	
	while (*str == ' ' || *str == '\t' || *str == '\n')
		++str;
	while (*str != '\0')
	{
		array[word_index] = worddup(str);
		++word_index;
		while (*str != '\0' && *str != ' ' && *str != '\t' && *str != '\n')
			++str;
		while (*str == ' ' || *str == '\t' || *str == '\n')
			++str;
	}
}

int count_words(char *str)
{
	int i;
	int word_count;
	
	word_count = 0;
	i = 0;
	while (str[i] == '\n' || str[i] == '\t' || str[i] == ' ')
		i++;
	while (str[i])
	{
		word_count++;
		while (str[i] != '\0' && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			i++;
		while (str[i] == '\n' || str[i] == '\t' || str[i] == ' ')
			i++;
	}
	return (word_count);
}

char    **ft_split(char *str)
{
	int num_words;
	char **array;

	num_words = count_words(str);
	array = malloc(sizeof(char *) * (num_words + 1));
	if (!array)
		return (NULL);
	array[num_words] = 0;
	fill_word(array, str);
	return (array);
}

int main()
{
	char **split;
	char str[] = " 	hello 	mon 	frere   zeubi		 ";


	split = ft_split(str);
	printf("%s", split[0]);
}