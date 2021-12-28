/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fractol.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 14:03:40 by abensett          #+#    #+#             */
/*   Updated: 2021/12/28 20:12:23 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx.h"
#include "../libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <X11/X.h>
#include <X11/keysym.h>

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 1000

#define DARK_RED 0x050000
#define DARK_BLUE 0x000005
#define DARK_GREEN 0x000500
#define COOL_COLOR 0x474d09
#define COOL_COLOR2 0x1400bb


#define MLX_ERROR 1

typedef struct s_fractal
{
	double x1;
	double x2;
	double y1;
	double y2;
	double c_r;
	double c_i;
	double z_r;
	double z_i;
    double zoom_x;
	double zoom_y;
	int color;
	int x;
	int y;
	int imax;
} t_fractal;

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp; 
	int		line_len;
	int		endian;
}	t_img;



typedef struct s_zoom
{
	double zoom_x;
	double zoom_y;
} 	t_zoom;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	char	*fractal_name;
	t_fractal f;
	t_zoom zm;
	t_img	img;
}	t_data;

/*ft_error_handlers.c*/
void ft_error(void);
int	ft_check_arg(char *av);


/*ft_fractol_utils.c*/
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void    ft_menu(t_data *data);
int	handle_keypress(int keysym, t_data *data);


/* ft_fractal.c*/
void ft_mandelbrot_init(t_fractal *fractal);
void ft_mandelbrot_draw(t_data *data);

/*ft_julia.c*/
void ft_julia_init(t_fractal *fractal);
void ft_julia_draw(t_data *data);
