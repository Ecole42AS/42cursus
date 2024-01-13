/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lray <lray@student.42lausanne.ch >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 00:37:38 by lray              #+#    #+#             */
/*   Updated: 2024/01/09 22:36:18 by lray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	set_delta_dist(t_ray *ray);
static void	set_step_and_side_dist(t_ctx *ctx, t_ray *ray);

void	ray_init(t_ctx *ctx, t_ray *ray, int x)
{
	ray->camera_x = 2 * x / (double)ctx->win.width - 1;
	ray->dir.x = ctx->player.dir.x + ctx->player.cam.x * ray->camera_x;
	ray->dir.y = ctx->player.dir.y + ctx->player.cam.y * ray->camera_x;
	ray->map.x = (int)ctx->player.pos.x;
	ray->map.y = (int)ctx->player.pos.y;
	ray->side_dist.x = 0;
	ray->side_dist.y = 0;
	ray->perp_wall_dist = 0;
	ray->step.x = 0;
	ray->step.y = 0;
	ray->hit = 0;
	ray->side = 0;
	ray->draw_point[0] = 0;
	ray->draw_point[1] = 0;
	ray->line_height = 0;
	ray->wall_x = 0;
	set_delta_dist(ray);
	set_step_and_side_dist(ctx, ray);
}

static void	set_delta_dist(t_ray *ray)
{
	if (ray->dir.x == 0)
		ray->delta_dist.x = 1e30;
	else
		ray->delta_dist.x = fabs(1 / ray->dir.x);
	if (ray->dir.y == 0)
		ray->delta_dist.y = 1e30;
	else
		ray->delta_dist.y = fabs(1 / ray->dir.y);
}

static void	set_step_and_side_dist(t_ctx *ctx, t_ray *ray)
{
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (ctx->player.pos.x - ray->map.x) * ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (ray->map.x + 1.0 - ctx->player.pos.x) * \
		ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (ctx->player.pos.y - ray->map.y) * ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (ray->map.y + 1.0 - ctx->player.pos.y) * \
		ray->delta_dist.y;
	}
}
