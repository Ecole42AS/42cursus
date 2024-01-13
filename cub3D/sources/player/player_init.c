/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lray <lray@student.42lausanne.ch >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 00:03:00 by lray              #+#    #+#             */
/*   Updated: 2024/01/09 23:13:33 by lray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	player_init(t_player *player, t_vec pos, t_vec dir, t_vec cam)
{
	player->pos.x = pos.x;
	player->pos.y = pos.y;
	player->dir.x = dir.x;
	player->dir.y = dir.y;
	player->cam.x = cam.x;
	player->cam.y = cam.y;
}
