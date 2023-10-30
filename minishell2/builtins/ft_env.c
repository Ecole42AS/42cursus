/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sepi <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 14:07:42 by mde-sepi          #+#    #+#             */
/*   Updated: 2022/09/14 14:17:44 by mde-sepi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "../minishell.h"

void	env(char **env_table)
{
	int	i;

	i = 0;
	while (env_table[i])
	{
		write(1, env_table[i], ft_strlen(env_table[i]));
		write(1, "\n", 1);
		i++;
	}
}
