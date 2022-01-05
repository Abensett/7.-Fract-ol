/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_burning_bird.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 14:38:41 by abensett          #+#    #+#             */
/*   Updated: 2022/01/05 17:51:47 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

void	ft_burning_bird_zoom_init(t_fractal *brot)
{
	brot->x1 = -2;
	brot->x2 = 2;
	brot->y1 = -2;
	brot->y2 = 2;
	brot->imax = 100;
	brot->color = 0xFFA07A;
	brot->x_posi = 0;
	brot->y_posi = 0;
	brot->iter_zoom = 0;
}

void	ft_burning_bird_init(t_fractal *brot)
{
	if (brot->iter_zoom == 0)
	{
		brot->x1 = -2;
		brot->x2 = 2;
		brot->y1 = -2;
		brot->y2 = 2;
		brot->imax = 100;
		brot->iter_zoom = 0;
	}
	brot->z_r = 0;
	brot->z_i = 0 ;
	brot->x = 0;
	brot->y = 0;
	brot->zoom_x = (double)WINDOW_WIDTH / (brot->x2 - brot->x1);
	brot->zoom_y = (double) WINDOW_HEIGHT / (brot->y2 - brot->y1);
	brot->c_i = brot->y / brot->zoom_y + brot->y1;
	brot->c_r = brot->x / brot->zoom_x + brot->x1;
}

static	double	my_abs(double a)
{
	if (a < 0)
		return (-a);
	return (a);
}

static	double	my_pow(double a)
{
	return (a * a);
}

void	ft_burning_bird_draw(t_data *d)
{
	int		i;
	double	tmp;

	while (d->f.x < WINDOW_WIDTH)
	{
		d->f.y = 0;
		while (d->f.y < WINDOW_HEIGHT)
		{
			d->f.c_r = d->f.x / d->f.zoom_x + d->f.x1;
			d->f.c_i = d->f.y / d->f.zoom_y + d->f.y1;
			d->f.z_r = 0;
			d->f.z_i = 0;
			i = 0;
			while (my_pow(d->f.z_r) + my_pow(d->f.z_i) < 4 && i++ < d->f.imax)
			{
				tmp = d->f.z_r;
				d->f.z_r = my_pow(d->f.z_r) - my_pow(d->f.z_i) + d->f.c_r;
				d->f.z_i = -2 * my_abs(d->f.z_i) * tmp + d->f.c_i;
			}
			if (i != d->f.imax)
				my_mlx_pixel_put(&d->img, d->f. x, d->f.y, d->f.color * i);
			d->f.y++;
		}
		d->f.x++;
	}
}
