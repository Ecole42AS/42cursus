/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_calculate_draw_points.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lray <lray@student.42lausanne.ch >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 22:49:34 by lray              #+#    #+#             */
/*   Updated: 2024/01/09 22:51:45 by lray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ray_calculate_draw_points(t_ctx *ctx, t_ray *ray)
{
	ray->draw_point[0] = -ray->line_height / 2 + ctx->win.height / 2;
	if (ray->draw_point[0] < 0)
		ray->draw_point[0] = 0;
	ray->draw_point[1] = ray->line_height / 2 + ctx->win.height / 2;
	if (ray->draw_point[1] >= ctx->win.height)
		ray->draw_point[1] = ctx->win.height - 1;
}
