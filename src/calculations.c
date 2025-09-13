/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crosorio <crosorio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 14:16:09 by crosorio          #+#    #+#             */
/*   Updated: 2025/09/13 13:01:44 by crosorio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_calculate_isos(t_fdf *fdf)
{
	int		i;
	int		j;
	double	tmp_x;
	double	tmp_y;

	i = 0;
	while (i < fdf->height)
	{
		j = 0;
		while (j < fdf->width)
		{
			tmp_x = (fdf->matrix[i][j].x - fdf->matrix[i][j].y)
				* cos(fdf->data_cam->angle) * fdf->data_cam->zoom;
			tmp_y = (fdf->matrix[i][j].x + fdf->matrix[i][j].y)
				* sin(fdf->data_cam->angle) * fdf->data_cam->zoom
				- (fdf->matrix[i][j].z * fdf->data_cam->z_scale);
			fdf->matrix[i][j].xiso = (int)tmp_x + fdf->data_cam->x_off;
			fdf->matrix[i][j].yiso = (int)tmp_y + fdf->data_cam->y_off;
			j++;
		}
		i++;
	}
}

void	img_put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (!img || !img->addr)
		return ;
	if (x < 0 || x >= img->w || y < 0 || y >= img->h)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = (unsigned int)color;
}

void	ft_init_bresenham(t_bresenham *b, t_node *a, t_node *b_node)
{
	int	dx_val;
	int	dy_val;

	dx_val = b_node->xiso - a->xiso;
	dy_val = b_node->yiso - a->yiso;
	b->dx = abs(dx_val);
	b->dy = abs(dy_val);
	b->sx = 1;
	if (dx_val < 0)
		b->sx = -1;
	b->sy = 1;
	if (dy_val < 0)
		b->sy = -1;
	b->err = b->dx - b->dy;
}

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
		img_put_pixel(img, x_current, y_current, a->color);
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
