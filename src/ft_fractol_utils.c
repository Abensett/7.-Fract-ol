/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fractol_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 14:01:28 by abensett          #+#    #+#             */
/*   Updated: 2021/12/28 18:41:23 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

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

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	return (0);
}

void    ft_menu(t_data *data)
{
	int x;
	int y;
	
	mlx_mouse_get_pos(data->mlx_ptr, data->win_ptr, &x, &y);
	mlx_string_put(data->mlx_ptr, data->win_ptr, 30, 30, 0, ft_itoa(x));
	mlx_string_put(data->mlx_ptr, data->win_ptr, 30, 40, 0, ft_itoa(y));
	mlx_string_put(data->mlx_ptr, data->win_ptr, 30, 80, 0, data->fractal_name);
} 