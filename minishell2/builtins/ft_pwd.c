/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sepi <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 14:07:42 by mde-sepi          #+#    #+#             */
/*   Updated: 2022/09/14 14:17:44 by mde-sepi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "../minishell.h"

void	pwd( void )
{
	char	s[100];

	getcwd(s, 100);
	write(1, s, ft_strlen(s));
	write(1, "\n", 1);
}
