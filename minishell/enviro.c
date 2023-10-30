/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviro.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 14:07:42 by mde-sepi          #+#    #+#             */
/*   Updated: 2023/10/02 18:30:50 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"

int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

void	del_env(char ***env_table)
{
	int	i;

	i = 0;
	while (env_table[0][i])
	{
		free(env_table[0][i]);
		i++;
	}
	free(env_table[0]);
	free(env_table);
}

char	**init_env(char **env)
{
	char	**env_table;
	int		len;
	int		max_len;

	len = 0;
	max_len = 0;
	while (env[len])
	{
		max_len = max(max_len, ft_strlen(env[len]));
		len++;
	}
	env_table = ft_calloc((len + 1), sizeof(char *));
	env_table[len] = NULL;
	while (len > 0)
	{
		len--;
		env_table[len] = ft_calloc(max_len + 1, 2 * sizeof(char));
		ft_strcpy(env_table[len], env[len]);
		env_table[len][max_len] = '\0';
	}
	return (env_table);
}

char	*ft_get_env(char *str, char ***env_table)
{
	int	i;

	i = 0;
	while (env_table[0][i])
	{
		if (comp_bfr_eq(env_table[0][i], str))
			return (bfr_aftr_eq(env_table[0][i], 1,
				ft_strlen(env_table[0][i]) + 1));
		i++;
	}
	return (NULL);
}
