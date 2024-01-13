/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lray <lray@student.42lausanne.ch >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 04:38:33 by lray              #+#    #+#             */
/*   Updated: 2024/01/08 06:18:15 by lray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	img_free(t_ctx *ctx, t_image *img)
{
	if (img)
		mlx_destroy_image(ctx->mlx, img->data);
	free(img);
}
