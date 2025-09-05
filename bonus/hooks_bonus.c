/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crosorio < crosorio@student.42madrid.com>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-03 10:36:58 by crosorio          #+#    #+#             */
/*   Updated: 2025-09-03 10:36:58 by crosorio         ###   ########.fr       */
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
	ft_calculate_all_isos(fdf);
	ft_draw_map(fdf);
	return (0);
}
int	ft_handle_zoom(int keycode, int x, int y, void *param)
{
	t_fdf *fdf = (t_fdf *)param;
    (void)x; (void)y;

	if (keycode == 4) // up +
		fdf->data_cam->zoom *= 1.1;
	else if (keycode == 5) // down -
	{
		fdf->data_cam->zoom /= 1.1;
		if (fdf->data_cam->zoom < 0.1)
			fdf->data_cam->zoom = 0.1;
	}
	ft_calculate_all_isos(fdf);
	ft_draw_map(fdf);
	return (0);
}
// int	ft_handle_zoom(int keycode, t_fdf *fdf)
// {
// 	if (keycode == 4) // up +
// 	{
// 		fdf->data_cam->zoom *= 1.1;
// 		if (fdf->data_cam->zoom > 10.0)
// 			fdf->data_cam->zoom = 10.0;
// 	}
// 	else if (keycode == 5) // down -
// 	{
// 		fdf->data_cam->zoom /= 1.1;
// 		if (fdf->data_cam->zoom < 0.1)
// 			fdf->data_cam->zoom = 0.1;
// 	}
// 	ft_calculate_all_isos(fdf);
// 	ft_draw_map(fdf);
// 	return (0);
// }
