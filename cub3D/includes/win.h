/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lray <lray@student.42lausanne.ch >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 01:36:41 by lray              #+#    #+#             */
/*   Updated: 2023/12/30 02:04:53 by lray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WIN_H
# define WIN_H

# include "structures.h"

void	win_init(t_win *win, t_win_params params);
void	win_free(t_win *win);

#endif
