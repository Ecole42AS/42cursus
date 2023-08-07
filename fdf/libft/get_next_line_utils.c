/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 17:45:09 by astutz            #+#    #+#             */
/*   Updated: 2023/07/30 17:47:27 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Modification to the original strjoin to handle s1 which is malloc. */
char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	char	*ptr;
	int		i;
	int		j;

	i = -1;
	j = -1;
	ptr = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (ptr == 0)
		return (NULL);
	while (s1[++i] != '\0')
		ptr[i] = s1[i];
	while (s2[++j] != '\0')
		ptr[i + j] = s2[j];
	ptr[i + j] = '\0';
	free((char *)s1);
	return (ptr);
}
