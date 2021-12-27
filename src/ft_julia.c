/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_julia.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 16:56:16 by abensett          #+#    #+#             */
/*   Updated: 2021/12/27 17:10:00 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

void ft_julia_init(t_mandelbrot *julia)
{
	julia->x1 = -1;
	julia->x2 = 1;
	julia->y1 = -1.2;
	julia->y2 = 1.2;
	julia->c_r = 0;
	julia->c_i = 0;
	julia->z_r = 0;
	julia->z_i = 0;
	julia->x = 0;
	julia->y = 0;
	julia->zoom_x = WINDOW_WIDTH / (julia->x2 - julia->x1);
	julia->zoom_y = WINDOW_HEIGHT / (julia->y2 - julia->y1);
	julia->imax = 150;
}

void ft_julia_draw(t_data *data)
{
	t_mandelbrot mb;
	ft_julia_init(&mb);
	int i;
	double tmp;

	while (mb.x < WINDOW_WIDTH)
	{
		mb.y = 0;
		while (mb.y < WINDOW_HEIGHT)
		{
			mb.c_r = 0.285;
			mb.c_i = 0.01;
			mb.z_r = mb.x / mb.zoom_x + mb.x1;
			mb.z_i = mb.y / mb.zoom_y + mb.y1;
			i = 0;
			while (mb.z_r * mb.z_r + mb.z_i * mb.z_i < 4 && i++ < mb.imax)
			{
				tmp = mb.z_r;
				mb.z_r = mb.z_r * mb.z_r - mb.z_i * mb.z_i + mb.c_r;
				mb.z_i = 2 * mb.z_i * tmp + mb.c_i;
			}
			if (i != mb.imax )
				my_mlx_pixel_put(&data->img, mb. x, mb.y++, 0x1400bb *(i+1) );
			else
				my_mlx_pixel_put(&data->img, mb.x, mb.y++, 0);
		}
		mb.x++;
	}
}
