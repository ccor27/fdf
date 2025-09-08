/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crosorio <crosorio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 10:10:05 by crosorio          #+#    #+#             */
/*   Updated: 2025/09/06 14:45:32 by crosorio         ###   ########.fr       */
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
		"FdF Controls:");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 50, 80, 0xFFFFFF,
		"Move: W A S D");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 50, 110, 0xFFFFFF, "Zoom: Scroll + -");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 50, 170, 0xFFFFFF, "Exit: ESC");
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
					&fdf->matrix[i][j + 1],fdf->data_cam->color_mode);
			}
			if (i + 1 < fdf->height)
			{
				ft_draw_bresenham(fdf->data_img, &fdf->matrix[i][j],
					&fdf->matrix[i + 1][j],fdf->data_cam->color_mode);
			}
			j++;
		}
		i++;
	}
}

double	ft_get_percent(int start, int end, int current)
{
	if (start == end)
		return (1.0);
	return ((double)(current - start) / (double)(end - start));
}

int	ft_interpolate(int start, int end, double t)
{
	return (int)(start + (end - start) * t);
}

int	ft_get_color(t_color conf)
{
	double	percent;

	int r, g, b_;
	if (conf.a->color == 0x000000 && conf.b->color == 0x000000)
		return (0xFFFFFF);
	if (abs(conf.b->xiso - conf.a->xiso) > abs(conf.b->yiso - conf.a->yiso))
		percent = ft_get_percent(conf.a->xiso, conf.b->xiso, conf.x);
	else
		percent = ft_get_percent(conf.a->yiso, conf.b->yiso, conf.y);
	r = ft_interpolate(((conf.a->color >> 16) & 0xFF),
			((conf.b->color >> 16) & 0xFF), percent);
	g = ft_interpolate(((conf.a->color >> 8) & 0xFF),
			((conf.b->color >> 8) & 0xFF), percent);
	b_ = ft_interpolate((conf.a->color & 0xFF), (conf.b->color & 0xFF),
			percent);
	if (conf.color_mode == 1) // R
		 return ((r << 16) | (g << 15) | (b_ << 15));
	else if (conf.color_mode == 2) // G
		return ((r << 15) | (g << 8) | (b_ << 15));
	else if (conf.color_mode == 3) // B
		return ((r << 15) | (g << 15) | b_);
	else
		return ((r << 16) | (g << 8) | b_);
}
