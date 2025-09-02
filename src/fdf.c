/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crosorio <crosorio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 13:02:09 by crosorio          #+#    #+#             */
/*   Updated: 2025/08/26 14:34:46 by crosorio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// static void	ft_print_map_matrix(t_file_map *map)
// {
// 	int	i;
// 	int	j;
// 	i = 0;
// 	while (i < map->height)
// 	{
// 		j = 0;
// 		while (j < map->width)
// 		{
// 			ft_printf("[%d][%d] -> ",i,j);
// 			ft_printf("(x: %d, y: %d, z: %d, color: %x, Xiso: %d, Yiso: %d)\n",
// 				map->matrix[i][j].x, map->matrix[i][j].y, map->matrix[i][j].z,
// 				map->matrix[i][j].color, map->matrix[i][j].xiso,
// 				map->matrix[i][j].yiso);
// 			j++;
// 		}
// 		i++;
// 	}
// }


static void	ft_initialize(t_fdf *file_map)
{
	file_map->width = -1;
	file_map->height = 0;
	file_map->matrix = NULL;
	file_map->tokens = NULL;
}

void	ft_init_cam(t_fdf *fdf)
{
	double	sx;
	double	sy;
	double	base;

	if (!fdf)
		return ;
	fdf->data_cam = malloc(sizeof(t_cam));
	if (!fdf->data_cam)
		ft_free_and_exit(fdf, "malloc cam failed\n", 1);
	fdf->data_cam->angle = 0.523599;
	sx = (double)fdf->data_img->w / (fdf->width * 2.0);
	sy = (double)fdf->data_img->h / (fdf->height * 2.0);
	base = sx;
	if (sy < sx)
		base = sy;
	if (base < 1.0)
		base = 1.0;
	fdf->data_cam->zoom = base * 0.7;
	fdf->data_cam->z_scale = 2.5;
	fdf->data_cam->x_off = fdf->data_img->w / 2.0;
	fdf->data_cam->y_off = fdf->data_img->h * 0.2;
}

int	ft_init_mlx(t_fdf *fdf)
{
	fdf->mlx_ptr = mlx_init();
	if (fdf->mlx_ptr == NULL)
		return (1);
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, 1366, 768, "FdF");
	if (fdf->win_ptr == NULL)
		return (1);
	fdf->data_img = malloc(sizeof(t_img));
	if (fdf->data_img == NULL)
		return (1);
	fdf->data_img->img = mlx_new_image(fdf->mlx_ptr, 1366, 768);
	if (fdf->data_img->img == NULL)
		return (1);
	fdf->data_img->addr = mlx_get_data_addr(fdf->data_img->img,
			&fdf->data_img->bpp, &fdf->data_img->line_len,
			&fdf->data_img->endian);
	fdf->data_img->w = 1366;
	fdf->data_img->h = 768;
	return (0);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc != 2)
		ft_error("No enough arguments or too much!", 1);
	if (ft_strncmp(ft_strrchr(argv[1], '.'), ".fdf", 4) != 0)
		ft_error("No valid extension, you must use .fdf extension", 1);
	ft_initialize(&fdf);
	ft_validate_and_store(argv[1], &fdf);
	if (ft_init_mlx(&fdf) != 0)
		ft_free_and_exit(&fdf,"Error during the initialization of mlx",1);
	ft_init_cam(&fdf);
	ft_calculate_all_isos(&fdf);
	ft_draw_map(&fdf);
	mlx_hook(fdf.win_ptr,17,0,ft_close,&fdf);
	mlx_loop(fdf.mlx_ptr);
	ft_free_and_exit(&fdf, NULL, 0);
	return(0);
}
