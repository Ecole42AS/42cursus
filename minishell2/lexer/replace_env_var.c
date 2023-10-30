/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 10:39:17 by astutz            #+#    #+#             */
/*   Updated: 2023/10/05 10:18:26 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*replace_env_var(char *input, t_pars *parsing)
{
	int		i;
	int		new_len;
	char	*result;

	i = 0;
	result = (char *)
		ft_malloc_failed_msg(ft_strlen(input) + 1, sizeof(char));
	ft_strcpy(result, input);
	while (result[i])
	{
		if (result[i] == '$' && (result[i + 1] != '\t' && result[i + 1] != ' '))
		{
			if (result[i + 1] == '?')
				result = replace_exit_code(result, &i, &new_len);
			result = replace_env_value(result, parsing, &new_len, &i);
		}
		i++;
	}
	return (result);
}
