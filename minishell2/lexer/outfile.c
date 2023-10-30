/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:00:31 by astutz            #+#    #+#             */
/*   Updated: 2023/10/03 12:06:33 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_outfile_stuck(char **words, t_pars *parsing, int *i)
{
	parsing->outfile = open(&words[*i][1], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (parsing->outfile < 0)
		perror("minishell: wrongfile: ");
}

void	ft_outfile(char **words, t_pars *parsing, int *i)
{
	if (words[*i + 1])
	{
		parsing->outfile = open(words[*i + 1], O_CREAT | O_WRONLY
				| O_TRUNC, 0777);
		if (parsing->outfile < 0)
			perror("minishell: wrongfile: ");
		*i += 1;
	}
	else
	{
		write(2, "syntax error near unexpected token `newline'", 46);
		*i += 1;
	}
}

void	ft_doutfile_stuck(char **words, t_pars *parsing, int *i)
{
	char	*file_name;

	file_name = ft_substr(words[*i], 2, ft_strlen(words[*i]) - 2);
	parsing->outfile = open(file_name, O_CREAT | O_RDWR | O_APPEND, 0777);
	if (parsing->outfile < 0)
		perror("file does not exist");
}

void	ft_doutfile(char **words, t_pars *parsing, int *i)
{
	if (words[*i + 1])
	{
		parsing->outfile = open(words[*i + 1], O_CREAT | O_RDWR
				| O_APPEND, 0777);
		if (parsing->outfile < 0)
			perror("open failed");
		*i += 1;
	}
	else
		write(2, "syntax error near unexpected token `newline'", 46);
}
