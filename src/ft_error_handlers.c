/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_handlers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 18:39:35 by abensett          #+#    #+#             */
/*   Updated: 2021/12/29 18:33:30 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

void	ft_error(void)
{
	ft_putstr_fd("Please  use a valid argument: Mandelbrot, Julia", 1);
	exit(0);
}

int	ft_check_arg(char *av)
{
	if (!ft_strncmp(av, "Mandelbrot", 10) && ft_strlen(av) == 10)
		return (0);
	else if (!ft_strncmp(av, "Julia", 5) && ft_strlen(av) == 5)
		return (0);
	return (1);
}
