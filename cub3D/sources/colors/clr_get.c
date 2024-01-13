/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clr_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lray <lray@student.42lausanne.ch >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 02:07:46 by lray              #+#    #+#             */
/*   Updated: 2024/01/09 23:07:05 by lray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

unsigned char	clr_get_t(int trgb)
{
	return (((unsigned int *)&trgb)[3]);
}

unsigned char	clr_get_r(int trgb)
{
	return (((unsigned int *)&trgb)[2]);
}

unsigned char	clr_get_g(int trgb)
{
	return (((unsigned int *)&trgb)[1]);
}

unsigned char	clr_get_b(int trgb)
{
	return (((unsigned int *)&trgb)[0]);
}
