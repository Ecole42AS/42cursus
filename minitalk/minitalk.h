/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 20:37:24 by astutz            #+#    #+#             */
/*   Updated: 2023/04/22 10:12:02 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include "ft_printf/includes/ft_printf.h"
# include "ft_printf/libft/libft.h"

void	ft_send_str(int pid, char *str);

typedef struct s_msg
{
	int		c;
	int		i;
}	t_msg;

#endif