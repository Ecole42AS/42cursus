/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameloop.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lray <lray@student.42lausanne.ch >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 01:09:00 by lray              #+#    #+#             */
/*   Updated: 2024/01/02 18:29:22 by lray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAMELOOP_H
# define GAMELOOP_H

# include "structures.h"

int		gameloop(t_ctx *ctx);
t_image	*raycasting(t_ctx *ctx, t_image *frame);

#endif
