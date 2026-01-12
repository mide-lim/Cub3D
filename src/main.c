# include "../includes/cub3D.h"

void ft_put_pixel(t_img *data, int x, int y, int color)
{
    char *pxl;

    if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
    {
        pxl = data->addr + (y * data->line_len + x * (data->bits_per_pixel / 8));
        *(unsigned int *)pxl = color;
    }
}

void	draw_square_4x4(t_img *data, int start_x, int start_y, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			ft_put_pixel(data, start_x + x, start_y + y, color);
			x++;
		}
		y++;
	}
}

int	clean_exit(t_mlx *data)
{
	if (!data)
		exit(0);

	if (data->frame.img)
		mlx_destroy_image(data->mlx, data->frame.img);

	if (data->win)
		mlx_destroy_window(data->mlx, data->win);

	/* aqui depois entram:
	   - free do mapa
	   - free das texturas
	   - free de arrays
	*/
	exit(0);
}


int	key_press(int keycode, t_mlx *data)
{
	if (keycode == KEY_ESC)
		clean_exit(data);
	return (0);
}



int	main(int argc, char **argv)
{
    t_img	img;
    t_mlx	mlx_data;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <map.cub>\n", argv[0]);
        return (EXIT_FAILURE);
    }

    parse_cub_file(argv[1], &mlx_data);

	mlx_data.mlx = mlx_init();
	mlx_data.win = mlx_new_window(mlx_data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Hello world!");
    img.img = mlx_new_image(mlx_data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
        &img.line_len, &img.endian);
    mlx_data.frame = img;
    

    mlx_hook(mlx_data.win, ON_DESTROY, 0, clean_exit, &mlx_data);
    mlx_hook(mlx_data.win, ON_KEYDOWN, 1L << 0, key_press, &mlx_data);

    draw_square_4x4(&mlx_data.frame, (WINDOW_WIDTH / 2), (WINDOW_HEIGHT / 2), RED);
    mlx_put_image_to_window(mlx_data.mlx, mlx_data.win, mlx_data.frame.img, 0, 0);


	mlx_loop(mlx_data.mlx);

}

