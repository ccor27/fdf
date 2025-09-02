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

void	ft_malloc_matrix_memory(t_fdf *file_map)
{
	int	i;

	file_map->matrix = malloc(sizeof(t_node *) * file_map->height);
	if (!file_map->matrix)
		ft_free_and_exit(file_map, "Parse error: malloc failed\n", 1);
	i = 0;
	while (i < file_map->height)
	{
		file_map->matrix[i] = malloc(sizeof(t_node) * file_map->width);
		if (!file_map->matrix[i])
			ft_free_and_exit(file_map, "Parse error: malloc failed\n", 1);
		i++;
	}
}

int	is_valid_hex(const char *str)
{
	int	i;

	if (ft_strlen(str) < 3)
		return (0);
	if (str[0] != '0' || (str[1] != 'x' && str[1] != 'X'))
		return (0);
	i = 2;
	while (str[i])
	{
		if (ft_base_value(str[i], "0123456789ABCDEFabcdef") == -1)
			return (0);
		i++;
	}
	return (1);
}

int	ft_is_valid_integer(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
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
		if (!ft_is_valid_integer(token))
			return (0);
		node->z = ft_atoi(token);
		if (!is_valid_hex(comma + 1))
			return (0);
		node->color = ft_atoi_base(comma + 2, "0123456789ABCDEFabcdef");
	}
	else
	{
		if (!ft_is_valid_integer(token))
			return (0);
		node->z = ft_atoi(token);
		node->color = 0xFFFFFF;
	}
	return (1);
}
