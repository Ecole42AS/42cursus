/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 19:11:37 by astutz            #+#    #+#             */
/*   Updated: 2023/05/01 17:16:57 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

# include <signal.h>
# include "ft_printf/includes/ft_printf.h"
# include "ft_printf/libft/libft.h"

typedef struct s_msg
{
	int		c;
	int		i;
	char	*str;
	int		msg_received;
}	t_msg;

#endif