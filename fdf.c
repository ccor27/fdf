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

static void	ft_print_map_matrix(t_file_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			ft_printf("(x: %d, y: %d, z: %d, color: %x, Xiso: %d, Yiso: %d)",
				map->matrix[i][j].x, map->matrix[i][j].y, map->matrix[i][j].z,
				map->matrix[i][j].color, map->matrix[i][j].xiso,
				map->matrix[i][j].yiso);
			if (j < map->width - 1)
				ft_printf("  ");
			j++;
		}
		ft_printf("\n");
		i++;
	}
}
static void	ft_initialize(t_file_map *file_map)
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
	ft_validate_and_store(argv[1], &file_map);
	ft_calculate_isos(&file_map);
	ft_print_map_matrix(&file_map);
	ft_error_parse(&file_map, NULL, 0);
		// here we need a function to free memory
}
/**
 * // Pseudo-code for drawing the entire map
void draw_map(t_map *map)
{
    int i = 0;
    while (i < map->height)
    {
        int j = 0;
        while (j < map->width)
        {
            // Draw horizontal line if it exists
            if (j < map->width - 1)
                draw_bresenham_line(map->matrix[i][j], map->matrix[i][j + 1]);

            // Draw vertical line if it exists
            if (i < map->height - 1)
                draw_bresenham_line(map->matrix[i][j], map->matrix[i + 1][j]);

            j++;
        }
        i++;
    }
}
 */
