/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crosorio <crosorio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 14:01:25 by crosorio          #+#    #+#             */
/*   Updated: 2025/09/11 10:23:30 by crosorio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	ft_set_color_config_values(t_node *a, t_node *b, t_color *conf,
		t_bresenham *b_data)
{
	conf->a = a;
	conf->b = b;
	conf->x = b_data->x_c;
	conf->y = b_data->y_c;
	conf->r_f = 1.0;
	conf->g_f = 1.0;
	conf->b_f = 1.0;
	conf->r=0;
	conf->g=0;
	conf->b_=0;
}

void	ft_find_z_min_max(t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	while (i < fdf->height)
	{
		j = 0;
		while (j < fdf->width)
		{
			if (fdf->matrix[i][j].z < fdf->z_min)
				fdf->z_min = fdf->matrix[i][j].z;
			if (fdf->matrix[i][j].z > fdf->z_max)
				fdf->z_max = fdf->matrix[i][j].z;
			j++;
		}
		i++;
	}
}

int	ft_get_color_from_z(int z, t_fdf *fdf)
{
	double	percent;

	if (fdf->z_max == fdf->z_min)
		return (0xFFFFFF);
	percent = (double)(z - fdf->z_min) / (double)(fdf->z_max - fdf->z_min);
	if (percent < 0.3)
		return (0x0000FF); // azul (profundo)
	else if (percent < 0.6)
		return (0x00FF00); // verde (medio)
	else if (percent < 0.9)
		return (0x964B00); // marrón (alto)
	else
		return (0xFFFFFF); // nieve/picos
}

void	ft_assign_color_by_z(t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	while (i < fdf->height)
	{
		j = 0;
		while (j < fdf->width)
		{
			ft_printf("Color antes: %d\n", fdf->matrix[i][j].color);
			if (fdf->matrix[i][j].color == -1)
			{
				fdf->matrix[i][j].color = ft_get_color_from_z(fdf->matrix[i][j].z,
					fdf);
					ft_printf("Color despues: %d\n", fdf->matrix[i][j].color);
			}
			j++;
		}
		i++;
	}
}
