/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 09:30:21 by astutz            #+#    #+#             */
/*   Updated: 2022/11/09 17:21:10 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Description
** Alloue (avec malloc(3)) et retourne la copie “fraiche” d’un tronçon
** de la chaine de caractères passée en paramètre.
** Le tronçon commence à l’index start et à pour longueur len.
** Si start et len ne désignent pas un tronçon de chaine valide,
** le comportement est indéterminé.
** Si l’allocation échoue, la fonction renvoie NULL.
** Param. #1
** La chaine de caractères dans laquelle chercher le tronçon à copier.
** Param. #2
** L’index dans la chaine de caractères où débute le tronçon à copier.
** Param. #3
** La longueur du tronçon à copier.
** Retour
** Le tronçon.
*/

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*newchain;
	size_t	i;

	if (!s)
		return (NULL);
	if (len <= 0 || (start + 1 > ft_strlen(s)))
	{
		newchain = (char *)malloc(1);
		*newchain = 0;
		return (newchain);
	}
	newchain = (char *)malloc (sizeof(char) * (len + 1));
	if (!newchain)
		return (NULL);
	i = 0;
	if (start < ft_strlen(s))
	{
		while (s[start] != '\0' && i < len)
			newchain[i++] = s[start++];
	}
	newchain[i] = '\0';
	return (newchain);
}


// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	char			*u1;
// 	unsigned int	i;

// 	i = 0;
// 	u1 = (char *)malloc((len + 1) * sizeof(char));
// 	if (u1 == 0)
// 		return (NULL);
// 	if (!s)
// 		return (NULL);
// 	u1[len] = '\0';
// 	while (len > 0)
// 	{
// 		u1[i] = s[start];
// 		i++;
// 		start++;
// 		len--;
// 	}
// 	return (u1);
// }
