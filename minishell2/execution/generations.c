/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sepi <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 14:07:42 by mde-sepi          #+#    #+#             */
/*   Updated: 2022/09/14 14:17:44 by mde-sepi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_fail_or_dup(t_pars *block, int temp, int err, char **args)
{
	int	i;

	i = 0;
	if (temp != 0)
	{
		while (args[i])
		{
			free(args[i]);
			i++;
		}
		free(args);
		write(temp, "minishell: ", 11);
		write(temp, block->name, ft_strlen(block->name));
		write(temp, ": command not found\n", 20);
		exit (err);
	}
	else
	{
		if (block->outfile != STDOUT_FILENO)
			dup2(block->outfile, STDOUT_FILENO);
		if (block->infile != STDIN_FILENO)
			dup2(block->infile, STDIN_FILENO);
	}
}

void	exec_builtins(t_pars *block, char **args)
{
	int	i;

	if (ft_strcmp(block->name, "export") == 0)
		export(block->env_table, args);
	else if (ft_strcmp(block->name, "echo") == 0)
		echo(args);
	else if (ft_strcmp(block->name, "env") == 0)
		env(block->env_table[0]);
	else if (ft_strcmp(block->name, "pwd") == 0)
		pwd();
	if (block->infile != STDIN_FILENO)
		close(block->infile);
	if (block->outfile != STDOUT_FILENO)
		close(block->outfile);
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	first_gen(t_pars *block, int fd[2])
{
	char	**args;
	int		temp;

	commander(block);
	args = argumenter(block);
	temp = dup(STDOUT_FILENO);
	close(fd[0]);
	exec_fail_or_dup(block, 0, 0, NULL);
	if (block->outfile == STDOUT_FILENO && block->next != NULL)
		dup2(fd[1], STDOUT_FILENO);
	if (block->type == 'B')
	{
		exec_builtins(block, args);
		close(fd[1]);
		exit(0);
	}
	execve(block->location, args, NULL);
	close(fd[1]);
	exec_fail_or_dup(block, temp, errno, args);
}

void	mid_gen(t_pars *block, int fgc[2], int fd[2])
{
	char	**args;
	int		temp;

	commander(block);
	args = argumenter(block);
	temp = dup(STDOUT_FILENO);
	close(fd[0]);
	close(fgc[1]);
	exec_fail_or_dup(block, 0, 0, NULL);
	if (block->infile == STDIN_FILENO)
		dup2(fgc[0], STDIN_FILENO);
	if (block->outfile == STDOUT_FILENO)
		dup2(fd[1], STDOUT_FILENO);
	if (block->type == 'B')
	{
		exec_builtins(block, args);
		close(fd[1]);
		close(fgc[0]);
		exit (0);
	}
	execve(block->location, args, NULL);
	close(fd[1]);
	close(fgc[0]);
	exec_fail_or_dup(block, temp, errno, args);
}

void	last_gen(t_pars *block, int fd[2])
{
	char	**args;
	int		temp;

	commander(block);
	args = argumenter(block);
	temp = dup(STDOUT_FILENO);
	close(fd[1]);
	exec_fail_or_dup(block, 0, 0, NULL);
	if (block->infile == STDIN_FILENO)
		dup2(fd[0], STDIN_FILENO);
	if (block->type == 'B')
	{
		exec_builtins(block, args);
		close(fd[0]);
		exit (0);
	}
	execve(block->location, args, NULL);
	close(fd[0]);
	exec_fail_or_dup(block, temp, errno, args);
}
