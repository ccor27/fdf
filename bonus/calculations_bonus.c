/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crosorio <crosorio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 12:52:56 by crosorio          #+#    #+#             */
/*   Updated: 2025/09/06 13:42:28 by crosorio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	ft_calculate_all_isos(t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	while (i < fdf->height)
	{
		j = 0;
		while (j < fdf->width)
		{
			ft_calculate_isos(&fdf->matrix[i][j], fdf->data_cam);
			j++;
		}
		i++;
	}
}

void	ft_calculate_isos(t_node *node, t_cam *cam)
{
	double	tmp_x;
	double	tmp_y;

	tmp_x = (node->x - node->y) * cos(cam->angle) * cam->zoom;
	tmp_y = (node->x + node->y) * sin(cam->angle) * cam->zoom - (node->z
			* cam->z_scale);
	node->xiso = (int)tmp_x + cam->x_off;
	node->yiso = (int)tmp_y + cam->y_off;
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

void	ft_draw_bresenham(t_img *img, t_node *a, t_node *b, int color_mode)
{
	t_bresenham	b_data;
	t_color		conf;

	ft_init_bresenham(&b_data, a, b);
	b_data.x_c = a->xiso;
	b_data.y_c = a->yiso;
	conf.color_mode=color_mode;
	while (1)
	{
		ft_set_color_config_values(a,b,&conf,&b_data);
		img_put_pixel(img, b_data.x_c, b_data.y_c, ft_get_color(conf));
		if (b_data.x_c == b->xiso && b_data.y_c == b->yiso)
			break ;
		b_data.e2_val = 2 * b_data.err;
		if (b_data.e2_val > -b_data.dy)
		{
			b_data.err -= b_data.dy;
			b_data.x_c += b_data.sx;
		}
		if (b_data.e2_val < b_data.dx)
		{
			b_data.err += b_data.dx;
			b_data.y_c += b_data.sy;
		}
	}
}
