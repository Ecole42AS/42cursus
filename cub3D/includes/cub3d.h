#ifndef CUB3D_H
# define CUB3D_H

#define DISPLAY_WIDTH 1920
#define DISPLAY_HEIGHT 1080

#include "../libft/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include "mlx.h"

typedef struct s_mlx
{
    void	*mlx;
    void	*mlx_win;
    void	*mlx_img;
    char	*mlx_data;
}			t_mlx;

typedef struct s_vector
{
	int	x;
	int	y;
}		t_vector;


    // mlx_ptr = mlx_init();
    // win_ptr = mlx_new_window(mlx_ptr, width, height, "Ma Fenêtre Minilibx");
    // image_ptr = mlx_new_image(mlx_ptr, width, height);
    // data_ptr = mlx_get_data_addr(image_ptr, &bits_per_pixel, &size_line, &endian);

    // // Utilisez ces structures pour dessiner et gérer votre application Minilibx

    // mlx_loop(mlx_ptr);
    // return 0;
// }


typedef struct s_parsing
{
	char	**parsed_lines;
}			t_parsing;

char	*gnl_unempty(int fd);

#endif