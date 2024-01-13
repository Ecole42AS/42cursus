/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_calculate_wall_x.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lray <lray@student.42lausanne.ch >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 22:54:37 by lray              #+#    #+#             */
/*   Updated: 2024/01/09 22:57:20 by lray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ray_calculate_wall_x(t_ctx *ctx, t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_x = ctx->player.pos.y + ray->perp_wall_dist * ray->dir.y;
	else
		ray->wall_x = ctx->player.pos.x + ray->perp_wall_dist * ray->dir.x;
	ray->wall_x -= floor(ray->wall_x);
}
