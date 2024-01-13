/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lray <lray@student.42lausanne.ch >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 17:01:13 by lray              #+#    #+#             */
/*   Updated: 2024/01/09 23:04:14 by lray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	draw_tex_verline(t_image *img, t_ray *ray, int x, t_image *texture);

t_image	*raycasting(t_ctx *ctx, t_image *frame)
{
	int		x;
	t_ray	ray;
	t_image	*texture;

	x = 0;
	while (x < ctx->win.width)
	{
		ray_init(ctx, &ray, x);
		ray_dda(ctx, &ray);
		ray_calculate_perp_wall_dist(ctx, &ray);
		ray_calculate_line_height(ctx, &ray);
		ray_calculate_draw_points(ctx, &ray);
		ray_calculate_wall_x(ctx, &ray);
		texture = ctx->textures[ray.hit];
		if (draw_tex_verline(frame, &ray, x, texture) != 0)
			return (NULL);
		++x;
	}
	return (frame);
}

static int	draw_tex_verline(t_image *img, t_ray *ray, int x, t_image *texture)
{
	int	y;
	int	tex_x;
	int	tex_y;
	int	color;
	int	d;

	tex_x = (int)(ray->wall_x * (double)texture->width);
	y = ray->draw_point[0];
	while (y < ray->draw_point[1])
	{
		d = y * 256 - img->height * 128 + ray->line_height * 128;
		tex_y = ((d * texture->height) / ray->line_height) / 256;
		color = get_pixel(texture, tex_x, tex_y);
		put_pixel(img, x, y, color);
		++y;
	}
	return (0);
}
