#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "./minilibx-linux/mlx.h"
# include "cub3D_types.h"

#define	WINDOW_WIDTH 1366
#define WINDOW_HEIGHT 768
#define RED 0xFF0000
#define GREEN 0x00FF00
#define BLUE 0x0000FF
#define KEY_ESC 65307

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
	int		w;
	int		h;
}	t_img;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	t_img	frame;
}	t_mlx;


/* app */
int parse_cub_file(const char *path, t_mlx *game);
// int		game_init(t_game *g);
// int		game_destroy(t_game *g, int code);

#endif
