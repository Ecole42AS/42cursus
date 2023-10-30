/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 08:42:36 by astutz            #+#    #+#             */
/*   Updated: 2023/10/06 08:42:39 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	display_line(char *input)
{
	if (ft_is_only_space(input))
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

int	quotes(char *input, int *i, t_ends *ends, int quote)
{
	*i += 1;
	ends->start = *i;
	if (quote == '\'')
		ends->in_squotes = 1;
	while (input[*i] != quote && input[*i])
		*i += 1;
	if (input[*i] == quote)
	{
		ends->end = *i;
		*i += 1;
		return (0);
	}
	else
	{
		if (quote == '\'')
			write(2, "Error: no closing for single quotes.\n", 38);
		if (quote == '\"')
			write(2, "Error: no closing for double quotes.\n", 38);
		display_line(input);
		return (1);
	}
}
