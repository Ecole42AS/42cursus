/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lray <lray@student.42lausanne.ch >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 18:44:58 by lray              #+#    #+#             */
/*   Updated: 2024/01/09 10:43:00 by lray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

# define CLR_BLACK		0x00000000U
# define CLR_GRAY		0x00808080U
# define CLR_LIGHT_GRAY	0x00C0C0C0U
# define CLR_DARK_GRAY	0x00404040U
# define CLR_WHITE		0x11111111U
# define CLR_RED		0x00FF0000U
# define CLR_ORANGE		0x00FFA500U
# define CLR_YELLOW		0x00FFFF00U
# define CLR_GREEN		0x0000FF00U
# define CLR_BLUE		0x000000FFU
# define CLR_INDIGO		0x004B0082U
# define CLR_VIOLET		0x008000FFU
# define CLR_CYAN		0x0000FFFFU
# define CLR_MAGENTA	0x00FF00FFU
# define CLR_PURPLE		0x00800080U
# define CLR_BROWN		0x00A52A2AU

int				clr_make_trgb(unsigned char t, unsigned char r, \
	unsigned char g, unsigned char b);
unsigned char	clr_get_t(int trgb);
unsigned char	clr_get_r(int trgb);
unsigned char	clr_get_g(int trgb);
unsigned char	clr_get_b(int trgb);

#endif
