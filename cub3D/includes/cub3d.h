/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 10:44:13 by lray              #+#    #+#             */
/*   Updated: 2024/01/13 17:06:20 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define DISPLAY_WIDTH 800
# define DISPLAY_HEIGHT 600

# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include "../minilibx/linux/mlx.h"

#include "structures.h"
#include "mlx_utils.h"
#include "colors.h"
#include "events.h"
#include "ctx.h"
#include "win.h"
#include "gameloop.h"
#include "player.h"
#include "ray.h"
#include "parsing.h"
#include "move.h"


typedef struct s_mlx_data
{
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}			t_mlx_data;

#endif
