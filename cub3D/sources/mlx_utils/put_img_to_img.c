/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_img_to_img.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lray <lray@student.42lausanne.ch >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 16:19:15 by lray              #+#    #+#             */
/*   Updated: 2024/01/08 07:29:47 by lray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	put_img_to_img(t_image *dst, t_image *src, int x, int y)
{
	int	i;
	int	j;
	int	color;

	i = 0;
	while (i < src->height && (i + y) < dst->height)
	{
		j = 0;
		while (j < src->width && (j + x) < dst->width)
		{
			color = get_pixel(src, j, i);
			if (color == -1)
				return (1);
			if (put_pixel(dst, j + x, i + y, color) == 1)
				return (2);
			++j;
		}
		++i;
	}
	return (0);
}
