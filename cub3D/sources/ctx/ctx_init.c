/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lray <lray@student.42lausanne.ch >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 23:51:50 by lray              #+#    #+#             */
/*   Updated: 2024/01/09 23:15:36 by lray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ctx_init(t_ctx *ctx, int width, int height, char *name)
{
	t_win_params	params;

	ctx->mlx = mlx_init();
	params.mlx = ctx->mlx;
	params.width = width;
	params.height = height;
	params.name = name;
	win_init(&ctx->win, params);
}
