/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_store_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crosorio < crosorio@student.42madrid.com>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-25 16:17:48 by crosorio          #+#    #+#             */
/*   Updated: 2025-08-25 16:17:48 by crosorio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_malloc_matrix_memory(t_file_map *file_map)
{
	int	i;

	file_map->matrix = malloc(sizeof(t_node *) * file_map->height);
	if (!file_map->matrix)
		ft_error_parse(file_map, "Parse error: malloc failed\n", 1);
	i = 0;
	while (i < file_map->height)
	{
		file_map->matrix[i] = malloc(sizeof(t_node) * file_map->width);
		if (!file_map->matrix[i])
			ft_error_parse(file_map, "Parse error: malloc failed\n", 1);
		i++;
	}
}

static int	 is_valid_hex(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_base_value(str[i], "0123456789ABCDEFabcdef") == -1)
			return (0);
		i++;
	}
	return (1);
}

int	parse_token(t_node *node, char *token, int x, int y)
{
	char	*comma;

	comma = ft_strchr(token, ',');
	node->x = x;
	node->y = y;
	if (comma)
	{
		*comma = '\0';
		node->z = ft_atoi(token);
		if (*(comma + 1) == '0' && (*(comma + 2) == 'x' || *(comma + 2) == 'X'))
		{
			if (!is_valid_hex(comma + 3))
				return (0);
			node->color = ft_atoi_base(comma + 3, "0123456789ABCDEFabcdef");
		}
		else
			return (0);
	}
	else
	{
		node->z = ft_atoi(token);
		node->color = 0xFFFFFF;
	}
	return (1);
}
