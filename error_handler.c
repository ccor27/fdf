/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_hanlder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crosorio < crosorio@student.42madrid.com>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-25 13:32:12 by crosorio          #+#    #+#             */
/*   Updated: 2025-08-25 13:32:12 by crosorio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_error(char *msg, int exit_code)
{
	if(msg)
		ft_printf(msg);
	exit(exit_code);
}

void	ft_error_parse(t_file_map *file_map, char *msg, int exit_code)
{
	//free struct memory
	if(file_map->matrix)
		ft_free_split_matrix(file_map->matrix);
	if(file_map->tokens)
		ft_free_split_tokens(file_map->tokens);
	ft_error(msg,exit_code);
}

void	ft_free_split_tokens(char **tokens)
{
	int i;

	i = 0;
	while(tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

void	ft_free_split_matrix(t_node **nodes)
{
	int i;

	i = 0;
	while(nodes[i])
	{
		free(nodes[i]);
		i++;
	}
	free(nodes);
}
