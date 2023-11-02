#ifndef CUB3D_H
# define CUB3D_H

#define DISPLAY_WIDTH 1920
#define DISPLAY_HEIGHT 1080

#include "../libft/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>


typedef struct s_parsing
{
	char	**parsed_lines;
}			t_parsing;

char *gnl_unempty(char *file);

#endif