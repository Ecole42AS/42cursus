/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 14:07:42 by mde-sepi          #+#    #+#             */
/*   Updated: 2023/10/02 17:42:46 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_pwd(char **env_table)
{
	int		i;
	char	*old_pwd;
	char	s[200];
	char	*str;

	i = 0;
	while (env_table[i])
	{
		if (!ft_strncmp(env_table[i], "PWD=", 4))
		{
			old_pwd = malloc(ft_strlen(env_table[i]) + 1);
			str = bfr_aftr_eq(env_table[i], 1, ft_strlen(env_table[i]));
			ft_strcpy(old_pwd, str);
			ft_strcpy(&env_table[i][4], getcwd(s, 100));
		}
		i++;
	}
	i = 0;
	while (env_table[i])
	{
		if (!ft_strncmp(env_table[i], "OLDPWD=", 7))
			ft_strcpy(&env_table[i][7], old_pwd);
		i++;
	}
	free (old_pwd);
}

int	cd(t_pars *block, char **args)
{
	if (args[1] == NULL)
		chdir(getenv("HOME"));
	else if (chdir(args[1]) != 0)
	{
		write(1, "minishell: cd: ", 15);
		write(1, args[1], ft_strlen(args[1]));
		write(1, ": No such file or directory\n", 29);
		return (0);
	}
	change_pwd(*block->env_table);
	return (1);
}
