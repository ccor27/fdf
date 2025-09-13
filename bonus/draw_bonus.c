/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crosorio <crosorio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 10:10:05 by crosorio          #+#    #+#             */
/*   Updated: 2025/09/13 13:10:34 by crosorio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	ft_draw_map(t_fdf *fdf)
{
	size_t	bytes;

	if (!fdf || !fdf->data_img)
		ft_free_and_exit(fdf, "Error drawing map\n", 1, 1);
	bytes = (size_t)fdf->data_img->line_len * (size_t)fdf->data_img->h;
	ft_bzero(fdf->data_img->addr, bytes);
	ft_draw_map_aux(fdf);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->data_img->img, 0,
		0);
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 50, 50, 0xFFFFFF,
		"FDF CONTROLS");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 50, 80, 0xFFFFFF,
		"Move: W A S D");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 50, 110, 0xFFFFFF,
		"Zoom: Scroll + -");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 50, 140, 0xFFFFFF, "Exit: ESC");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 50, 170, 0xFFFFFF,
		"Color Controls: R G B N");
}

void	ft_draw_map_aux(t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	while (i < fdf->height)
	{
		j = 0;
		while (j < fdf->width)
		{
			if (j + 1 < fdf->width)
			{
				ft_draw_bresenham(fdf->data_img, &fdf->matrix[i][j],
					&fdf->matrix[i][j + 1], fdf->data_cam->color_mode);
			}
			if (i + 1 < fdf->height)
			{
				ft_draw_bresenham(fdf->data_img, &fdf->matrix[i][j],
					&fdf->matrix[i + 1][j], fdf->data_cam->color_mode);
			}
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

void	ft_draw_bresenham(t_img *img, t_node *a, t_node *b, int color_mode)
{
	t_bresenham	b_data;
	t_color		conf;

	ft_init_bresenham(&b_data, a, b);
	b_data.x_c = a->xiso;
	b_data.y_c = a->yiso;
	conf.color_mode = color_mode;
	while (1)
	{
		ft_set_color_config_values(a, b, &conf, &b_data);
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
