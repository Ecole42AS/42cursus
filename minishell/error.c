/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:05:39 by astutz            #+#    #+#             */
/*   Updated: 2023/10/06 08:38:18 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_malloc_failed_msg(int size, size_t type)
{
	void	*ptr;

	ptr = ft_calloc(size + 1, type);
	if (!ptr)
	{
		perror("Memory allocation failure");
		exit(g_exit_code);
	}
	return (ptr);
}

void	set_after_pipe(int i, int *j, char *after_pipe);

int	if_pipe(size_t *i, char *input, int input_length, char *after_pipe)
{
	size_t	j;

	*i += 1;
	j = 0;
	while (input[*i] && input[*i] != '|')
	{
		if (j < input_length - *i)
		{
			after_pipe[j] = input[*i];
			j++;
		}
		*i += 1;
	}
	if (j < input_length - *i || input[*i] == '|')
		after_pipe[j] = '\0';
	if (input[*i] == '|')
		i++;
	free(after_pipe);
	if (ft_is_only_space(after_pipe))
	{	
		write(2, "syntax error near unexpected token '|'\n", 40);
		display_line(input);
		return (1);
	}
	return (0);
}

int	check_pipes_error(char *input)
{
	size_t	i;
	size_t	input_length;
	char	*after_pipe;

	i = 0;
	input_length = ft_strlen(input) + 1;
	while (input[i])
	{
		if ((input[i] == '|' && input[i + 1] == '|') || input[0] == '|')
		{
			write(2, "syntax error near unexpected token '|'\n", 40);
			display_line(input);
			return (1);
		}
		if (input[i] == '|')
		{
			after_pipe = ft_malloc_failed_msg(input_length - i, sizeof(char));
			if (if_pipe(&i, input, input_length, after_pipe))
				return (1);
		}
		else
			i++;
	}
	return (0);
}
