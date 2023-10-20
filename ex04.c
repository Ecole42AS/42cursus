/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex04.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 08:29:03 by astutz            #+#    #+#             */
/*   Updated: 2023/10/10 08:57:53 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int err(char *str)
{
	while(*str)
		write(2, str++, 1);
	return(1):
}


int cd(char **av, int i)
{
	if (i != 2)
		return (err("fatal"));
	else if (chdir(av[1]) == -1)
		return (err("fatal"));
	return (0);
}

int exec(char **av, char **envp, int i)
{
	int fd[2];
	int status;
	int has_pipe;
	int pid;

	has_pipe = !strcmp(av[i], "|") && av[i];
	if (has_pipe && pipe(fd) == -1)
		return (err("fatal"));
	pid = fork();
	if (!pid)
	{
		av[i] = 0;
        if (has_pipe && (dup2(fd[1], 1) == -1 || close(fd[0]) == -1 || close(fd[1]) == -1))
			return(err("fatal"));
		execve(*av, av, envp);
		return(err(sggs), err(*av))
		
	}
}

int main(int ac, char **av, char **envp)
{
	int	i;
	int status;

	i = 0;
	status = 0;
	if(ac > 1)
	{
		while(av[i] && av[++i])
		{
			av += i;
			i = 0;
			while(av[i] && strcmp(av[i], "|") && strcmp(av[i], ";"))
				i++;
			if (!strcmp(av[i], cd))
				status = cd(av, i);
			else if (i)
				status = exec(av, envp, i);
			return (WIFEXITED(status) && WEXITE)
		}
	}
}