/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:01:57 by astutz            #+#    #+#             */
/*   Updated: 2022/11/09 17:15:21 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*
** Description
** Alloue (avec malloc(3)) et
** retourne un tableau de chaines de caractères “fraiches”
** (toutes terminées par un ’\0’, le tableau également donc)
** résultant de la découpe de s selon le caractère c.
** Si l’allocation echoue, la fonction retourne NULL.
** Exemple : ft_strsplit("*salut*les***etudiants*", ’*’)
** renvoie le tableau ["salut", "les", "etudiants"].
** Param. #1
** La chaine de caractères à découper.
** Param. #2
** Le caractère selon lequel découper la chaine.
** Retour
** Le tableau de chaines de caractères “fraiches” résultant de la découpe.
*/

#include "libft.h"

static int	count_words (char const *s, char c)
{
	int	words;
	int	i;

	words = 0;
	i = 0;
	if (!s)
		return (0);
	if (s[i] != c)
	{
		i++;
		words++;
	}
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			words++;
		i++;
	}
	return (words);
}

static char	*make_string(char const *s, char c)
{
	char	*word;
	int		i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	word = (char *)malloc (sizeof(char) * (i + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		num_words;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	num_words = count_words(s, c);
	result = (char **)malloc (sizeof(char *) * (num_words + 1));
	if (!result)
		return (NULL);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			result[i] = make_string (s, c);
			i++;
			while (*s && *s != c)
				s++;
		}
	}
	result[i] = NULL;
	return (result);
}
