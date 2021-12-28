/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fractol.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 13:54:38 by abensett          #+#    #+#             */
/*   Updated: 2021/12/28 20:14:42 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_fractol.h"


int	ft_draw(t_data *data)
{
	
	
	
	if (data->win_ptr == NULL)
		return (1);
	
	ft_julia_init(&data->f);
	data->zm.zoom_x = WINDOW_WIDTH / (data->f.x2 - data->f.x1);
	data->zm.zoom_y = WINDOW_HEIGHT / (data->f.y2 - data->f.y1);
	ft_julia_draw(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	ft_menu(data);
	return (0);
}


int	handle_scroll(int button, int x, int y, t_data *data)
{
	if(button == 4)
	{
		data->f.x1 +=100;
 		data->f.y2 +=100; 
	}
	return (0);
}

int ft_init_zoom (char *zoom)
{
	
}


int		main(int ac, char **av)
{
	t_data	data;
/* 	if (ac != 2)
		ft_error();
	if (ft_check_arg(av[1]))
		ft_error(); */

	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (MLX_ERROR);
	data.win_ptr = mlx_new_window(data.mlx_ptr,
					 WINDOW_WIDTH, WINDOW_HEIGHT,"FRACTOL");
	if (data.win_ptr == NULL)
		return (MLX_ERROR);
	data.fractal_name = ft_strdup(av[1]);
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH, WINDOW_WIDTH);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp,
				&data.img.line_len, &data.img.endian);

	mlx_loop_hook(data.mlx_ptr, &ft_draw, &data);
	mlx_mouse_hook(data.win_ptr, &handle_scroll, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_loop(data.mlx_ptr);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
}	