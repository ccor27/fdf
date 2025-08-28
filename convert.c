/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crosorio < crosorio@student.42madrid.com>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-28 14:16:09 by crosorio          #+#    #+#             */
/*   Updated: 2025-08-28 14:16:09 by crosorio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_calculate_isos(t_file_map *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->height)
	{
		j = 0;
		while (j < data->width)
		{
			data->matrix[i][j].xiso = (data->matrix[i][j].x
					- data->matrix[i][j].y) * cos(0.523599);
			data->matrix[i][j].yiso = (data->matrix[i][j].x
					+ data->matrix[i][j].y) * sin(0.523599)
				- data->matrix[i][j].z;
			j++;
		}
		i++;
	}
}
