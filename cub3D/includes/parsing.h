/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:35:41 by astutz            #+#    #+#             */
/*   Updated: 2024/01/13 12:00:22 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef struct s_texture
{
	char	*NO_texture_path;
	char	*SO_texture_path;
	char	*WE_texture_path;
	char	*EA_texture_path;
}			t_texture;

/*voir avec luca si il faut rajouter le t de trgb*/
typedef struct s_color
{
    int	rgb_floor[3];
    int	rgb_ceiling[3];
} 		t_color;

typedef struct s_parsing
{
	char	**parsed_lines;
}			t_parsing;

char	*gnl_unempty(int fd);
int		open_file(char *file_path);
void	free_split(char **split_result);
void	free_texture(t_texture *texture);
void	parse_texture_paths(t_texture *texture, int fd);
void	parse_colors(int fd, t_color *color);


#endif