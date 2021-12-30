/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_julia.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 16:56:16 by abensett          #+#    #+#             */
/*   Updated: 2021/12/30 16:22:53 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

void	ft_julia_zoom_init(t_fractal *julia)
{
	julia->x1 = -1.5;
	julia->x2 = 1.5;
	julia->y1 = -1.5;
	julia->y2 = 1.5;
	julia->imax = 50;
	julia->iter_zoom = 0;
	julia->color = 0xFFA07A;
}

void	ft_julia_init(t_fractal *julia)
{
	if (julia->iter_zoom == 0)
	{
		julia->x1 = -1.5;
		julia->x2 = 1.5;
		julia->y1 = -1.5;
		julia->y2 = 1.5;
		julia->imax = 150;
		julia->iter_zoom = 0;
	}
	julia->z_r = 0;
	julia->z_i = 0;
	julia->x = 0;
	julia->y = 0;
	julia->zoom_x = (double)WINDOW_WIDTH / (julia->x2 - julia->x1);
	julia->zoom_y = (double)WINDOW_HEIGHT / (julia->y2 - julia->y1);
	julia->c_r = ((long)julia->x_posi / julia->zoom_x + julia->x1);
	julia->c_i = ((long)julia->x_posi / julia->zoom_y + julia->y1);
}

void	ft_julia_draw(t_data *d)
{
	int		i;
	double	tmp;

	while (d->f.x < WINDOW_WIDTH)
	{
		d->f.y = 0;
		while (d->f.y < WINDOW_HEIGHT)
		{
			d->f.z_r = d->f.x / d->f.zoom_x + d->f.x1;
			d->f.z_i = d->f.y / d->f.zoom_y + d->f.y1;
			i = 0;
			while (d->f.z_r * d->f.z_r + d->f.z_i * d->f.z_i < 4
				&& i++ < d->f.imax)
			{
				tmp = d->f.z_r;
				d->f.z_r = d->f.z_r * d->f.z_r - d->f.z_i * d->f.z_i + d->f.c_r;
				d->f.z_i = 2 * d->f.z_i * tmp + d->f.c_i;
			}
			if (i != d->f.imax)
				my_mlx_pixel_put(&d->img, d->f. x, d->f.y, d->f.color * i);
			d->f.y++;
		}
		d->f.x++;
	}
}
