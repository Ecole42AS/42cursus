/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_var_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:48:32 by astutz            #+#    #+#             */
/*   Updated: 2023/10/09 09:29:01 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*replace_exit_code(char *result, int *i, int *new_len)
{
	int		start;
	int		end;
	char	*exit_code_str;
	char	*new_result;

	start = *i + 1;
	end = *i + 2;
	exit_code_str = ft_itoa(g_exit_code % 256);
	*new_len = ft_strlen(result) + ft_strlen(exit_code_str) - (end - start) + 1;
	new_result = (char *)
		ft_malloc_failed_msg(*new_len, sizeof(char));
	ft_strlcpy(new_result, result, start);
	ft_strlcat(new_result, exit_code_str,
		ft_strlen(new_result) + ft_strlen(exit_code_str) + 1);
	if (result[end] != '\0')
	{
		ft_strlcat(new_result, result + end,
			ft_strlen(result + end) + ft_strlen(new_result) + 1);
		new_result[ft_strlen(new_result)] = '\0';
	}
	free(result);
	result = new_result;
	*i = start + ft_strlen(exit_code_str) - 1;
	free(exit_code_str);
	return (result);
}

char	*replace_env_value(char *result, t_pars *parsing, int *new_len, int *i)
{
	t_ends	*len;
	char	*env_key;

	len = ft_malloc_failed_msg(1, sizeof(t_ends));
	len->start = *i + 1;
	while (result[*i + 1] != '\t' && result[*i + 1] != ' '
		&& result[*i + 1] != '\"'
		&& result[*i + 1] && result[*i + 1] != '\'')
		*i += 1;
	len->end = *i + 1;
	env_key = ft_strndup(result + len->start, len->end - len->start);
	len->env_value = ft_get_env(env_key, parsing->env_table);
	free(env_key);
	if (len->env_value)
		result = replace_env_value_bis(result, new_len, i, len);
	free(len);
	return (result);
}

char	*replace_env_value_bis(char *result, int *new_len, int *i, t_ends *len)
{
	char	*new_result;

	*new_len = ft_strlen(result) + ft_strlen(len->env_value)
		- (len->end - len->start) + 1;
	new_result = (char *)ft_calloc(*new_len, sizeof(char));
	if (new_result == NULL)
	{
		perror("Erreur d'allocation mémoire");
		return (result);
	}
	ft_strlcpy(new_result, result, len->start);
	ft_strlcat(new_result, len->env_value,
		ft_strlen(new_result) + ft_strlen(len->env_value) + 1);
	ft_strlcat(new_result, result + len->end,
		ft_strlen(new_result) + ft_strlen(result + len->end) + 1);
	new_result[ft_strlen(new_result)] = '\0';
	free(result);
	result = new_result;
	*i = len->start + ft_strlen(len->env_value) - 1;
	return (result);
}

void	waiting(void)
{
	int	status;

	status = 0;
	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			g_exit_code = WEXITSTATUS(status);
	}
}
