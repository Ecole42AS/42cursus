/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lray <lray@student.42lausanne.ch >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 16:23:00 by lray              #+#    #+#             */
/*   Updated: 2024/01/09 23:23:19 by lray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_image	*img_create(void *mlx, int width, int height)
{
	t_image	*img;

	img = malloc(sizeof(t_image));
	if (!img)
	{
		ft_putstr_fd("Malloc failed\n", 2);
		return (NULL);
	}
	img->data = mlx_new_image(mlx, width, height);
	if (!img->data)
	{
		ft_putstr_fd("Loading image failed\n", 2);
		return (NULL);
	}
	img->addr = mlx_get_data_addr(img->data, &img->bpp, \
		&img->line_len, &img->endian);
	if (!img->addr)
	{
		ft_putstr_fd("Cannont get images informations\n", 2);
		return (NULL);
	}
	img->width = width;
	img->height = height;
	return (img);
}
