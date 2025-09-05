/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crosorio < crosorio@student.42madrid.com>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-02 10:10:05 by crosorio          #+#    #+#             */
/*   Updated: 2025-09-02 10:10:05 by crosorio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	ft_draw_map(t_fdf *fdf)
{
	size_t	bytes;

	if (!fdf || !fdf->data_img)
		ft_free_and_exit(fdf, "Error drawing map\n", 1,1);
	bytes = (size_t)fdf->data_img->line_len * (size_t)fdf->data_img->h;
	ft_bzero(fdf->data_img->addr, bytes);
	ft_draw_map_aux(fdf);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->data_img->img, 0,
		0);
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
					&fdf->matrix[i][j + 1]);
			}
			if (i + 1 < fdf->height)
			{
				ft_draw_bresenham(fdf->data_img, &fdf->matrix[i][j],
					&fdf->matrix[i + 1][j]);
			}
			j++;
		}
		i++;
	}
}
