/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fractol_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 14:01:28 by abensett          #+#    #+#             */
/*   Updated: 2021/12/29 20:09:37 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	i = img->bpp - 8;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

int	ft_handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	if (keysym == 99)
		ft_handle_colors(data);
	if (keysym == KEY_UP)
	{
		data->f.y1 -= 0.1;
		data->f.y2 -= 0.1;
	}
	if (keysym == KEY_LEFT)
	{
		data->f.x1 -= 0.1;
		data->f.x2 -= 0.1;
	}
	if (keysym == KEY_DOWN)
	{
		data->f.y1 += 0.1;
		data->f.y2 += 0.1;
	}
	if (keysym == KEY_RIGHT)
	{
		data->f.x1 += 0.1;
		data->f.x2 += 0.1;
	}
	return (0);
}

void	ft_handle_colors(t_data *data)
{
	int COLORS [] = {0x800000, COOL_COLOR, COOL_COLOR2, 0xFFA07A,
		0x40CE16, 0x1640CE, 0xCE1640, 0xFAB6A7, 0xA7FAB6, 0xB6A7FA,
		0x3E060F, 0x0F3E06, 0x060F3E, 0xED7CFE, 0xFEED7C, 0x7CFEED};
	static int i = 0;

	if (i < 20)
			i++;
	else
			i = 0;
	data->f.color = COLORS[i];
}

void	ft_menu(t_data *data)
{
	mlx_mouse_get_pos(data->mlx_ptr, data->win_ptr,
		&data->f.x_posi, &data->f.y_posi);
	mlx_string_put(data->mlx_ptr, data->win_ptr,
		30, 20, 0xFFFFFF, data->fractal_name);
	mlx_string_put(data->mlx_ptr, data->win_ptr,
		30, 40, 0xFFFFFF, ft_itoa((int)data->f.x_posi));
	mlx_string_put(data->mlx_ptr, data->win_ptr,
		30, 50, 0xFFFFFF, ft_itoa((int)data->f.y_posi));
	mlx_string_put(data->mlx_ptr, data->win_ptr,
		30, 70, 0xFFFFFF, "ZOOM :");
	mlx_string_put(data->mlx_ptr, data->win_ptr,
		70, 70, 0xFFFFFF, ft_itoa(data->f.iter_zoom));
}

int	ft_handle_scroll(int button, int x, int y, t_data *data)
{
	double	mx;
	double	my;

	mx = ((long)x / data->f.zoom_x + data->f.x1);
	my = ((long)y / data->f.zoom_y + data->f.y1);
	if (button == 4)
	{
		data->f.x1 = mx + (data->f.x1 - mx) * 0.5;
		data->f.x2 = mx + (data->f.x2 - mx) * 0.5;
		data->f.y1 = my + (data->f.y1 - my) * 0.5;
		data->f.y2 = my + (data->f.y2 - my) * 0.5;
		data->f.imax += 5;
		data->f.iter_zoom++;
	}
	else if (button == 5 && data->f.iter_zoom > 0)
	{
		data->f.x1 = mx + (data->f.x1 - mx) / 0.5;
		data->f.x2 = mx + (data->f.x2 - mx) / 0.5;
		data->f.y1 = my + (data->f.y1 - my) / 0.5;
		data->f.y2 = my + (data->f.y2 - my) / 0.5;
		data->f.imax -= 5;
		data->f.iter_zoom--;
	}
	return (0);
}



