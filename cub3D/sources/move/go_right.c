/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_right.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lray <lray@student.42lausanne.ch >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:08:45 by lray              #+#    #+#             */
/*   Updated: 2024/01/10 15:31:34 by lray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	go_right(t_ctx *ctx)
{
	double	new_x;
	double	new_y;

	new_x = ctx->player.pos.x + ctx->player.dir.y * MOVE_SPEED;
	new_y = ctx->player.pos.y - ctx->player.dir.x * MOVE_SPEED;
	if (move_is_valide(ctx, new_x, new_y))
	{
		ctx->player.pos.x = new_x;
		ctx->player.pos.y = new_y;
	}
}
