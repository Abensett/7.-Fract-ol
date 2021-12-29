/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fractol.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 14:03:40 by abensett          #+#    #+#             */
/*   Updated: 2021/12/29 20:08:23 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx.h"
#include "../libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include <math.h>

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 1000
//Colors
#define COOL_COLOR 0x474d09
#define COOL_COLOR2 0x1400bb
//KEYS

#define KEY_LEFT 65361
#define KEY_DOWN 65364
#define KEY_RIGHT 65363
#define KEY_UP 65362

typedef struct s_fractal
{
	int		x; //POUR DESSINER
	int		y;
	double	x1; //POUR valeur de zoom
	double	x2;
	double	y1;
	double	y2;
	double	c_r; // NOMBRE COMPLEXES UTILES POUR CALCUL
	double	c_i;
	double	z_r;
	double	z_i;
	double	zoom_x; //ZOOM
	double	zoom_y;
	int		iter_zoom;
	int		x_posi;
	int		y_posi;
	int		color;

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


typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	char	*fractal_name;
	t_fractal f;
	t_img	img;
}	t_data;

/*ft_error_handlers.c*/
void ft_error(void);
int	ft_check_arg(char *av);


/*ft_fractol_utils.c*/
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	ft_menu(t_data *data);
int		ft_handle_keypress(int keysym, t_data *data);
int		ft_handle_scroll(int button, int x, int y, t_data *data);
void	ft_handle_colors(t_data *data);




/* ft_fractal.c*/
void	ft_mandelbrot_zoom_init(t_fractal *brot);
void 	ft_mandelbrot_init(t_fractal *fractal);
void 	ft_mandelbrot_draw(t_data *data);

/*ft_julia.c*/
void 	ft_julia_zoom_init(t_fractal *julia);
void 	ft_julia_init(t_fractal *fractal);
void 	ft_julia_draw(t_data *data);
