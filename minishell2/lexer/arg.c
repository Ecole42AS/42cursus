/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:12:50 by astutz            #+#    #+#             */
/*   Updated: 2023/10/06 11:01:57 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_prog(char **words, t_pars *parsing, int *i, int *is_cmd_or_prog)
{
	parsing->cmd = ft_malloc_failed_msg(ft_strlen(words[*i] + 2) + 1,
			sizeof(char));
	ft_strcpy(parsing->cmd, words[*i] + 2);
	parsing->type = 'P';
	*is_cmd_or_prog = 1;
	*i += 1;
}

void	ft_command_or_builtin(char **words, t_pars *parsing, int *i,
			int *is_cmd_or_prog)
{
	int			j;
	const char	*builtins[]
		= {"echo", "cd", "pwd", "export", "unset", "env", "exit"};

	j = -1;
	parsing->cmd = ft_malloc_failed_msg(ft_strlen(words[*i]) + 1, sizeof(char));
	ft_strcpy(parsing->cmd, words[*i]);
	*is_cmd_or_prog = 1;
	while (++j < 7)
	{
		if (!ft_strcmp(words[*i], builtins[j]))
		{
			parsing->type = 'B';
			break ;
		}
		else
			parsing->type = 'C';
	}
}

void	ft_pipe(char **words, t_pars *parsing, int *i)
{
	t_pars	*new_node;

	*i += 1;
	new_node = (t_pars *)ft_malloc_failed_msg(1, sizeof(t_pars));
	parsing->next = new_node;
	initialize_parsing(parsing->next, parsing->env_table);
	parser(words + *i, new_node);
	return ;
}

void	ft_arg(char **words, t_pars *parsing, int *i)
{
	char	*tmp;

	if (parsing->arg)
	{
		tmp = ft_malloc_failed_msg(ft_strlen(parsing->arg) + 1, sizeof(char));
		ft_strlcpy(tmp, parsing->arg, ft_strlen(parsing->arg) + 1);
		free(parsing->arg);
		parsing->arg = ft_malloc_failed_msg(ft_strlen(tmp)
				+ ft_strlen(words[*i]) + 2, sizeof(char));
		ft_strlcat(parsing->arg, tmp, ft_strlen(tmp) + 1);
		free(tmp);
		ft_strlcat(parsing->arg, "\\", 2 + ft_strlen(parsing->arg));
		ft_strlcat(parsing->arg, words[*i],
			ft_strlen(words[*i]) + ft_strlen(parsing->arg) + 1);
	}
	else
	{
		parsing->arg = ft_strdup(words[*i]);
		if (!parsing->arg)
		{
			perror("Memory allocation failure");
			exit(1);
		}
	}
}
