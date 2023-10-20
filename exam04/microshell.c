/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 20:55:06 by astutz            #+#    #+#             */
/*   Updated: 2023/10/09 22:23:57 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

int	err(char *str)
{
	printf("%s\n", str);
	while(*str)
		write(2, str++, 1);
	return (1);
}

int	cd(char	**av, int i)
{
	if (i != 2)
		return err("bad arguments\n");
	else if (chdir(av[1] == -1))
		return err("error: cd: cannot change directory to "), err(av[1]), err("\n");
	return (0);
}

int exec(char **av, char **envp, int i)
{
	int	fd[2];
	int	status;
	int has_pipe;
	int	pid;

	has_pipe = !strcmp(av[i], "|") && av[i];
	if (has_pipe && pipe(fd) == -1)
		return (err("problem creating pipe"));
	pid = fork();
	if (!pid)
	{
		av[i] = 0;
		if (av[i] && (dup2(fd[1], 1) == -1 || close(fd[1]) == -1 || close(fd[0]) == -1))
			return (err("fatal error"));
		execve(*av, av, envp);
		return (err("command:"), err(*av), err("\n"));
	}
	waitpid(pid, &status, 0);
	if (has_pipe && (dup2(fd[0], 0) == -1 || close(fd[0]) == -1 || close(fd[1] == -1)))
		return (err("fatal"));
	return(WIFEXITED(status) && WEXITSTATUS(status));

}

int main()
{
	if (1)
		printf("%d",);
}