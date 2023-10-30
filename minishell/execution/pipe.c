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

int	first_set(t_pars *block, int fd[2])
{
	pid_t	pid;

	if (use_pipe(block))
	{
		pid = fork();
		if (pid == 0)
			first_gen(block, fd);
	}
	return (0);
}

t_pars	*mid_set(t_pars *block, int fd[2], int fx[2], int snd)
{
	pid_t	pid;

	if (snd == 0)
	{
		close(fd[1]);
		if (use_pipe(block))
		{
			pid = fork();
			if (pid == 0)
				mid_gen(block, fd, fx);
		}
		close(fd[0]);
	}
	if (snd == 1)
	{
		close(fx[1]);
		if (use_pipe(block))
		{
			pid = fork();
			if (pid == 0)
				mid_gen(block, fx, fd);
		}
		close(fx[0]);
	}
	return (block->next);
}

void	last_set(t_pars *block, int fd[2], int fx[2], int loop)
{
	pid_t	pid;

	close(fd[1]);
	if (fx[1])
		close(fx[1]);
	if (use_pipe(block))
	{
		pid = fork();
		if (pid == 0)
		{
			if (loop == 1)
				last_gen(block, fx);
			else
				last_gen(block, fd);
		}
	}
	close(fd[0]);
	if (fx[0])
		close(fx[0]);
}

int	next_block(t_pars **block)
{
	if ((*block)->next)
	{
		*block = (*block)->next;
		return (1);
	}
	return (0);
}

void	pipes(t_pars *block)
{
	int		fd[2];
	int		fx[2];
	int		loop;

	pipe(fd);
	loop = first_set(block, fd);
	if (next_block(&block))
	{
		while (block->next != NULL)
		{
			pipe(fx);
			block = mid_set(block, fd, fx, 0);
			loop = 1;
			if (block->next == NULL)
				break ;
			pipe(fd);
			block = mid_set(block, fd, fx, 1);
			loop = 0;
		}
		last_set(block, fd, fx, loop);
	}
	waiting();
}
