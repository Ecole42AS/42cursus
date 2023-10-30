/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_only_space.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 21:01:27 by astutz            #+#    #+#             */
/*   Updated: 2023/09/29 10:07:54 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Vérifie si la chaîne de caractère n'a que des espaces ou des tabs*/
int	ft_is_only_space(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] != 32 && str[i] != '\t')
			return (0);
	return (1);
}
