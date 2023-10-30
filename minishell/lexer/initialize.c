/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 18:53:05 by astutz            #+#    #+#             */
/*   Updated: 2023/10/02 14:11:32 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	initialize_parsing(t_pars *my_pars, char ***env_table)
{
	if (my_pars != NULL)
	{
		my_pars->infile = STDIN_FILENO;
		my_pars->outfile = STDOUT_FILENO;
		my_pars->cmd = NULL;
		my_pars->type = 0;
		my_pars->arg = NULL;
		my_pars->name = NULL;
		my_pars->location = NULL;
		my_pars->env_table = env_table;
		my_pars->next = NULL;
	}
}
/*void initialize_squote
(t_single_quote_list *squote, t_single_quote_list *head)
{
	if (squote != NULL)
	{
		squote->single_quote_content = NULL;
		squote->head = head;
		squote->next = NULL;
	}
}*/ 