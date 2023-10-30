/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 16:07:40 by astutz            #+#    #+#             */
/*   Updated: 2023/10/05 14:55:57 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	trailing_spaces(char *input)
{
	int	input_length;

	input_length = ft_strlen(input);
	while (input_length > 0 && (input[input_length - 1] == ' '
			|| input[input_length - 1] == '\t'))
	{
		input[input_length - 1] = '\0';
		input_length--;
	}
}

char	*set_word(char *input, t_ends ends, t_pars *parsing)
{
	char	*word;
	char	*temp;

	word = ft_substr(input, ends.start, ends.end - ends.start);
	if ((ft_strnstr(word, "$", ft_strlen(word) + 1) != NULL
			&& !ends.in_squotes))
	{
		temp = word;
		word = replace_env_var(temp, parsing);
		free(temp);
	}
	return (word);
}

void	set_ends(t_ends *ends, int *i, char *input)
{
	ends->start = *i;
	while (!ft_is_space(input[*i]) && input[*i] && input[*i] != '\''
		&& input[*i] != '\"')
		*i += 1;
	ends->end = *i;
}

int	loop(t_ends *ends, int *i, char *input)
{
	ends->in_squotes = 0;
	while (ft_is_space(input[*i]) == 1 && input[*i])
		*i += 1;
	if ((input[*i] == '\'' || input[*i] == '\"'))
	{
		if (quotes(input, i, ends, input[*i]))
			return (1);
	}
	else
		set_ends(ends, i, input);
	return (0);
}

char	**lexer(char *input, t_pars *parsing)
{
	char	**word;
	int		i;
	int		j;
	t_ends	ends;

	i = 0;
	j = -1;
	ends.end = 0;
	if (check_pipes_error(input) == 1)
		return (NULL);
	trailing_spaces(input);
	word = (char **)ft_malloc_failed_msg(ft_strlen(input) + 1, sizeof(char *));
	while (input[i])
	{
		if (loop(&ends, &i, input))
			return (NULL);
		if (!ends.in_squotes || ends.end > ends.start)
			word[++j] = set_word(input, ends, parsing);
	}
	word[++j] = NULL;
	return (word);
}
