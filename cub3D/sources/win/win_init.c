/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lray <lray@student.42lausanne.ch >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 01:34:14 by lray              #+#    #+#             */
/*   Updated: 2023/12/30 02:11:20 by lray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	win_init(t_win *win, t_win_params params)
{
	win->mlx = params.mlx;
	win->width = params.width;
	win->height = params.height;
	win->name = params.name;
	win->win = mlx_new_window(win->mlx, win->width, win->height, win->name);
}
