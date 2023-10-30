/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creator.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 14:07:42 by mde-sepi          #+#    #+#             */
/*   Updated: 2023/09/28 11:22:08 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	commander(t_pars *block)
{
	int		fd[2];
	pid_t	pid;

	if (block->type == 'C')
	{
		block->name = extract_prg_name(block->cmd);
		pipe(fd);
		pid = fork();
		if (pid == 0)
			extract_cmd_location(fd, block->name);
		close(fd[1]);
		block->location = get_next_line(fd[0]);
		close(fd[0]);
	}
	if (block->type == 'P')
	{
		block->location = block->cmd;
		block->name = extract_prg_name(block->cmd);
	}
	if (block->type == 'B')
	{
		block->name = extract_prg_name(block->cmd);
		block->location = extract_built_location(block->name);
	}
}

char	**argumenter(t_pars *block)
{
	char	**args;
	char	*temp1;
	char	*temp2;

	if (block->name)
	{
		if (block->arg != NULL)
		{
			temp1 = append_str("\\", block->arg);
			temp2 = append_str(block->name, temp1);
			free(temp1);
			args = ft_split(temp2, '\\');
			free(temp2);
		}
		else
			args = ft_split(block->name, '\\');
		return (args);
	}
	return (NULL);
}

void	ft_strcpy(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str2[i])
	{
		str1[i] = str2[i];
		i++;
	}
	str1[i] = '\0';
}

char	**append_lines(char **table, char **str, int n)
{
	char	**ret;
	int		len;
	int		i;

	ret = new_matrix(table, n);
	i = 0;
	while (table[i])
	{
		ft_strcpy(ret[i], table[i]);
		free(table[i]);
		i++;
	}
	len = 1;
	while (str[len])
	{
		ft_strcpy(ret[i + len - 1], str[len]);
		len++;
	}
	free(ret[len + i - 1]);
	ret[len + i - 1] = NULL;
	free(table);
	return (ret);
}

int	block_type_b(t_pars *block)
{
	char	**args;
	int		i;

	if ((!ft_strcmp(block->name, "export") && !block->arg)
		|| !ft_strcmp(block->name, "env") || !ft_strcmp(block->name, "pwd")
		|| ft_strcmp(block->name, "echo") == 0)
		return (1);
	args = argumenter(block);
	if (ft_strcmp(block->name, "export") == 0 && block->arg)
		export(block->env_table, args);
	else if (ft_strcmp(block->name, "cd") == 0)
		cd(block, args);
	else if (ft_strcmp(block->name, "unset") == 0)
		unset(block->env_table, args);
	i = -1;
	while (args[++i])
		free(args[i]);
	free (args);
	return (0);
}

/*int     invent_cat(t_pars *block)
{
	if (block->type != 0)
		return (0);
	if (block->infile != STDIN_FILENO && block->outfile != STDOUT_FILENO)
		return (1);
	if (block->infile != STDIN_FILENO && block->next != NULL)
		return (1);
	if (block->id != 1 && block->outfile != STDOUT_FILENO)
		return (1);
	return (0);
}

if (invent_cat(block)) TO COPY ZSH FILIN FILOUT NO COMMAND
{
	cat = malloc(4 * sizeof(char));
	ft_strcpy(cat, "cat", 4);
	block->cmd = cat;
	block->type = 'C';
	return (1);
}*/
