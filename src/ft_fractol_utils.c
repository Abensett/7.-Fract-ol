/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fractol_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 14:01:28 by abensett          #+#    #+#             */
/*   Updated: 2022/01/05 17:56:16 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

int	ft_handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	if (keysym == KEY_C)
		ft_handle_colors(data);
	ft_move(data, keysym);
	return (0);
}

int	ft_handle_scroll(int button, int x, int y, t_data *data)
{
	ft_handle_zoom(button, x, y, data);
	if (button == 3)
		ft_handle_colors(data);
	return (0);
}

void	ft_handle_colors(t_data *data)
{
	static int	colors[20] = {0x800000, COOL_COLOR, COOL_COLOR2, 0xFFA07A,
		0x40CE16, 0x1640CE, 0xCE1640, 0xFAB6A7, 0xA7FAB6, 0xB6A7FA,
		0x3E060F, 0x0F3E06, 0x060F3E, 0xED7CFE, 0xFEED7C, 0x7CFEED,
		0x370028, 0x0f056b, 0x2f1b0c, 0x2f1b0c};
	static int	i = 0;

	if (i < 19)
			i++;
	else
			i = 0;
	data->f.color = colors[i];
}

void	ft_handle_zoom(int button, int x, int y, t_data *data)
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
}

void	ft_move(t_data *data, int keysym)
{
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
}
