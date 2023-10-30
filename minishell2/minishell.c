/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 10:16:35 by astutz            #+#    #+#             */
/*   Updated: 2023/10/03 10:24:17 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code = 0;

int	words(char *input, t_pars *parsing)
{
	char	**words;
	int		i;

	words = lexer(input, parsing);
	if (words)
	{
		parser(words, parsing);
		i = 0;
		while (words[i])
		{
			free(words[i]);
			i++;
		}
		free(words);
		return (0);
	}
	return (1);
}

void	test_exit(t_pars *parsing)
{
	if (parsing->cmd)
	{
		if (!ft_strncmp(parsing->cmd, "exit", 5))
			ft_exit(parsing);
	}
}

int	test_input(char *input, t_pars *parsing)
{
	if (((input && input[0] == '\0') || input == NULL)
		|| ft_is_only_space(input) == 1)
	{
		free(input);
		ft_parsclear(parsing, custom_del);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	char	***env_table;
	t_pars	*parsing;

	input = argv[argc - 1];
	init_termios();
	env_table = malloc(2 * sizeof(char **));
	*env_table = init_env(env);
	while (input)
	{
		parsing = (t_pars *)ft_malloc_failed_msg(1, sizeof(t_pars));
		signals_init(signals_handle_input);
		input = readline("\x1B[38;5;82mminishell$\x1B[0m ");
		signals_init(signals_handle_execution);
		if (test_input(input, parsing))
			continue ;
		initialize_parsing(parsing, env_table);
		words(input, parsing);
		test_exit(parsing);
		add_history(input);
		pipes(parsing);
		free(input);
		ft_parsclear(parsing, custom_del);
	}
}
