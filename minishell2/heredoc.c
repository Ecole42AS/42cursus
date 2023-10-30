/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 14:22:17 by astutz            #+#    #+#             */
/*   Updated: 2023/10/02 17:42:46 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_heredoc(const char *delimiter, t_pars *parsing)
{
	char	*heredoc_buffer;

	parsing->infile = open(".heredoc.txt", O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (parsing->infile == -1)
	{
		perror("Error creating heredoc file");
		return ;
	}
	while (1)
	{
		heredoc_buffer = readline("> ");
		if (heredoc_buffer == NULL)
			break ;
		if (!ft_strncmp(delimiter, heredoc_buffer, ft_strlen(delimiter) + 1))
		{
			free(heredoc_buffer);
			break ;
		}
		write(parsing->infile, heredoc_buffer, ft_strlen(heredoc_buffer));
		write(parsing->infile, "\n", 1);
		free(heredoc_buffer);
	}
	close(parsing->infile);
	parsing->infile = open(".heredoc.txt", O_CREAT | O_RDWR, 0777);
}

void	remove_heredoc(void)
{
	char	*arg[3];
	int		pid;

	pid = fork();
	if (pid == 0)
	{
		arg[0] = "rm";
		arg[1] = ".heredoc.txt";
		arg[2] = NULL;
		open(".heredoc.txt", O_CREAT | O_RDWR | O_TRUNC, 0777);
		execve("/bin/rm", arg, NULL);
		write(1, "heredock destruction failed", 11);
		g_exit_code = errno;
		exit (g_exit_code);
	}
}
