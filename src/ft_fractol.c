/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fractol.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 13:54:38 by abensett          #+#    #+#             */
/*   Updated: 2021/12/30 17:38:44 by abensett         ###   ########.fr       */
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

int	ft_draw(t_data *data)
{
	/* if (data->win_ptr == NULL)
		return (1);
	if (!ft_strncmp(data->fractal_name, "Mandelbrot", 10))
	{
		ft_mandelbrot_init(&data->f);
		ft_mandelbrot_draw(data);
	}
	else if (!ft_strncmp(data->fractal_name, "Julia", 5))
	{
		ft_julia_init(&data->f);
		ft_julia_draw(data);
	}
	else if (ft_strncmp(data->fractal_name, "Julia", 5))
	{
		ft_julia_init(&data->f);
		ft_julia_draw(data);
	} */
/* 	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img,
		0, 0); */
/* 	ft_menu(data);
 */	return (0);
}

int	ft_init_fractal(t_data data)
{
	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (1);
	data.win_ptr = mlx_new_window(data.mlx_ptr,
			WINDOW_WIDTH, WINDOW_HEIGHT, "Fract'ol");
	if (data.win_ptr == NULL)
		return (1);
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH, WINDOW_WIDTH);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp,
			&data.img.line_len, &data.img.endian);
	mlx_loop_hook(data.mlx_ptr, &ft_draw, &data);
/*  	mlx_mouse_hook(data.win_ptr, &ft_handle_scroll, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &ft_handle_keypress, &data); */
	mlx_loop(data.mlx_ptr);
	mlx_destroy_image(data.mlx_ptr,data.img.mlx_img);
	mlx_destroy_window(data.mlx_ptr, data.win_ptr);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
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

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		ft_error();
	if (ft_check_arg(av[1]))
		ft_error();
	data.fractal_name = av[1];
 	if (!ft_strncmp(data.fractal_name, "Mandelbrot", 10))
		ft_mandelbrot_zoom_init(&data.f);
	else if (!ft_strncmp(data.fractal_name, "Julia", 5))
		ft_julia_zoom_init(&data.f);
	ft_init_fractal(data);
}
