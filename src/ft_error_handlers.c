/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_handlers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 18:39:35 by abensett          #+#    #+#             */
/*   Updated: 2021/12/28 18:42:48 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

void ft_error(void)
{
	ft_putstr_fd("Les arguments valables sont : mandelbrot, julia", 1);
	exit(0);
}

int	ft_check_arg(char *av)
{
	if (!ft_strncmp(av, "mandelbrot", 10) && ft_strlen(av) == 10)
		return (0);
	else if (!ft_strncmp(av, "julia", 5) && ft_strlen(av) == 5)
		return (0);
	return (1);
}