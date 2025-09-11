/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_store_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crosorio <crosorio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 16:45:02 by crosorio          #+#    #+#             */
/*   Updated: 2025/09/11 10:48:12 by crosorio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	ft_store_data(t_fdf *fdf, int width, int row, char **tokens)
{
	int	col;

	col = 0;
	while (col < width)
	{
		fdf->matrix[row][col].x = col;
		fdf->matrix[row][col].y = row;
		if (!parse_token(&fdf->matrix[row][col], tokens[col]))
			ft_free_and_exit(fdf,
				"Parse error: Invalid either color or number\n", 1, 1);
		col++;
	}
}

void	ft_process_line_aux(int row, char **tokens, t_fdf *map, int mode)
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
			ft_free_and_exit(map, "Irregular map\n", 1, 1);
		map->height++;
	}
	else if (mode == 1)
		ft_store_data(map, width, row, tokens);
}

void	process_line(char *line, t_fdf *fdf, int row, int mode)
{
	char	*trimmed_line;

	trimmed_line = ft_strtrim(line, " \t\n");
	if (!trimmed_line)
	{
		free(line);
		ft_free_and_exit(fdf, "Memory error in trim\n", 1, 1);
	}
	if (ft_strlen(trimmed_line) == 0)
	{
		free(line);
		free(trimmed_line);
		ft_free_and_exit(fdf, "Error map not valid\n", 1, 1);
	}
	fdf->tokens = ft_split(trimmed_line, ' ');
	if (!fdf->tokens)
	{
		free(line);
		free(trimmed_line);
		ft_free_and_exit(fdf, "Memory error in split\n", 1, 1);
	}
	ft_process_line_aux(row, fdf->tokens, fdf, mode);
	ft_free_split_tokens(fdf->tokens);
	free(trimmed_line);
}

void	ft_read_file(t_fdf *file_map, int mode)
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
				ft_free_and_exit(file_map, "Parse: Map not valid\n", 1, 1);
			}
		}
		else
			break ;
	}
}

void	ft_validate_and_store(char *file, t_fdf *fdf)
{
	fdf->infile = open(file, O_RDONLY);
	if (fdf->infile < 0)
		ft_free_and_exit(fdf, "Error opening the file", 1, 1);
	ft_read_file(fdf, 0);
	ft_malloc_matrix_memory(fdf);
	fdf->infile = open(file, O_RDONLY);
	if (fdf->infile < 0)
		ft_free_and_exit(fdf, "Error opening the file", 1, 1);
	ft_read_file(fdf, 1);
	ft_find_z_min_max(fdf);
	ft_assign_color_by_z(fdf);
}
