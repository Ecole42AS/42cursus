/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 07:41:19 by astutz            #+#    #+#             */
/*   Updated: 2023/10/04 14:50:14 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_pars *token)
{
	int	pid;

	if (!token->arg || (ft_isnumeric(token->arg) && is_sp(token->arg) == 0))
	{
		if (token->arg)
			g_exit_code = ft_atoi(token->arg) % 256;
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		pid = fork();
		if (pid == 0)
			remove_heredoc();
		free(token->arg);
		rl_clear_history();
		exit(g_exit_code);
	}
	else if (ft_strnstr(token->arg, "\\", ft_strlen(token->arg)) != NULL)
	{
		ft_putstr_fd("exit\nexit: too many arguments\n", STDERR_FILENO);
		g_exit_code = 1;
	}
	else if (ft_isnumeric(token->arg) == 0)
	{
		exit_msg(token);
		exit (255);
	}
}

void	exit_msg(t_pars *token)
{
	ft_putstr_fd("exit\nminishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(token->arg, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	free(token->arg);
	rl_clear_history();
}

int	ft_isnumeric(char *arg)
{
	int	i;

	i = -1;
	while (arg[++i])
		if (ft_isdigit(arg[i]) == 0)
			return (0);
	return (1);
}

char	*get_first_arg(char *arg, t_pars *token)
{
	int	i;
	int	start;
	int	end;

	i = 0;
	start = i;
	while (ft_is_space(arg[i]) != 1)
		i++;
	end = i;
	arg = ft_substr(token->arg, start, end - start);
	return (arg);
}

int	is_sp(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (ft_is_space(str[i]) == 1)
			return (1);
	}
	return (0);
}
