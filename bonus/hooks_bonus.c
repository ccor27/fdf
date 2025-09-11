/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crosorio <crosorio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 10:36:58 by crosorio          #+#    #+#             */
/*   Updated: 2025/09/11 10:39:08 by crosorio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	ft_handle_keypress(int keycode, t_fdf *fdf)
{
	int	move_sptep;

	move_sptep = 10;
	if (keycode == 65307)
		ft_free_and_exit(fdf, NULL, 0, 0);
	else if (keycode == 119) // w
		fdf->data_cam->y_off += move_sptep;
	else if (keycode == 115) // s
		fdf->data_cam->y_off -= move_sptep;
	else if (keycode == 97) // a
		fdf->data_cam->x_off += move_sptep;
	else if (keycode == 100) // a
		fdf->data_cam->x_off -= move_sptep;
	else if (keycode == 114) // R
		fdf->data_cam->color_mode = 1;
	else if (keycode == 103) // G
		fdf->data_cam->color_mode = 2;
	else if (keycode == 98) // B
		fdf->data_cam->color_mode = 3;
	else if (keycode == 110) // N (normal)
		fdf->data_cam->color_mode = 0;
	ft_calculate_isos(fdf);
	ft_draw_map(fdf);
	return (0);
}

int	ft_handle_zoom(int keycode, int x, int y, void *param)
{
	t_fdf	*fdf;
	double	prev_zoom;
	double	scale;

	fdf = (t_fdf *)param;
	prev_zoom = fdf->data_cam->zoom;
	if (keycode == 4) // scroll up
		fdf->data_cam->zoom *= 1.1;
	else if (keycode == 5) // scroll down
	{
		fdf->data_cam->zoom /= 1.1;
		if (fdf->data_cam->zoom < 0.1)
			fdf->data_cam->zoom = 0.1;
	}
	else
		return (0);
	scale = fdf->data_cam->zoom / prev_zoom;
	// ajustar offsets para que el zoom se centre en (x,y)
	fdf->data_cam->x_off = x - scale * (x - fdf->data_cam->x_off);
	fdf->data_cam->y_off = y - scale * (y - fdf->data_cam->y_off);
	ft_calculate_isos(fdf);
	ft_draw_map(fdf);
	return (0);
}
