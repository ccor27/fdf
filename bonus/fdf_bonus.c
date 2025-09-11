/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crosorio <crosorio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 13:02:09 by crosorio          #+#    #+#             */
/*   Updated: 2025/09/11 12:40:04 by crosorio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	ft_initialize(t_fdf *file_map)
{
	file_map->width = -1;
	file_map->height = 0;
	file_map->matrix = NULL;
	file_map->tokens = NULL;
	file_map->z_max = -2147483648;
	file_map->z_min = 2147483647;
	file_map->data_cam = NULL;
	file_map->data_img = NULL;
	file_map->mlx_ptr = NULL;
	file_map->win_ptr = NULL;
}

//37.7 degrees fdf->data_cam->angle = 0.6578;
void	ft_init_cam(t_fdf *fdf)
{
	double	sx;
	double	sy;
	double	base;

	if (!fdf)
		return ;
	fdf->data_cam = malloc(sizeof(t_cam));
	if (!fdf->data_cam)
		ft_free_and_exit(fdf, "malloc cam failed\n", 1, 1);
	fdf->data_cam->angle = 0.523599;
	sx = (double)fdf->data_img->w / (fdf->width * 2.0);
	sy = (double)fdf->data_img->h / (fdf->height * 2.0);
	base = sx;
	if (sy < sx)
		base = sy;
	if (base < 1.0)
		base = 1.0;
	fdf->data_cam->zoom = base * 0.9;
	fdf->data_cam->z_scale = 2.5;
	fdf->data_cam->x_off = fdf->data_img->w / 2.0;
	fdf->data_cam->y_off = fdf->data_img->h * 0.2;
}

int	ft_init_mlx(t_fdf *fdf)
{
	fdf->mlx_ptr = mlx_init();
	if (fdf->mlx_ptr == NULL)
		return (1);
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, 2560, 1440, "FdF");
	//fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, 1366, 768, "FdF");
	if (fdf->win_ptr == NULL)
		return (1);
	fdf->data_img = malloc(sizeof(t_img));
	if (fdf->data_img == NULL)
		return (1);
	fdf->data_img->img = mlx_new_image(fdf->mlx_ptr, 2560, 1440);
	//fdf->data_img->img = mlx_new_image(fdf->mlx_ptr, 1366, 768);
	if (fdf->data_img->img == NULL)
		return (1);
	fdf->data_img->addr = mlx_get_data_addr(fdf->data_img->img,
			&fdf->data_img->bpp, &fdf->data_img->line_len,
			&fdf->data_img->endian);
	fdf->data_img->w = 2560;
	fdf->data_img->h = 1440;
	return (0);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;
	char    *file_extension;

	if (argc != 2)
		ft_error("No enough arguments or too much!\n", 1);
	file_extension =ft_strrchr(argv[1], '.');
	if (file_extension == NULL || ft_strncmp(file_extension, ".fdf", 4) != 0)
		ft_error("No valid extension, you must use .fdf extension\n", 1);
	ft_initialize(&fdf);
	ft_validate_and_store(argv[1], &fdf);
	if (ft_init_mlx(&fdf) != 0)
		ft_free_and_exit(&fdf, "Error during the initialization of mlx\n", 1, 1);
	ft_init_cam(&fdf);
	ft_calculate_isos(&fdf);
	ft_draw_map(&fdf);
	mlx_hook(fdf.win_ptr, 17, 0, ft_close, &fdf);
	mlx_hook(fdf.win_ptr, 2, 1L << 0, ft_handle_keypress, &fdf);
	mlx_hook(fdf.win_ptr, 4, 1L << 2, ft_handle_zoom, &fdf);
	mlx_loop(fdf.mlx_ptr);
	ft_free_and_exit(&fdf, NULL, 0, 1);
	return (0);
}
