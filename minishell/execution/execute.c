/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sepi <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 14:07:42 by mde-sepi          #+#    #+#             */
/*   Updated: 2022/09/14 14:17:44 by mde-sepi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	use_pipe(t_pars *block)
{
	int		len;

	len = -1;
	if (block->type == 'C' || block->type == 'P')
		return (1);
	if (block->type == 'B')
	{
		commander(block);
		if (block_type_b(block))
			return (1);
		if (block->infile != STDIN_FILENO)
			close (block->infile);
		if (block->outfile != STDOUT_FILENO)
			close (block->outfile);
	}
	return (0);
}

char	*append_str(char *str1, char *str2)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	ret = ft_calloc(ft_strlen(str1) + ft_strlen(str2) + 1, sizeof(char));
	while (str1[i])
	{
		ret[i] = str1[i];
		i++;
	}
	j = i;
	i = 0;
	while (str2[i])
	{
		ret[i + j] = str2[i];
		i++;
	}
	return (ret);
}

//exacts the location of a given actualy builtin command
void	extract_cmd_location(int fd[2], char *name)
{
	char	*arg[3];
	int		temp;

	arg[0] = "whereis";
	arg[1] = name;
	arg[2] = NULL;
	temp = dup(STDIN_FILENO);
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	execve("/usr/bin/whereis", arg, NULL);
	write(temp, "minishell: ", 11);
	write(temp, name, ft_strlen(name));
	write(temp, ": command not found\n", 20);
	g_exit_code = 127;
	if (errno)
		g_exit_code = errno;
	exit (g_exit_code);
}

//exacts the name of the file from the given location
char	*extract_prg_name(char *location)
{
	char	*name;
	char	*temp;
	int		i;

	temp = location;
	i = 0;
	while (location[i])
	{
		if (location[i] == '/')
			temp = location + i + 1;
		i++;
	}
	name = malloc(ft_strlen(temp) + 1);
	ft_strcpy(name, temp);
	return (name);
}

char	*extract_built_location(char *name)
{
	char	s[100];
	char	*location;
	char	*loc2;

	ft_strcpy(s, getenv("PWD"));
	location = append_str(s, "/builtins/");
	loc2 = append_str(location, name);
	free(location);
	return (loc2);
}
