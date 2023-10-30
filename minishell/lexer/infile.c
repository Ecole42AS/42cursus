/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:07:40 by astutz            #+#    #+#             */
/*   Updated: 2023/10/03 12:10:39 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_infile_stuck(char **words, t_pars *parsing, int *i,
		int *is_cmd_or_prog)
{
	*is_cmd_or_prog = 0;
	parsing->infile = open(&words[*i][1], O_RDONLY, 0777);
	if (parsing->infile < 0)
	{
		*is_cmd_or_prog = 1;
		parsing->type = 0;
		perror("minishell: wrongfile: ");
	}
}

void	ft_infile(char **words, t_pars *parsing, int *i, int *is_cmd_or_prog)
{
	*is_cmd_or_prog = 0;
	if (words[*i + 1])
	{
		parsing->infile = open(words[*i + 1], O_RDONLY, 0777);
		if (parsing->infile < 0)
		{
			*is_cmd_or_prog = 1;
			parsing->type = 0;
			perror("minishell: wrongfile: ");
		}
		*i += 1;
	}
	else
	{
		write(2, "syntax error near unexpected token `newline'", 45);
		*i += 1;
	}
}

void	ft_dinfile_stuck(char **words, t_pars *parsing, int *i)
{
	const char	*delimiter;

	delimiter = ft_substr(words[*i], 2, ft_strlen(words[*i]) - 2);
	handle_heredoc(delimiter, parsing);
}

void	ft_dinfile(char **words, t_pars *parsing, int *i)
{
	const char	*delimiter;

	if (words[*i + 1])
	{
		delimiter = words[*i + 1];
		handle_heredoc(delimiter, parsing);
		*i += 1;
	}
	else
	{
		write(2, "syntax error near unexpected token `newline'", 46);
		*i += 1;
	}
}
