/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sepi <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 14:07:42 by mde-sepi          #+#    #+#             */
/*   Updated: 2022/09/14 14:17:44 by mde-sepi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "../minishell.h"

char	**new_matrix(char **old, int size_change)
{
	int		len;
	int		max_len;
	char	**ret;
	int		i;

	len = 0;
	while (old[len])
	{
		max_len = max(max_len, ft_strlen(old[len]));
		len++;
	}
	ret = malloc((len + 1 + size_change) * sizeof(char *));
	i = 0;
	while (i <= len + size_change)
	{
		ret[i] = malloc(max_len * sizeof(char) + 1);
		i++;
	}
	return (ret);
}

int	comp_bfr_eq(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] && str1[i] != '=')
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	if (str2[i] != '\0' && str2[i] != '=')
		return (0);
	return (1);
}

char	*bfr_aftr_eq(char *str, int spot, int len)
{
	int		i;
	char	*temp;

	i = 0;
	if (spot == 0)
	{
		temp = malloc((len + 1) * sizeof(char));
		ft_strcpy(temp, str);
		while (str[i])
		{
			if (str[i] == '=')
				temp[i] = '\0';
			i++;
		}
		return (temp);
	}
	else if (spot == 1)
	{
		while (str[i] && str[i] != '=')
			i++;
		return (&str[i + 1]);
	}
	else
		return (str);
}

char	**remove_line(char **table, int spot)
{
	char	**ret;
	int		len;
	int		i;

	ret = new_matrix(table, -1);
	i = 0;
	len = 0;
	while (table[i] != NULL)
	{
		if (i != spot)
		{
			ft_strcpy(ret[len], table[i]);
			len++;
		}
		free(table[i]);
		i++;
	}
	free(ret[len]);
	ret[len] = NULL;
	free(table);
	return (ret);
}

int	unset(char ***env_table, char **argv)
{
	int	i;
	int	j;

	j = 1;
	while (argv[j])
	{
		i = 0;
		while (env_table[0][i])
		{
			if (comp_bfr_eq(env_table[0][i], argv[j]))
			{
				*env_table = remove_line(*env_table, i);
				break ;
			}
			i++;
		}
		j++;
	}
	return (1);
}
