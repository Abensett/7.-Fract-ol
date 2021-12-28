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

void ft_mandelbrot_init(t_fractal *brot)
{
	brot->x1 = -2.1;
	brot->x2 = 0.6;
	brot->y1 = -1.2;
	brot->y2 = 1.2;
	brot->c_i = brot->y / brot->zoom_y + brot->y1;
	brot->c_r = brot->x / brot->zoom_x + brot->x1;
	brot->z_r = 0;
	brot->z_i = 0;
	brot->x = 0;
	brot->y = 0;
	brot->zoom_x = WINDOW_WIDTH / (brot->x2 - brot->x1);
	brot->zoom_y = WINDOW_HEIGHT / (brot->y2 - brot->y1);
	brot->imax = 200;
}

void ft_mandelbrot_draw(t_data *data)
{
	int i;
	double tmp;

	ft_mandelbrot_init(&data->f);
	while (data->f.x < WINDOW_WIDTH)
	{
		data->f.y = 0;
		while (data->f.y < WINDOW_HEIGHT)
		{
			data->f.c_r = data->f.x / data->f.zoom_x + data->f.x1;
			data->f.c_i = data->f.y / data->f.zoom_y + data->f.y1;
			data->f.z_r = 0;
			data->f.z_i = 0;
			i = 0;
			while (data->f.z_r * data->f.z_r + data->f.z_i * data->f.z_i < 4 && i++ < data->f.imax)
			{
				tmp = data->f.z_r;
				data->f.z_r = data->f.z_r * data->f.z_r - data->f.z_i * data->f.z_i + data->f.c_r;
				data->f.z_i = 2 * data->f.z_i * tmp + data->f.c_i;
			}
			if (i != data->f.imax )
				my_mlx_pixel_put(&data->img, data->f. x, data->f.y++, DARK_BLUE+ i * 20);
			else
				my_mlx_pixel_put(&data->img, data->f.x, data->f.y++, 0);
		}
		data->f.x++;
	}
}