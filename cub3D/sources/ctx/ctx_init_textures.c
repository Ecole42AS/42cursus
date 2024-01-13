/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx_init_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lray <lray@student.42lausanne.ch >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 04:21:34 by lray              #+#    #+#             */
/*   Updated: 2024/01/09 23:17:15 by lray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	make_background(t_ctx *ctx, unsigned int c1, unsigned int c2);

int	ctx_init_textures(t_ctx *ctx, unsigned int colors[2], char **tex_path)
{
	int	i;

	ctx->textures[0] = img_create(ctx->mlx, ctx->win.width, ctx->win.height);
	make_background(ctx, colors[0], colors[1]);
	i = 1;
	while (i <= 4)
	{
		ctx->textures[i] = img_load(ctx->mlx, tex_path[i - 1]);
		if (!ctx->textures[i])
			return (i);
		++i;
	}
	return (0);
}

static void	make_background(t_ctx *ctx, unsigned int c1, unsigned int c2)
{
	int	x;
	int	y;

	y = 0;
	while (y < ctx->win.height)
	{
		x = 0;
		while (x < ctx->win.width)
		{
			if (y < ctx->win.height / 2)
				put_pixel(ctx->textures[0], x, y, c1);
			else
				put_pixel(ctx->textures[0], x, y, c2);
			++x;
		}
		++y;
	}
}
