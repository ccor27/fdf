/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crosorio < crosorio@student.42madrid.com>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-04 12:52:56 by crosorio          #+#    #+#             */
/*   Updated: 2025-09-04 12:52:56 by crosorio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	ft_draw_bresenham(t_img *img, t_node *a, t_node *b)
{
	t_bresenham	b_data;
	int			e2_val;
	int			x_current;
	int			y_current;

	ft_init_bresenham(&b_data, a, b);
	x_current = a->xiso;
	y_current = a->yiso;
	while (1)
	{
		img_put_pixel(img, x_current, y_current, 0xFF0000);
		if (x_current == b->xiso && y_current == b->yiso)
			break ;
		e2_val = 2 * b_data.err;
		if (e2_val > -b_data.dy)
		{
			b_data.err -= b_data.dy;
			x_current += b_data.sx;
		}
		if (e2_val < b_data.dx)
		{
			b_data.err += b_data.dx;
			y_current += b_data.sy;
		}
	}
}
