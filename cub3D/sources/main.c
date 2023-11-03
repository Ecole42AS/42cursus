/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:15:29 by astutz            #+#    #+#             */
/*   Updated: 2023/11/03 13:10:13 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int main(int ac, char **av)
{
	(void)ac;
	(void)av;
	t_mlx *mlx;
	mlx->mlx = mlx_init();
	mlx->mlx_win = mlx_new_window(mlx->mlx, DISPLAY_WIDTH, DISPLAY_HEIGHT, "Cub3D");
	mlx->mlx_img = mlx_new_image()
	mlx_loop(mlx->mlx);
    int fd = open("/Users/astutz/42cursus/cub3D/test.txt", O_RDONLY);

	if (fd == -1)
	{
		ft_putstr_fd(strerror(errno), 2);
		return(1);
	}

    char *line;
    while ((line = gnl_unempty(fd)) != NULL)
	{
		if (line[strlen(line) - 1] == '\n')
            line[strlen(line) - 1] = '\0';
        printf("Ligne non vide : %s\n", line);
        free(line);
    }

    close(fd);

    return 0;
}
