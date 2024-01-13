/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lray <lray@student.42lausanne.ch >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 16:10:14 by lray              #+#    #+#             */
/*   Updated: 2024/01/08 07:27:55 by lray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_UTILS_H
# define MLX_UTILS_H

int		put_pixel(t_image *img, int x, int y, int color);
int		get_pixel(t_image *img, int x, int y);
int		put_img_to_img(t_image *dst, t_image *src, int x, int y);
t_image	*img_create(void *mlx, int width, int height);
t_image	*img_load(void *mlx, char *path);
void	img_free(t_ctx *ctx, t_image *img);

#endif
