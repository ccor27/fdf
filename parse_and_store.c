/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_store.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crosorio <crosorio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 16:45:02 by crosorio          #+#    #+#             */
/*   Updated: 2025/08/26 18:45:28 by crosorio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "fdf.h"

static void	ft_store_data(t_file_map *file_map,int width, int row, char **tokens)
{
	int	col;

	col = 0;
	while (col < width)
	{
		file_map->matrix[row][col].x = col;//eje horizontal
		file_map->matrix[row][col].y = row;//eje vertical
		file_map->matrix[row][col].z = ft_atoi(tokens[col]);
		if (!parse_token(&file_map->matrix[row][col], tokens[col], col, row))
			ft_error_parse(file_map, "Parse error: Invalid color format\n", 1);
		col++;
	}
}

static void	ft_process_line_aux(int row, char **tokens, t_file_map *map,
		int mode)
{
	int	width;

	width = 0;
	while (tokens[width])
		width++;
	if (mode == 0)
	{
		if (map->width == -1)
			map->width = width;
		else if (width != map->width)
			ft_error_parse(map, "Irregular map\n", 1);
		map->height++;
	}
	else if (mode == 1)
		ft_store_data(map,width,row,tokens);
}

static void	process_line(char *line, t_file_map *file_map, int row, int mode)
{
	file_map-> tokens = ft_split(line, ' ');
	if (!file_map->tokens)
		ft_error_parse(file_map, "Memory error in split\n", 1);
	ft_process_line_aux(row, file_map->tokens, file_map, mode);
}

static void	ft_read_file(t_file_map *file_map, int mode)
{
	char	*line;
	int		row;

	row = 0;
	while (1)
	{
		line = get_next_line(file_map->infile);
		if (line != NULL)
		{
			if (line[0] != '\0' && line[0] != '\n')
			{
				process_line(line, file_map, row, mode);
				if (mode == 1)
					row++;
				free(line);
			}
			else
			{
				free(line);
				ft_error_parse(file_map, "Parse: Map not valid\n", 1);
			}
		}
		else
			break ;
	}
}

void	ft_validate_and_store(char *file, t_file_map *file_map)
{
	file_map->infile = open(file, O_RDONLY);
	if (file_map->infile < 0)
		ft_error_parse(file_map, "Error opening the file", 1);
	ft_read_file(file_map, 0);
	//	close(file_map->infile);
	ft_malloc_matrix_memory(file_map);
	file_map->infile = open(file, O_RDONLY);
	if (file_map->infile < 0)
		ft_error_parse(file_map, "Error opening the file", 1);
	ft_read_file(file_map, 1);
	//	close(file_map->infile);
}
