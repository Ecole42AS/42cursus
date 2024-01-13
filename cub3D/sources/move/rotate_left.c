/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_left.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lray <lray@student.42lausanne.ch >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:09:54 by lray              #+#    #+#             */
/*   Updated: 2024/01/09 11:12:38 by lray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	rotate_left(t_ctx *ctx)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = ctx->player.dir.x;
	old_plane_x = ctx->player.cam.x;
	ctx->player.dir.x = ctx->player.dir.x * cos(ROT_SPEED) - \
		ctx->player.dir.y * sin(ROT_SPEED);
	ctx->player.dir.y = old_dir_x * sin(ROT_SPEED) + \
		ctx->player.dir.y * cos(ROT_SPEED);
	ctx->player.cam.x = ctx->player.cam.x * cos(ROT_SPEED) - \
		ctx->player.cam.y * sin(ROT_SPEED);
	ctx->player.cam.y = old_plane_x * sin(ROT_SPEED) + \
		ctx->player.cam.y * cos(ROT_SPEED);
}
