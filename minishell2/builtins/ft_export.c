/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sepi <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 14:07:42 by mde-sepi          #+#    #+#             */
/*   Updated: 2022/09/14 14:17:44 by mde-sepi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../minishell.h"

void	write_down(char *temp, char *min)
{
	char	*prnt;

	prnt = bfr_aftr_eq(temp, 0, ft_strlen(temp));
	write(1, "Declare -x ", 11);
	write(1, prnt, ft_strlen(prnt));
	free (prnt);
	prnt = bfr_aftr_eq(temp, 1, ft_strlen(temp));
	write(1, "=\"", 2);
	write(1, prnt, ft_strlen(prnt));
	write(1, "\"\n", 2);
	ft_strcpy(min, temp);
}

void	print_export(char **table)
{
	char	*min;
	char	*temp;
	int		len;
	int		j;

	len = -1;
	while (table[++len])
		j = max(j, ft_strlen(table[len]));
	min = ft_calloc((j + 1), sizeof(char));
	temp = ft_calloc((j + 1), sizeof(char));
	ft_strcpy(min, " ");
	while (len-- > 0)
	{
		j = 0;
		ft_strcpy(temp, "~~~~~");
		while (table[j])
		{
			if (ft_strcmp(table[j], min) > 0 && ft_strcmp(table[j], temp) < 0)
				ft_strcpy(temp, table[j]);
			j++;
		}
		write_down(temp, min);
	}
	free(min);
	free(temp);
}

void	print_invalid(char *str)
{
	write(1, "minishell: export: '", 20);
	write(1, str, ft_strlen(str));
	write(1, "' : not a valid identifier\n", 27);
}

int	check_ok(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[++i])
	{
		j = -1;
		if (argv[i][0] == '=')
		{
			print_invalid(argv[i]);
			return (0);
		}
		while (argv[i][++j] && argv[i][j] != '=')
		{
			if (argv[i][j] == '-')
			{
				print_invalid(argv[i]);
				return (0);
			}
		}
		if (argv[i][j] == '\0' || (argv[i][j] == '=' && argv[i][j + 1] == '\0'))
			return (0);
	}
	return (1);
}

void	export(char ***env_table, char **argv)
{
	int	argc;

	argc = 0;
	while (argv[argc])
		argc++;
	if (argc == 1)
		print_export(*env_table);
	else
	{	
		if (check_ok(argv))
		{
			unset(env_table, argv);
			*env_table = append_lines(*env_table, argv, argc - 1);
		}
	}
}
