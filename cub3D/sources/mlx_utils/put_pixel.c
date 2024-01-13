/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lray <lray@student.42lausanne.ch >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 16:06:52 by lray              #+#    #+#             */
/*   Updated: 2024/01/09 23:19:44 by lray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	put_pixel(t_image *img, int x, int y, int color)
{
	char	*dst;

	if (!img || !img->addr)
	{
		ft_putstr_fd("Image is NULL\n", 2);
		return (1);
	}
	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
	{
		ft_putstr_fd("Coordinates are out of bounds\n", 2);
		return (2);
	}
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
	return (0);
}
