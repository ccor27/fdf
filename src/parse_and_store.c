/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_store.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crosorio <crosorio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 16:45:02 by crosorio          #+#    #+#             */
/*   Updated: 2025/09/13 14:02:39 by crosorio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_store_data(t_fdf *file_map, int width, int row, char **tokens)
{
	int	col;

	col = 0;
	while (col < width)
	{
		file_map->matrix[row][col].x = col;
		file_map->matrix[row][col].y = row;
		if (!parse_token(&file_map->matrix[row][col], tokens[col]))
			return (0);
		col++;
	}
	return (1);
}

int	ft_process_line_aux(int row, char **tokens, t_fdf *map, int mode)
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
			return (0);
		map->height++;
		return (1);
	}
	else if (mode == 1)
	{
		if (!ft_store_data(map, width, row, tokens))
			return (0);
		else
			return (1);
	}
	else
		return (0);
}

void	process_line(char *line, t_fdf *fdf, int row, int mode)
{
	char	*trimmed_line;

	trimmed_line = ft_strtrim(line, " \t\n");
	if (!trimmed_line)
	{
		free(line);
		get_next_line(0, 1);
		ft_free_and_exit(fdf, "Memory error in trim\n", 1, 1);
	}
	fdf->tokens = ft_split(trimmed_line, ' ');
	if (!fdf->tokens || !ft_process_line_aux(row, fdf->tokens, fdf, mode))
	{
		free(trimmed_line);
		free(line);
		if (!fdf->tokens)
			ft_free_and_exit(fdf, "Memory error in split\n", 1, 1);
		get_next_line(0, 1);
		ft_free_and_exit(fdf, "Memory Irregular map or invalid color/number\n",
			1, 1);
	}
	ft_free_split_tokens(&fdf->tokens);
	free(trimmed_line);
}

void	ft_read_file(t_fdf *file_map, int mode, int row)
{
	char	*line;

	while (1)
	{
		line = get_next_line(file_map->infile, 0);
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
				get_next_line(0, 1);
				ft_free_and_exit(file_map, "Parse: Map not valid\n", 1, 1);
			}
		}
		else
			break ;
	}
}

void	ft_validate_and_store(char *file, t_fdf *file_map)
{
	file_map->infile = open(file, O_RDONLY);
	if (file_map->infile < 0)
		ft_free_and_exit(file_map, "Error opening the file\n", 1, 1);
	ft_read_file(file_map, 0, 0);
	ft_malloc_matrix_memory(file_map);
	close(file_map->infile);
	file_map->infile = open(file, O_RDONLY);
	if (file_map->infile < 0)
		ft_free_and_exit(file_map, "Error opening the file\n", 1, 1);
	ft_read_file(file_map, 1, 0);
}
