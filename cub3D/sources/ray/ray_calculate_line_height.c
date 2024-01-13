/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_calculate_line_height.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lray <lray@student.42lausanne.ch >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 22:45:55 by lray              #+#    #+#             */
/*   Updated: 2024/01/09 22:47:36 by lray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ray_calculate_line_height(t_ctx *ctx, t_ray *ray)
{
	ray->line_height = (int)(ctx->win.height / ray->perp_wall_dist);
}
