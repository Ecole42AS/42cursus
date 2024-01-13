/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lray <lray@student.42lausanne.ch >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 20:49:26 by lray              #+#    #+#             */
/*   Updated: 2024/01/09 11:11:45 by lray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	key_handler(int keycode, void *param)
{
	t_ctx	*ctx;

	ctx = param;
	if (keycode == KEY_ESC)
	{
		ctx_free(ctx);
		exit (0);
	}
	else if (keycode == KEY_W || keycode == KEY_UP)
		go_front(ctx);
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		go_back(ctx);
	else if (keycode == KEY_A)
		go_left(ctx);
	else if (keycode == KEY_D)
		go_right(ctx);
	else if (keycode == KEY_LEFT)
		rotate_left(ctx);
	else if (keycode == KEY_RIGHT)
		rotate_right(ctx);
	return (0);
}
