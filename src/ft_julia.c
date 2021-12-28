/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_julia.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 16:56:16 by abensett          #+#    #+#             */
/*   Updated: 2021/12/28 20:09:46 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

void ft_julia_init(t_fractal *julia)
{
	julia->x1 = -1;
	julia->x2 = 1;
	julia->y1 = -1.2;
	julia->y2 = 1.2;
	julia->c_r = 0.285;
	julia->c_i = 0.01;
	julia->z_r = 0;
	julia->z_i = 0;
	julia->x = 0;
	julia->y = 0;
	julia->color = DARK_BLUE;
	julia->imax = 150;
}


void ft_julia_draw(t_data *data)
{
	int i;
	double tmp;

	while (data->f.x < WINDOW_WIDTH)
	{
		data->f.y = 0;
		while (data->f.y < WINDOW_HEIGHT)
		{
			data->f.z_r = data->f.x / data->zm.zoom_x + data->f.x1;
			data->f.z_i = data->f.y / data->zm.zoom_y + data->f.y1;
			i = 0;
			while (data->f.z_r * data->f.z_r + data->f.z_i * data->f.z_i < 4 
					&& i++ < data->f.imax)
			{
				tmp = data->f.z_r;
				data->f.z_r = data->f.z_r * data->f.z_r - data->f.z_i * data->f.z_i + data->f.c_r;
				data->f.z_i = 2 * data->f.z_i * tmp + data->f.c_i;
			}
			if (i != data->f.imax )
				my_mlx_pixel_put(&data->img, data->f. x, data->f.y, data->f.color + i * 20 );
			data->f.y++;
		}
		data->f.x++;
	}
}
