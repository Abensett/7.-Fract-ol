/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mandelbrot->c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 14:06:55 by abensett          #+#    #+#             */
/*   Updated: 2021/12/27 14:12:20 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

void ft_mandelbrot_init(t_mandelbrot *brot)
{
	brot->x1 = -2.1;
	brot->x2 = 0.6;
	brot->y1 = -1.2;
	brot->y2 = 1.2;
	brot->c_r = 0;
	brot->c_i = 0;
	brot->z_r = 0;
	brot->z_i = 0;
	brot->x = 0;
	brot->y = 0;
	brot->zoom_x = WINDOW_WIDTH / (brot->x2 - brot->x1);
	brot->zoom_y = WINDOW_HEIGHT / (brot->y2 - brot->y1);
	brot->imax = 50;
}

void ft_mandelbrot_draw(t_data *data)
{
	t_mandelbrot mb;
	ft_mandelbrot_init(&mb);
	int i;
	double tmp;

	while (mb.x < WINDOW_WIDTH)
	{
		mb.y = 0;
		while (mb.y < WINDOW_HEIGHT)
		{
			mb.c_r = mb.x / mb.zoom_x + mb.x1;
			mb.c_i = mb.y / mb.zoom_y + mb.y1;
			mb.z_r = 0;
			mb.z_i = 0;
			i = 0;
			while (mb.z_r * mb.z_r + mb.z_i * mb.z_i < 4 && i++ < mb.imax)
			{
				tmp = mb.z_r;
				mb.z_r = mb.z_r * mb.z_r - mb.z_i * mb.z_i + mb.c_r;
				mb.z_i = 2 * mb.z_i * tmp + mb.c_i;
			}
			if (i != mb.imax )
				my_mlx_pixel_put(&data->img, mb. x, mb.y++, DARK_RED *(i+1) );
			else
				my_mlx_pixel_put(&data->img, mb.x, mb.y++, 0);
		}
		mb.x++;
	}
}

/* t_mandelbrot *mb;
	int i;
	double tmp;

	ft_mandelbrot_init(mb);
	while (mb.x < WINDOW_WIDTH)
	{
		mb.y = 0;
		while (mb.y < WINDOW_HEIGHT)
		{
			mb.mb.c_r = mb.x / mb.zoom_x + mb.x1;
			mb.mb.c_i = mb.y / mb.zoom_y + mb.y1;
			mb.mb.z_r = 0;
			mb.mb.z_i = 0;
			i = 0;
			while (mb.mb.z_r * mb.mb.z_r + mb.mb.z_i * mb.mb.z_i < 4 && i < mb.imax)
			{
				tmp = mb.mb.z_r;
				mb.mb.z_r = mb.mb.z_r * mb.mb.z_r - mb.mb.z_i * mb.mb.z_i + mb.mb.c_r;
				mb.mb.z_i = 2 * mb.mb.z_i * tmp + mb.mb.c_i;
				i++;
			}
			if (i != mb.imax )
				my_mlx_pixel_put(&data->img, mb.x, mb.y, DARK_RED *(i+1) );
			else
				my_mlx_pixel_put(&data->img, mb.x, mb.y, 0);

			mb.y++;
		}
		mb.x++;
	} */
	