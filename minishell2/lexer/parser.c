/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 20:10:22 by astutz            #+#    #+#             */
/*   Updated: 2023/10/03 14:53:43 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	chevrons(char **words, t_pars *parsing, int *i, int *is_cmd_or_prog)
{
	if (words[*i][0] == '<' && words[*i][1] != 0 && words[*i][1] != '<')
		ft_infile_stuck(words, parsing, i, is_cmd_or_prog);
	else if (!ft_strncmp(words[*i], "<", ft_strlen(words[*i])))
		ft_infile(words, parsing, i, is_cmd_or_prog);
	else if (words[*i][0] == '>' && words[*i][1] != 0 && words[*i][1] != '>')
		ft_outfile_stuck(words, parsing, i);
	else if (!ft_strncmp(words[*i], ">", ft_strlen(words[*i])))
		ft_outfile(words, parsing, i);
	else if (!ft_strncmp(words[*i], "<<", ft_strlen(words[*i])))
		ft_dinfile(words, parsing, i);
	else if (words[*i][0] == '<' && words[*i][1] == '<' && words[*i][2] != 0)
		ft_dinfile_stuck(words, parsing, i);
	else if (!ft_strncmp(words[*i], ">>", ft_strlen(words[*i])))
		ft_doutfile(words, parsing, i);
	else if (words[*i][0] == '>' && words[*i][1] == '>' && words[*i][2] != 0)
		ft_doutfile_stuck(words, parsing, i);
}

void	parser(char **words, t_pars *parsing)
{
	int			i;
	int			is_cmd_or_prog;

	i = 0;
	is_cmd_or_prog = 0;
	while (words[i])
	{
		if (words[i][0] == '<' || words[i][0] == '>')
			chevrons(words, parsing, &i, &is_cmd_or_prog);
		else if (is_cmd_or_prog == 0 && !ft_strncmp(words[i], "./", 2))
			ft_prog(words, parsing, &i, &is_cmd_or_prog);
		else if (is_cmd_or_prog == 0 && ft_strncmp(words[i], "|", 1))
			ft_command_or_builtin(words, parsing, &i, &is_cmd_or_prog);
		else if (!ft_strcmp(words[i], "|"))
		{
			ft_pipe(words, parsing, &i);
			return ;
		}
		else
			ft_arg(words, parsing, &i);
		i++;
	}
}

void	custom_del(void *content)
{
	t_pars	*element;

	element = (t_pars *)content;
	free(element->cmd);
	free(element->arg);
	free(element->name);
	free(element->location);
	free(element);
}

void	ft_parsclear(t_pars *pars, void (*del)(void*))
{
	t_pars	*tmp;

	if (!pars)
		return ;
	if (pars && del)
	{
		while (pars)
		{
			tmp = (pars)->next;
			del(pars);
			pars = tmp;
		}
		pars = NULL;
	}
}
