/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 10:34:16 by astutz            #+#    #+#             */
/*   Updated: 2023/07/31 16:38:47 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*	Math formula to convert 3D points to 2D points to draw a perspective map.*/
void	ft_convert_fx(t_data *data, int x, int y, int i)
{
	data->t_point[i].fx = (x * cosf(data->alpha) + \
							y * cosf(data->alpha + 2) + \
							(data->map.parse[y][x] * data->key.altitude) * \
							cosf(data->alpha - 2));
	data->t_point[i].fx *= -data->size;
}

void	ft_convert_fy(t_data *data, int x, int y, int i)
{
	data->t_point[i].fy = (x * sinf(data->alpha) + \
							y * sinf(data->alpha + 2) + \
							(data->map.parse[y][x] * data->key.altitude) * \
							sinf(data->alpha - 2));
	data->t_point[i].fy *= -data->size;
}

/*	Convert the X, Y and Z with the above formula inside a structure. */
void	ft_convert(t_data *data)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	y = -1;
	data->t_point = malloc(sizeof(t_point) * \
							(data->map.height * data->map.width));
	if (!data->t_point)
	{
		ft_free_map_parse(data);
		ft_display_error("Error with malloc during convert.\n");
	}
	while (++y < data->map.height)
	{
		x = -1;
		while (++x < data->map.width)
		{
			ft_convert_fx(data, x, y, i);
			ft_convert_fy(data, x, y, i);
			i++;
		}
	}
}
