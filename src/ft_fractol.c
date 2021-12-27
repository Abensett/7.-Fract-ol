/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fractol.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 13:54:38 by abensett          #+#    #+#             */
/*   Updated: 2021/12/27 18:51:48 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_fractol.h"


/* 
typedef struct s_mandelbrot
{
	double mb.x1 = -2.1;
	double mb.x2 = 0.6;
	double mb.y1 = -1,2;
	double mb.y2 = 1.2;
	int image_x = 270;
	int image_y  = 240;
	int mb.imax = 50;
} 	 t_mandelbrot; */


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


int	ft_draw(t_data *data)
{
	int x;
	int y;

	mlx_mouse_get_pos(data->mlx_ptr, data->win_ptr, &x, &y);
	printf("x : %d et y : %d ", x, y);

	if (data->win_ptr == NULL)
		return (1);
	
	ft_julia_draw(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	return (0);
}

/* void    menu(t_data data)
{
	int *x;
	int *y;

	mlx_mouse_get_pos(data->win_ptr, x, y);

	printf("x : %d et y : %d ", *x, *y);
} */
int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	return (0);
}


int	handle_scroll(int button, int x, int y, t_data *data)
{
	if(button == 0)
		printf("x : %d et y : %d\n",x,y );
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

	mlx_loop_hook(data.mlx_ptr, &ft_draw, &data);
	/* Setup hooks */ 
	mlx_mouse_hook(data.win_ptr, &handle_scroll, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_loop(data.mlx_ptr);
	/* we will exit the loop if there's no window left, and execute this code */
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
}