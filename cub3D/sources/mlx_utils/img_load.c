/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lray <lray@student.42lausanne.ch >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 05:56:38 by lray              #+#    #+#             */
/*   Updated: 2024/01/09 23:22:26 by lray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_image	*img_load(void *mlx, char *path)
{
	t_image	*new_img;

	new_img = malloc(sizeof(t_image));
	if (!new_img)
	{
		ft_putstr_fd("Malloc failed\n", 2);
		return (NULL);
	}
	new_img->data = mlx_xpm_file_to_image(mlx, path, &new_img->width, \
		&new_img->height);
	if (!new_img->data)
	{
		ft_putstr_fd("Load XPM file failed\n", 2);
		free(new_img);
		return (NULL);
	}
	new_img->addr = mlx_get_data_addr(new_img->data, &new_img->bpp, \
		&new_img->line_len, &new_img->endian);
	if (!new_img->addr)
	{
		mlx_destroy_image(mlx, new_img);
		free(new_img);
		return (NULL);
	}
	return (new_img);
}
