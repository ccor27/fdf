/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crosorio < crosorio@student.42madrid.com>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-25 13:02:09 by crosorio          #+#    #+#             */
/*   Updated: 2025-08-25 13:02:09 by crosorio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void ft_print_map_matrix(t_file_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			ft_printf("(x: %d, y: %d, z: %d, color: %x)", map->matrix[i][j].x,
				map->matrix[i][j].y, map->matrix[i][j].z,
				map->matrix[i][j].color);
			if (j < map->width - 1)
				ft_printf("  ");
			j++;
		}
		ft_printf("\n");
		i++;
	}
}
static void ft_initialize(t_file_map *file_map)
{
	file_map->width = -1;
	file_map->height = 0;
	file_map->matrix = NULL;
	file_map->tokens = NULL;
}

int	main(int argc, char **argv)
{
	t_file_map	file_map;

	if (argc != 2)
		ft_error("No enough arguments or too much!", 1);
	if (ft_strncmp(ft_strrchr(argv[1], '.'), ".fdf", 4) != 0)
		ft_error("No valid extension, you must use .fdf extension", 1);
	ft_initialize(&file_map);
	ft_printf("before validate and store\n");
	ft_validate_and_store(argv[1], &file_map);
	ft_printf("the validation and store was successfully");
	ft_print_map_matrix(&file_map);
	ft_error_parse(&file_map,NULL,0);//here we need a function to free memory
}
