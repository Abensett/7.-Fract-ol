#include <stdlib.h>
#include <stdio.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include "fractol.h"

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 1000

#define MLX_ERROR 1

#define RED_PIXEL 0xFF0000
#define GREEN_PIXEL 0x00FF00
#define WHITE_PIXEL 0xFFFFFF
#define BLACK_PIXEL 0x0

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp; 
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
}	t_data;
/* 
typedef struct s_mandelbrot
{
	double x1 = -2.1;
	double x2 = 0.6;
	double y1 = -1,2;
	double y2 = 1.2;
	int image_x = 270;
	int image_y  = 240;
	int imax = 50;
} 	 t_mandelbrot; */

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char    *pixel;
	int		i;

	i = img->bpp - 8;
    pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		/* big endian, MSB is the leftmost bit */
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		/* little endian, LSB is the leftmost bit */
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}
void	render_background(t_img *img, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
			my_mlx_pixel_put(img, j++, i, color);
		++i;
	}
}

int	render(t_data *data)
{

	if (data->win_ptr == NULL)
		return (1);

	double x1 = -2.1;
	double x2 = 0.6;
	double y1 = -1.2;
	double y2 = 1.2;
	int imax = 50;
	float zoom_x = WINDOW_WIDTH / (x2 - x1);
	float zoom_y = WINDOW_HEIGHT / (y2 - y1) ;
	int x = 0;
	int y = 0;
	double c_r;
	double c_i;
	double z_r;
	double z_i;
	int i;
	double tmp;
	int COLOR = 0xFF0000;
	while (x < WINDOW_WIDTH)
	{
		y = 0;
		while (y < WINDOW_HEIGHT)
		{
/* 		   printf("\n x = %lf et y= %lf",x,y);
 */
			c_r = x / zoom_x + x1;
			c_i = y / zoom_y + y1;
/* 			printf("\nc_r = %lf et c_i= %lf",c_r, c_i);
 */			z_r = 0;
			z_i = 0;
			i = 0;
			while (z_r * z_r + z_i * z_i < 4 && i < imax)
			{
				tmp = z_r;
				z_r = z_r * z_r - z_i * z_i + c_r;
				z_i = 2 * z_i * tmp + c_i;
				i++;
			}
	
			if (i == imax )
				my_mlx_pixel_put(&data->img, x, y, COLOR - pow(x,2) + pow(y,2) );
			else
				my_mlx_pixel_put(&data->img, x, y, BLACK_PIXEL);

			y++;
		}
		x++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	return (0);
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	return (0);
}



int	main(void)
{
	t_data	data;

	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (MLX_ERROR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT,
								"FRACTOL");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		return (MLX_ERROR);
	}

	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH, WINDOW_WIDTH);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp, &data.img.line_len,
									&data.img.endian);

	mlx_loop_hook(data.mlx_ptr, &render, &data);
	/* Setup hooks */ 
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_loop(data.mlx_ptr);
	/* we will exit the loop if there's no window left, and execute this code */
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
}