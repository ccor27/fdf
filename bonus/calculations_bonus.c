/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crosorio <crosorio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 12:52:56 by crosorio          #+#    #+#             */
/*   Updated: 2025/09/19 14:04:55 by crosorio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

/**
 * Function to apply the isometric projection
 */
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

/**
 * Function to get the percentage for colors
 */
double	ft_get_percent(int start, int end, int current)
{
	if (start == end)
		return (1.0);
	return ((double)(current - start) / (double)(end - start));
}

/**
 * Function to get the interpolation's value
 */
int	ft_interpolate(int start, int end, double t)
{
	return ((int)(start + (end - start) * t));
}

/**
 * Funtion to get the color of the line to draw
 */
int	ft_get_color(t_color *conf)
{
	double	percent;

	if (conf->a->color == 0x000000 && conf->b->color == 0x000000)
		return (0xFFFFFF);
	if (abs(conf->b->xiso - conf->a->xiso) > abs(conf->b->yiso - conf->a->yiso))
		percent = ft_get_percent(conf->a->xiso, conf->b->xiso, conf->x);
	else
		percent = ft_get_percent(conf->a->yiso, conf->b->yiso, conf->y);
	conf->r = ft_interpolate(((conf->a->color >> 16) & 0xFF),
			((conf->b->color >> 16) & 0xFF), percent);
	conf->g = ft_interpolate(((conf->a->color >> 8) & 0xFF),
			((conf->b->color >> 8) & 0xFF), percent);
	conf->b_ = ft_interpolate((conf->a->color & 0xFF), (conf->b->color & 0xFF),
			percent);
	if (conf->color_mode == 1)
		conf->r_f = 1.5;
	else if (conf->color_mode == 2)
		conf->g_f = 1.5;
	else if (conf->color_mode == 3)
		conf->b_f = 1.5;
	conf->r = fmin(255, (int)(conf->r * conf->r_f));
	conf->g = fmin(255, (int)(conf->g * conf->g_f));
	conf->b_ = fmin(255, (int)(conf->b_ * conf->b_f));
	return ((conf->r << 16) | (conf->g << 8) | conf->b_);
}
